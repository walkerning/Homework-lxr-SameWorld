#ifndef MY_ITEM_H
#define MY_ITEM_H

#include <QPainter>
#include <QGraphicsItem>

//class for customization
class MyItem: public QGraphicsObject
{
  Q_OBJECT

 public:
   MyItem()
    {
      pressed = false;
      setFlag(ItemIsMovable);
    }


  // item state
  bool pressed;

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
