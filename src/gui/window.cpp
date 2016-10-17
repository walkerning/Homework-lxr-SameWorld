#include "window.h"

MainWindow::MainWindow(QWidget *parent) :
  QGraphicsView(parent), startGui(new StartGui()),
  levelGui(new LevelGui()), gameGui(new GameGui()) {
  setScene(new QGraphicsScene(this));
  //setSceneRect();

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
  appearAni->setKeyValueAt(0, 1);
  appearAni->setKeyValueAt(1, 0);
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
