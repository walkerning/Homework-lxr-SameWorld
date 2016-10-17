#ifndef _SAME_WORLD_LEVEL_H_
#define _SAME_WORLD_LEVEL_H_
#include <cstdlib>
#include <vector>
#include <QWidget>
#include <QGraphicsScene>
#include "ui_level.h"
#include "items/level_item.h"

//#include "../user.h"
//#include "../chess.h"

class LevelGui:public QWidget
{
  Q_OBJECT

 public:
  LevelGui();
  virtual ~LevelGui() {};

  public slots:
    void Layout(int level_num, int current_level);

  private:
    QRectF findSceneRect(int level_num, int current_level);
    Ui::LevelGui ui;
    std::vector<LevelGraphicsItem*> level_items;
};
#endif
