#include "chess.h"

void ChessBoard::Start()
{
  // first version: only support two origin points
  // get a origin randomly
  Piece::Coordinate first_origin = origin.front();
  if (SearchWayFool(first_origin, pieces)) // find one way
    {
      std::cout << "find one way!!!";
    }
  else // use another origin
    {
      //TODO: detect symmetry to avoid recurring the second origin
      //TODO: if we have three origins or more, use a circulate rather than if...else...
      if (SearchWayFool(origin.back(), pieces)) // find one way
        {
          std::cout << "find one way!!!";
        }
      else
        {
          std::cout << "Sorry, we don't find a way!\n";
        }
    }
}

bool ChessBoard::RecurAgain(Piece::Coordinate current_coordinate, Piece neighbor, std::vector<Piece> pieces, bool last_origin_color, bool current_point_color)
{
  if (!neighbor.get_block() && !neighbor.get_changed()) // not be blocked and not be changed
    {
      pieces[current_coordinate.x * width + current_coordinate.y].set_changed(true);
      pieces[current_coordinate.x * width + current_coordinate.y].set_color(!current_point_color); // inverse the color
      if (NumOfConnectedDomain(pieces, last_origin_color) == 1) // there's only one connected domain
        {

        }
      else // continue to recur
        {
          return SearchWayFool(neighbor.get_coordinate(), pieces);
        }
    }
  return false;
}

bool ChessBoard::SearchWayFool(Piece::Coordinate point, std::vector<Piece> pieces)
{
  bool flag = false;; // flag == true, find a way
  Piece current_piece = pieces[point.x * width + point.y];
  bool last_origin_color = pieces[origin.back().x * width + origin.back().y].get_color();
  bool current_point_color = current_piece.get_color();

  // search for the 4-neighbor of this point
  Piece::Coordinate neighbor_up = {point.x - 1, point.y};
  Piece::Coordinate neighbor_left = {point.x, point.y - 1};
  Piece::Coordinate neighbor_down = {point.x + 1, point.y};
  Piece::Coordinate neighbor_right = {point.x, point.y + 1};

  if (neighbor_up.x >= 0) // the up neighbor
    {
      Piece neighbor = pieces[neighbor_up.x * width + neighbor_up.y];
      if (RecurAgain(point, neighbor, pieces, last_origin_color, current_point_color))
        return true;
    }
  if (neighbor_left.y >= 0) // the left neighbor
    {
      Piece neighbor = pieces[neighbor_left.x * width + neighbor_left.y];
      if (RecurAgain(point, neighbor, pieces, last_origin_color, current_point_color))
        return true;
    }
  if (neighbor_down.x < height) // the down neighbor
    {
      Piece neighbor = pieces[neighbor_down.x * width + neighbor_down.y];
      if (RecurAgain(point, neighbor, pieces, last_origin_color, current_point_color))
        return true;
    }
  if (neighbor_right.y < width) // the right neighbor
    {
      Piece neighbor = pieces[neighbor_right.x * width + neighbor_right.y];
      if (RecurAgain(point, neighbor, pieces, last_origin_color, current_point_color))
        return true;
    }
  return false;
}

int ChessBoard::NumOfConnectedDomain(std::vector<Piece> pieces, bool last_origin_color)
{
  int num = 0; // number of connected domain

  // first we should know that we find the black connected domain or white one, which depends on the color of origin.

  for(int i = 0; i < height; i++)
    for  (int j = 0; j < width; j++)
      {

      }

  return num;
}

void ChessBoard::set_num_of_around_piece()
{

}
