#include "level.h"

LevelGui::LevelGui() {
  ui.setupUi(this);
  ui.graphicsView->setScene(new QGraphicsScene(ui.graphicsView));
  ui.graphicsView->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
  ui.graphicsView->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
  QMatrix mtx;
  mtx.scale(ui.graphicsView->width()/LEVEL_SCENE_WIDTH, ui.graphicsView->width()/LEVEL_SCENE_WIDTH);
  ui.graphicsView->setMatrix(mtx);
  //ui.graphicsView->setSceneRect();
}

void LevelGui::Layout(int level_num, int current_level) {
  // srand(1); // everytime the layout should be the same
  int start = level_items.size();
  if (level_num > start) {
    for (int i = start; i < level_num; i++) {
      LevelGraphicsItem* new_item = new LevelGraphicsItem(i, (i < current_level));
      this->ui.graphicsView->scene()->addItem(new_item);
      if (i %  2 == 0) {
        new_item->SetPos(4, i);
      } else {
        new_item->SetPos(1, i);
      }
      if (i > 0) {
        // TODO: setup QPen for this
        QPointF p1 = new_item->CenterPos();
        QPointF p2 = level_items.back()->CenterPos();
        this->ui.graphicsView->scene()->addLine(p1.x(), p1.y(), p2.x(), p2.y());
      }
      level_items.push_back(new_item);
    }
  }
  // set finished state of old level items.
  for (int i = 0; i < start; i++) {
    level_items[i]->SetFinished(i < current_level);
  }
  QRectF rect = findSceneRect(level_num, current_level);
  ui.graphicsView->setSceneRect(rect);
  ui.graphicsView->centerOn(rect.center());
}

QRectF LevelGui::findSceneRect(int level_num, int current_level) {
  int center_level = (current_level == 0)? 0: center_level-1;
  float centery = level_items[center_level]->CenterPos().y();
  QRectF rect(0, centery - LEVEL_SCENE_HEIGHT/2, LEVEL_SCENE_WIDTH, LEVEL_SCENE_HEIGHT );
  return rect;
}
