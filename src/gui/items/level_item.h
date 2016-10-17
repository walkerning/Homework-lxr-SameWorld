#include <string>
#include <QGraphicsItem>
#include <QPainter>
#include <QImage>
#include "items.h"

class LevelGraphicsItem: public SameWorldItem {
  //Q_OBJECT

 public:
 LevelGraphicsItem(int level, bool finished, QGraphicsItem* parent = NULL): SameWorldItem(parent),
    level_(level), finished_(finished) {}
  inline int Level() { return level_; }
  static const char* fileName;
  static const char* finishedFileName;
  void SetFinished(bool finished);

 protected:
  virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                     QWidget* widget=NULL);
  virtual QRectF boundingRect() const;

 private:
  int level_;
  bool finished_;
};
