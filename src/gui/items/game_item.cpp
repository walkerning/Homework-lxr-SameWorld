#include "game_item.h"

QRectF GameItem::boundingRect() const
 {
   //return QRectF(0, 0, 0.8*UNIT_WIDTH, 0.8*UNIT_WIDTH);
   return QRectF(0, 0, UNIT_WIDTH, UNIT_WIDTH);
 }

void GameItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  QRectF rect = boundingRect();
  int color = piece.get_status();
  std::string image_name = ":";
  switch (color) {
  case 1: image_name += "white"; break;
  case 2: image_name += "black"; break;
  }
  switch (status) {
  case ItemNormal: break;
  case ItemPressed: image_name += "_pressed"; break;
  }
  if (origin) {
    image_name += "_origin";
  }
  painter->save();
  image_name += ".png";
  QImage im(image_name.c_str());
  // QPen pen(Qt::NoPen);
  // painter->setPen(pen);
  float image_size = status == ItemNormal? 0.7*UNIT_WIDTH:0.9*UNIT_WIDTH;
    //painter->drawImage(0.1 * UNIT_WIDTH, 0.1 * UNIT_WIDTH, im.scaled(0.8*UNIT_WIDTH, 0.8*UNIT_WIDTH,
    //                            Qt::IgnoreAspectRatio));
  painter->drawImage((UNIT_WIDTH - image_size)/2, (UNIT_WIDTH - image_size)/2,
                     im.scaled(image_size, image_size, Qt::IgnoreAspectRatio));
  painter->restore();
}
