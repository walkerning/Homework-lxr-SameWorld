#include "game.h"

void GameGui::Layout() // once get the gameSignal, start to design layout
{
  //int height = input.get_height();
  //int width = input.get_width();
  QGraphicsScene* scene = new QGraphicsScene;
  QGraphicsView* view = new QGraphicsView(scene);
  MyItem *item = new MyItem();
  //scene->addItem(item);
  ui.pieceLayout->addWidget(view);

}

void GameGui::Restart()
{




}

void GameGui::ShowAnswer()
{




}
