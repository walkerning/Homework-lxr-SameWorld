#ifndef _SAMEWORLD_GAME_VIEW_H_
#define _SAMEWORLD_GAME_VIEW_H_

#include <vector>
#include <cmath>

#include <QGraphicsView>
#include <QMouseEvent>

#include "items/game_item.h"
#include "../user.h"
#include "../chess.h"

#define GAMEVIEW_WIDTH 450
#define GAMEVIEW_HEIGHT 450

class GameView: public QGraphicsView {
  Q_OBJECT

 public:
 GameView(QWidget* parent=NULL): QGraphicsView(parent), mousePressed(false) {
    setMouseTracking(true);
    resize(GAMEVIEW_WIDTH, GAMEVIEW_HEIGHT);
    setScene(new QGraphicsScene(this));
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
  }
  void setUserInput(UserInput input);

 signals:
  void levelFinished();
  void levelFailed();

 protected:
  virtual void mouseMoveEvent(QMouseEvent* e);
  virtual void mousePressEvent(QMouseEvent* e);
  virtual void mouseReleaseEvent(QMouseEvent* e);

 private:
  bool isNeighbor(Piece p1, Piece p2);
  bool judgeSuccess();

  int num_origin;
  bool mousePressed;
  std::vector<GameItem*> route_items;
  std::vector<GameItem*> all_items;
};
#endif
