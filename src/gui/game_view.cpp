#include "game_view.h"

void GameView::mousePressEvent(QMouseEvent* e) {
  QPointF pt = mapToScene(e->pos());
  QGraphicsItem* item = scene()->itemAt(pt);
  if (item == NULL) return;
  GameItem* specific_item;
  if (!(specific_item = dynamic_cast<GameItem*>(item))) {
    return;
  }
  if (!specific_item->Origin()) {
    return;
  }
  specific_item->setStatus(ItemPressed);
  route_items.push_back(specific_item);
  mousePressed = true;
}

bool GameView::isNeighbor(Piece p1, Piece p2) {
  Piece::Coordinate c1 = p1.get_coordinate();
  Piece::Coordinate c2 = p2.get_coordinate();
  int xdiff = abs(c1.x - c2.x);
  int ydiff = abs(c1.y - c2.y);
  return (xdiff + ydiff == 1);
}

void GameView::mouseMoveEvent(QMouseEvent* e) {
  if (!mousePressed) return;
  QPointF pt = mapToScene(e->pos());
  QGraphicsItem* item = scene()->itemAt(pt);
  if (item == NULL) return;
  GameItem* specific_item;
  if (!(specific_item = dynamic_cast<GameItem*>(item))) {
    return;
  }
  if (specific_item == route_items.back()) {
    return;
  }
  if (!isNeighbor(specific_item->Piece(), route_items.back()->Piece())) {
    return;
  }
  int num_items = route_items.size();
  if (num_items > 1 && specific_item == route_items[route_items.size() - 2]) {
    route_items.back()->setStatus(ItemNormal);
    route_items.pop_back();
    return;
  }
  for (int i = 0; i < num_items - 2; i ++) {
    if (route_items[i] == specific_item) {
      return;
    }
  }
  specific_item->setStatus(ItemPressed);
  route_items.push_back(specific_item);
}

void GameView::mouseReleaseEvent(QMouseEvent* e) {
  if (route_items.size() > 1) {
    for (const auto& item: route_items) {
      item->flip();
      item->setStatus(ItemNormal);
    }
    route_items[0]->setOrigin(false);
    num_origin --;
    if (judgeSuccess()) {
      emit levelFinished();
    } else if (num_origin <= 0) {
      emit levelFailed();
    }
  } else {
    for (const auto& item: route_items) {
      item->setStatus(ItemNormal);
    }
  }
  route_items.clear();
  mousePressed = false;
}

void GameView::setUserInput(UserInput input) {
  scene()->clear();
  all_items.clear();
  ChessBoard board(input);
  num_origin = board.Origin().size();
  for (auto& piece: board.Pieces()) {
    if (piece.get_status() == 3) {
      continue;
    }
    GameItem* item = new GameItem(piece);
    if (std::find(board.Origin().begin(), board.Origin().end(), piece.get_coordinate()) != board.Origin().end()) {
      item->setOrigin(true);
    }
    all_items.push_back(item);
    scene()->addItem(item);
  }

  // reset the scale matrix
  QRectF rect = scene()->itemsBoundingRect();
  float width_scale = GAMEVIEW_WIDTH/(1.2 * rect.width());
  float height_scale = GAMEVIEW_HEIGHT/(1.2 * rect.height());
  float scale = width_scale > height_scale? height_scale: width_scale;
  QMatrix mtx;
  mtx.scale(scale, scale);
  setMatrix(mtx);
  setSceneRect(rect);
  centerOn(rect.center());
}

bool GameView::judgeSuccess() {
  int prev_color = 0;
  for (auto& item: all_items) {
    int color = item->Piece().get_status();
    if (color != 3) {
      if (prev_color && prev_color != color)
        return false;
      prev_color = color;
    }
  }
  return true;
}
