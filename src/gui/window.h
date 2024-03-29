#include <map>
#include <vector>
#include <QDir>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QStateMachine>
#include <QState>
#include <QAbstractTransition>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QFinalState>
#include <QSignalTransition>
#include <QDebug>

#include "start.h"
#include "level.h"
#include "game.h"

class MainWindow: public QGraphicsView {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = NULL);
  static QAbstractAnimation* MakeAnimation(QGraphicsProxyWidget* formerWidget,
                                           QGraphicsProxyWidget* aimWidget);
  virtual ~MainWindow() {};

  public slots:
    void showWindow();
    void closePrevWindow();
    void layoutGameGui(int);
    void layoutLevelGui();
    void onLevelFinished();

 private:
    void ReadAllLevels();
    void ReadHistory();
    void WriteHistory();
    StartGui* startGui;
    LevelGui* levelGui;
    GameGui* gameGui;

    QGraphicsProxyWidget* startWindow;
    QGraphicsProxyWidget* levelWindow;
    QGraphicsProxyWidget* gameWindow;

    QStateMachine* stateM;
    QState* startState;
    QState* levelState;
    QState* gameState;
    QFinalState* quitState;

    QState* prevState;
    std::map<QState*, QGraphicsProxyWidget*> stateWindowMap;

    std::vector<UserInput> userInputVec;
    int current_level_;
};
