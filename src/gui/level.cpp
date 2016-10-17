#include "level.h"

LevelGui::LevelGui() {
  ui.setupUi(this);
  this->graphicsView = new LevelGraphicsView(this);
  this->graphicsView->move(0, 0);
  connect(graphicsView, SIGNAL(gameSignal(int)), this, SIGNAL(gameLayoutSignal(int)));
  connect(graphicsView, SIGNAL(gameSignal(int)), this, SIGNAL(gameSignal()));
}

void LevelGui::Layout(int level_num, int current_level) {
  int start = level_items.size();
  if (level_num > start) {
    for (int i = start; i < level_num; i++) {
      LevelGraphicsItem* new_item = new LevelGraphicsItem(i, (i < current_level));
      this->graphicsView->scene()->addItem(new_item);
      if (i %  2 == 0) {
        new_item->SetPos(3, i);
      } else {
        new_item->SetPos(1, i);
      }
      if (i > 0) {
        // TODO: setup QPen for this
        QPointF p1 = new_item->CenterPos();
        QPointF p2 = level_items.back()->CenterPos();
        QGraphicsLineItem* line = this->graphicsView->scene()->addLine(p1.x(), p1.y(), p2.x(), p2.y(),
                                                                         QPen(Qt::darkCyan));
        line->setZValue(0);
      }
      level_items.push_back(new_item);
    }
  }
  // set finished state of old level items.
  for (int i = 0; i < start; i++) {
    level_items[i]->SetFinished(i < current_level);
  }
  QRectF rect = findSceneRect(level_num, current_level);
  QMatrix mtx;
  mtx.scale(float(graphicsView->width())/LEVEL_SCENE_WIDTH, float(graphicsView->width())/LEVEL_SCENE_WIDTH);
  graphicsView->setMatrix(mtx);
  graphicsView->setSceneRect(rect);
  graphicsView->centerOn(rect.center());
}

QRectF LevelGui::findSceneRect(int level_num, int current_level) {
  int center_level = (current_level == 0)? 0: current_level-1;
  float centery = level_items[center_level]->CenterPos().y();
  QRectF rect(0, centery - LEVEL_SCENE_HEIGHT/2, LEVEL_SCENE_WIDTH, LEVEL_SCENE_HEIGHT );
  return rect;
}

void LevelGraphicsView::mousePressEvent(QMouseEvent* e) {
    QPointF pt = mapToScene(e->pos());
    QGraphicsItem* item = scene()->itemAt(pt);
    if (item == NULL) return;
    emit gameSignal(dynamic_cast<LevelGraphicsItem*>(item)->Level());
  }
