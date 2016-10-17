#ifndef _SAMEWORLD_GAME_ITEM_H_
#define _SAMEWORLD_GAME_ITEM_H_

#include <string>
#include <QPainter>
#include <QGraphicsItem>
#include <QPolygon>
#include <QGraphicsSceneMouseEvent>
#include "items.h"
#include "../../piece.h" // ugly... no time..

enum GameItemStatus {
  ItemNormal,
  ItemPressed,
};

class GameItem: public SameWorldItem {
 public:
 GameItem(Piece p): piece(p), status(ItemNormal), origin(false) {
    SetPos(p.get_coordinate().x, p.get_coordinate().y);
  }

  inline class Piece Piece() { return piece; }

  inline bool Origin() { return origin; }
  void setOrigin(bool isOrigin) {
    this->origin = isOrigin;
    update();
  }

  void setStatus(GameItemStatus status) {
    this->status = status;
    update();
  }

  void flip() {
    int now_color = piece.get_status();
    // ==3 is an error
    if (now_color != 3) {
      piece.set_status(3 - now_color);
    }
    update();
  }

 protected:
   virtual QRectF boundingRect() const;

  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

 private:
  class::Piece piece;
  GameItemStatus status;
  bool origin;
};

#endif //_SAMEWORLD_GAME_ITEM_H_
