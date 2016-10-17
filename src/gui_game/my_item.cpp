#include "my_item.h"

QRectF MyItem::boundingRect() const
{
  return QRectF(x, y, radius * 0.8, radius * 0.8);// radius of circle is 100
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  QRectF rect = boundingRect();
  if (status == 1)// pressed, light this item
    {
      QPen pen(Qt::NoPen);
      painter->setPen(pen);
      QPointF p(x, y);
      QImage image(":background_light.png");
      image = image.scaled(radius * 0.8, radius * 0.8, Qt::IgnoreAspectRatio);
      painter->drawImage(p, image);
      painter->drawEllipse(rect);
    }
  else if (status == 0) // origin
    {
      QPen pen(Qt::NoPen);
      painter->setPen(pen);
      QPointF p(x, y);
      QImage image(":background.png");
      image = image.scaled(radius * 0.8, radius * 0.8, Qt::IgnoreAspectRatio);
      painter->drawImage(p, image);
      painter->drawEllipse(rect);
    }
  else if (status == 2) // released: change all selected item to opposite color
    {
      QPen pen(Qt::NoPen);
      painter->setPen(pen);
      QPointF p(x, y);
      QImage image(":background.png"); // modify here
      image = image.scaled(radius * 0.8, radius * 0.8, Qt::IgnoreAspectRatio);
      painter->drawImage(p, image);
      painter->drawEllipse(rect);
    }
  else if (status == 3)
    {

    }
}

void MyItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if ( !event ) {
      return;
   }
  QPointF p = event->lastPos(); // p.x is actually y
  QPointF p2 = event->pos(); // p.x is actually y
  std::cout << p.x() << " " << p.y() << std::endl;
  std::cout << p2.x() << " " << p2.y() << std::endl;

  status = 1;
  update(); // go to paint
  QGraphicsItem::mousePressEvent(event);
}

void MyItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  if ( !event ) {
      return;
   }
  status = 2;
  update();
  QGraphicsItem::mouseReleaseEvent(event);
}

void MyItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  if ( !event ) {
      return;
   }
  // if mouse go through item and this item is in the 4-neighbor of the last item, we light this item
  status = 3;
  QPointF p = event->pos(); // p.x is actually y
  update();
}
