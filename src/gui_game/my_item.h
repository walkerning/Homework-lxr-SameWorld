#ifndef MY_ITEM_H
#define MY_ITEM_H

#include <iostream>
#include <QPainter>
#include <QGraphicsItem>
#include <QPolygon>
#include <QGraphicsSceneMouseEvent>

//class for customization
class MyItem: public QGraphicsObject
{

 public:
 MyItem(int x, int y, int radius):x(x), y(y), radius(radius)
    {
      status = 0;
      setFlag(ItemIsSelectable);
    }

  // item state
  int status; // status = 0, origin, status = 1, pressed, status = 2, released, status = 3, moved
  int x;
  int y;
  int radius;

 protected:
  //overriding mouse events
    // overriding boundingRect(must do it!)
   virtual QRectF boundingRect() const;

  // overriding paint()(must do it!)
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // MY_ITEM_H
