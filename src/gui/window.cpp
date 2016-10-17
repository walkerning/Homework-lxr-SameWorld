#include "window.h"

MainWindow::MainWindow(QWidget *parent) :
  QGraphicsView(parent), startGui(new StartGui()),
  levelGui(new LevelGui()), gameGui(new GameGui()) {
  ReadAllLevels();
  ReadHistory();
  setScene(new QGraphicsScene(this));
  //setSceneRect();
  setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
  setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
  setFixedSize(QSize(500, 585));
  setSceneRect(QRectF(0, 0, 500, 580));

  startWindow = this->scene()->addWidget(startGui);
  levelWindow = this->scene()->addWidget(levelGui);
  gameWindow = this->scene()->addWidget(gameGui);

  // close widgets except startGui
  levelWindow->widget()->close();
  gameWindow->widget()->close();

  stateM = new QStateMachine(this);
  startState = new QState(stateM);
  levelState = new QState(stateM);
  gameState = new QState(stateM);
  quitState = new QFinalState(stateM);
  prevState= NULL;

  QSignalTransition* transStartToLevel = startState->addTransition(startGui, SIGNAL(levelSignal()),
                                                                   levelState);
  transStartToLevel->addAnimation(MakeAnimation(startWindow, levelWindow));

  QSignalTransition* transLevelToGame = levelState->addTransition(levelGui, SIGNAL(gameSignal()),
                                                                  gameState);
  transLevelToGame->addAnimation(MakeAnimation(levelWindow, gameWindow));
  QSignalTransition* transGameToStart = gameState->addTransition(gameGui, SIGNAL(backSignal()),
                                                                 startState);
  QSignalTransition* transStartToQuit = startState->addTransition(startGui, SIGNAL(exitSignal()),
                                                                  quitState);
  stateWindowMap[startState] = startWindow;
  stateWindowMap[levelState] = levelWindow;
  stateWindowMap[gameState] = gameWindow;

  QSignalTransition* transitions[] = {transStartToLevel, transLevelToGame, transGameToStart};
  for (int i = 0; i < 3; i ++) {
    connect(transitions[i], SIGNAL(triggered()), this, SLOT(showWindow()));
  }
  for (const auto& kv: stateWindowMap) {
    connect(kv.first, SIGNAL(entered()), SLOT(closePrevWindow()));
  }

  // connect layout signals
  connect(startGui, SIGNAL(levelSignal()), this, SLOT(layoutLevelGui()));
  connect(levelGui, SIGNAL(gameLayoutSignal(int)), this, SLOT(layoutGameGui(int)));
  stateM->setInitialState(startState);
  stateM->start();
}

void MainWindow::showWindow() {
  QObject* sender = this->sender();
  QState* target = dynamic_cast<QState*>(dynamic_cast<QAbstractTransition*>(sender)->targetState());
  auto it = stateWindowMap.find(target);
  if (it != stateWindowMap.end()) {
    it->second->widget()->show();
  }
}

QAbstractAnimation* MainWindow::MakeAnimation(QGraphicsProxyWidget* formerWidget,
                                              QGraphicsProxyWidget* aimWidget) {
  QPropertyAnimation* disappearAni = new QPropertyAnimation(formerWidget->widget(), "windowOpacity");
  disappearAni->setDuration(500);
  disappearAni->setKeyValueAt(0, 1);
  disappearAni->setKeyValueAt(1, 0);
  disappearAni->setEasingCurve(QEasingCurve::InOutQuad);
  QPropertyAnimation* appearAni = new QPropertyAnimation(aimWidget->widget(), "windowOpacity");
  appearAni->setDuration(500);
  appearAni->setKeyValueAt(0, 0);
  appearAni->setKeyValueAt(1, 1);
  appearAni->setEasingCurve(QEasingCurve::InOutQuad);
  auto parallelAniGrp = new QParallelAnimationGroup();
  parallelAniGrp->addAnimation(disappearAni);
  parallelAniGrp->addAnimation(appearAni);
  return parallelAniGrp;
}

void MainWindow::closePrevWindow() {
  if (prevState == NULL)
    return;
  prevState = dynamic_cast<QState*>(this->sender());
  stateWindowMap[prevState]->widget()->close();
}

void MainWindow::layoutGameGui(int level) {
  //gameGui->Layout(userInputVec[level]);
}

void MainWindow::layoutLevelGui() {
  levelGui->Layout(userInputVec.size(), current_level_);
}
void MainWindow::ReadHistory()
{
  QFile level_file(":level.txt");
  if (!level_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "Unable to open level file!!";
    return;
  }
  QTextStream in(&level_file);
  std::string level_line;
  while (!in.atEnd()) {
    QString line = in.readLine();
    current_level_ = atoi(line.toStdString().c_str());
  }
  level_file.close();
  //ReadAllLevel(user_level);
}

void MainWindow::ReadAllLevels() {
  // read level infos from "data.txt"
  QFile data_file(":data.txt"); // get levels data
  if (!data_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "Unable to open data file!!";
    return;
  }
  QTextStream in(&data_file);
  std::string line;
  while (!in.atEnd()) {
    QString qstr = in.readLine();
    UserInput input; // save user's level infos
    QStringList list = qstr.split(" ", QString::SkipEmptyParts);
    // set height and width
    int height = list.at(1).toInt(); // height
    input.set_height(height);
    int width = list.at(2).toInt(); // width
    input.set_width(width);
    // set status(black, white or block)
    std::vector<int> status;
    for (int i = 0; i < input.get_height(); i++)
      for (int j = 0; j < input.get_width(); j++)
        status.push_back(WHITE);
    QString black_pieces = list.at(3); // black pieces
    if (black_pieces != "-1") // exist black pieces
      {
        QStringList black_pieces_index = black_pieces.split(",", QString::SkipEmptyParts);
        for (int i = 0; i < black_pieces_index.size(); ++i)
          status[black_pieces_index.at(i).toInt()] = BLACK;
      }
    QString block_pieces = list.at(4); // block pieces
    if (block_pieces != "-1") // exist block pieces
      {
        QStringList block_pieces_index = block_pieces.split(",", QString::SkipEmptyParts);
        for (int i = 0; i < block_pieces_index.size(); ++i)
          status[block_pieces_index.at(i).toInt()] = BLOCK;
      }
    input.set_status(status);
    // set origin
    std::vector<Piece::Coordinate> origin;
    QString qorigin = list.at(5); // origin
    if (qorigin != "-1") // exist origin
      {
        QStringList origin_index = qorigin.split(",", QString::SkipEmptyParts);
        for (int i = 0; i < origin_index.size(); ++i)
          {
            int x = origin_index.at(i).toInt() / input.get_width();
            int y = origin_index.at(i).toInt() % input.get_width();
            Piece::Coordinate origin_point = {x, y};
            origin.push_back(origin_point);
          }
        input.set_origin(origin);
      }
    userInputVec.push_back(input);
  }
}
