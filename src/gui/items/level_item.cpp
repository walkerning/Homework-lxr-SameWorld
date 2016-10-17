#include "level_item.h"

const char* LevelGraphicsItem::fileName = ":level_item.png";
const char* LevelGraphicsItem::finishedFileName = ":finished_level_item.png";

QRectF LevelGraphicsItem::boundingRect() const {
  QRectF r(0, 0, UNIT_WIDTH, UNIT_WIDTH);
  return r;
}

void LevelGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                              QWidget* widget) {
  painter->save();
  QImage* im = new QImage(finished_?LevelGraphicsItem::finishedFileName:LevelGraphicsItem::fileName);

  painter->drawImage(0, 0,
                     im->scaled(UNIT_WIDTH, UNIT_WIDTH,
                                Qt::IgnoreAspectRatio));
  QColor color(255, 255, 255);
  QBrush brush(color);
  painter->setBrush(brush);
  painter->setPen(QPen(color));
  QFont font = painter->font() ;
  font.setPointSize(font.pointSize() * 2);
  painter->setFont(font);
  painter->drawText(boundingRect(), Qt::AlignCenter, std::to_string(level_).c_str());
  painter->restore();
}

void LevelGraphicsItem::SetFinished(bool finished) {
  finished_ = finished;
  update();
}
