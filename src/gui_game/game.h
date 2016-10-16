#include <QWidget>
#include <QString>
#include "ui_game.h"
#include "../user.h"
#include "my_item.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QListWidget>
#include <QDebug>
#include <QPainter>

class GameGui:public QWidget
{
  Q_OBJECT

 public:
  GameGui() {
    ui.setupUi(this);

    connect(ui.renewButton, SIGNAL(clicked()), this, SLOT(Restart())); // click "renew", start this level from beginning
    connect(ui.answerButton, SIGNAL(clicked()), this, SLOT(ShowAnswer())); // click "answer", give user a hint
    connect(ui.backButton, SIGNAL(clicked()), this, SLOT(cLayout())); // click "answer", give user a hint

  }

 public slots:
   void Layout();
   void Restart();
   void ShowAnswer();

  private:
    Ui::GameForm ui;
};

// 算法：
/* 如果鼠标点按并且该点在两个起点位置之一，、判断为开始位置。之后必须一直在press状态，松开即停止，在press的过程中每经过一个新的圆（需要是4邻域），就连出一条新的线，并且更改changed && status，如果发现新连的圆正好是上一个就把那条线收回，并且更改changed && status。 */
/* 重来：重新把一开始的界面刷一遍 */
/* 看答案：先用电脑计算出答案（接口：第一步哪些棋变色，第二步哪些棋变色），之后将那些需要被选中的棋“点亮”，当用户按顺序点亮这些点之后，就成功进入下一关。 */
