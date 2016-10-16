#include "my_item.h"

QRectF MyItem::boundingRect() const
{
  return QRectF(0, 0, 100, 100);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  QRectF rect = boundingRect();
  if (pressed)
    {
      QPen pen(Qt::red, 3);
      painter->setPen(pen);
      painter->drawEllipse(rect);
    }
  else
    {
      QPen pen(Qt::black, 3);
      painter->setPen(pen);
      painter->drawRect(rect);
    }
}

void MyItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  pressed = true;
  update();
  QGraphicsItem::mousePressEvent(event);
}

void MyItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  pressed = false;
  update();
  QGraphicsItem::mouseReleaseEvent(event);
}
