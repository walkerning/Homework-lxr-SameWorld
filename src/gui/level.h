#ifndef _SAME_WORLD_LEVEL_H_
#define _SAME_WORLD_LEVEL_H_
#include <cstdlib>
#include <vector>
#include <QWidget>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDebug>
#include "ui_level.h"
#include "items/level_item.h"

//#include "../user.h"
//#include "../chess.h"


class LevelGraphicsView: public QGraphicsView {
  Q_OBJECT

 public:
  LevelGraphicsView(QWidget* parent=NULL): QGraphicsView(parent) {
    resize(LEVEL_SCENE_WIDTH, LEVEL_SCENE_HEIGHT + 5);
    setScene(new QGraphicsScene(this));
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    QMatrix mtx;
    mtx.scale(float(this->width())/LEVEL_SCENE_WIDTH, float(this->width())/LEVEL_SCENE_WIDTH);
    setMatrix(mtx);
  }
 signals:
  void gameSignal(int);

 protected:
  virtual void mousePressEvent(QMouseEvent* e);
};


class LevelGui:public QWidget
{
  Q_OBJECT

 public:
  LevelGui();
  virtual ~LevelGui() {};

 signals:
  void gameSignal();
  void gameLayoutSignal(int);

  public slots:
    void Layout(int level_num, int current_level);

 private:
    QRectF findSceneRect(int level_num, int current_level);
    Ui::LevelGui ui;
    std::vector<LevelGraphicsItem*> level_items;
    LevelGraphicsView* graphicsView;
};

#endif
