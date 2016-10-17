#include "game.h"

void GameGui::Layout() // once get the gameSignal, start to design layout
{
  //int height = input.get_height();// attention: qt's height is actually the width
  //int width = input.get_width();
  int height = 5;
  int width = 3;
  QGraphicsScene* scene = new QGraphicsScene(0, 0, 400, 400); // set the size of scene
  QGraphicsView* view = new QGraphicsView(scene);

  int radius = 400 / std::max(height, width);

  // move all items to center of the scene
  // right center (200, 200)
  // now center (height * radius, width * radius)
  MyItem *item[height * width]; //FIXME: need release
  for (int i = 0; i < height; ++i)
    for (int j = 0; j < width; ++j)
      {
        item[i * width + j] = new MyItem(j * radius - width * radius / 2 + 200, i * radius - height * radius / 2 + 200, radius);
        scene->addItem(item[i * width + j]);
      }

  //QGraphicsItem *item_pos = view->itemAt(272, 351);





  ui.pieceLayout->addWidget(view);
}

void GameGui::Restart()
{




}

void GameGui::ShowAnswer()
{




}
