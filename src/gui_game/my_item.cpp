#include "my_item.h"

QRectF MyItem::boundingRect() const
{
  return QRectF(x, y, radius * 0.8, radius * 0.8);// radius of circle is 100
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  QRectF rect = boundingRect();
  if (pressed)
    {
      QPen pen(Qt::red, 3);
      painter->setPen(pen);
      painter->drawRect(rect);
    }
  else
    {
      QPen pen(Qt::black, 3);
      painter->setPen(pen);

      QBrush brush(Qt::Dense1Pattern);
      QImage image;
      image.load(":background.png");
      brush.setTextureImage(image);
      painter->setBrush(brush);
      painter->drawEllipse(rect);
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
