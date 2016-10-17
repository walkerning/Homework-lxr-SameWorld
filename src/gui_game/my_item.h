#ifndef MY_ITEM_H
#define MY_ITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QPolygon>

//class for customization
class MyItem: public QGraphicsObject
{

 public:
 MyItem(int x, int y, int radius):x(x), y(y), radius(radius)
    {
      pressed = false;
      setFlag(ItemIsMovable);
    }

  // item state
  bool pressed;
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
