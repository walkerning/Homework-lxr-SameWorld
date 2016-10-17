#ifndef _SAME_WORLD_ITEMS_H_
#define _SAME_WORLD_ITEMS_H_
#include <QGraphicsObject>
//#define EDGE_WIDTH 2
#define UNIT_WIDTH 20

#define LEVEL_SCENE_WIDTH 100
#define LEVEL_SCENE_HEIGHT 100

class SameWorldItem: public QGraphicsObject {
public:
SameWorldItem(QGraphicsItem* parent=NULL): QGraphicsObject(parent) {}
inline void SetPos(int x, int y) {
setPos(x * UNIT_WIDTH, y * UNIT_WIDTH);
}
inline QPointF CenterPos() {
return scenePos() + QPointF(UNIT_WIDTH/2, UNIT_WIDTH/2);
}
};
#endif
