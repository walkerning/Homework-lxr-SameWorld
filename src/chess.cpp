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

bool ChessBoard::RecurAgain(Piece::Coordinate current_coordinate, Piece neighbor, std::vector<Piece> pieces, int last_origin_status, int current_point_status)
{
  if (neighbor.get_status() != BLOCK && !neighbor.get_changed()) // not be blocked and not be changed
    {
      pieces[current_coordinate.x * width + current_coordinate.y].set_changed(true);
      pieces[current_coordinate.x * width + current_coordinate.y].set_status(BLACK + WHITE - current_point_status); // inverse the color, 1->2, 2->1
      if (NumOfConnectedDomain(pieces, last_origin_status) == 1) // there's only one connected domain
        {
          // compute the attribute <num_of_around_piece>
          int num_of_remaining_pieces = set_num_of_around_piece(pieces, last_origin_status);
          Piece::Coordinate start_coordinate = origin.back();







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
  Piece current_piece = pieces[point.x * width + point.y];
  int last_origin_status = pieces[origin.back().x * width + origin.back().y].get_status();
  int current_point_status = current_piece.get_status();

  // search for the 4-neighbor of this point
  Piece::Coordinate neighbor_up = {point.x - 1, point.y};
  Piece::Coordinate neighbor_left = {point.x, point.y - 1};
  Piece::Coordinate neighbor_down = {point.x + 1, point.y};
  Piece::Coordinate neighbor_right = {point.x, point.y + 1};

  //TODO: maybe can merge the four "if" to one "for"
  if (neighbor_up.x >= 0) // the up neighbor
    {
      Piece neighbor = pieces[neighbor_up.x * width + neighbor_up.y];
      if (RecurAgain(point, neighbor, pieces, last_origin_status, current_point_status))
        return true;
    }
  if (neighbor_left.y >= 0) // the left neighbor
    {
      Piece neighbor = pieces[neighbor_left.x * width + neighbor_left.y];
      if (RecurAgain(point, neighbor, pieces, last_origin_status, current_point_status))
        return true;
    }
  if (neighbor_down.x < height) // the down neighbor
    {
      Piece neighbor = pieces[neighbor_down.x * width + neighbor_down.y];
      if (RecurAgain(point, neighbor, pieces, last_origin_status, current_point_status))
        return true;
    }
  if (neighbor_right.y < width) // the right neighbor
    {
      Piece neighbor = pieces[neighbor_right.x * width + neighbor_right.y];
      if (RecurAgain(point, neighbor, pieces, last_origin_status, current_point_status))
        return true;
    }
  return false;
}

int ChessBoard::NumOfConnectedDomain(std::vector<Piece> pieces, int last_origin_status)
{
  int num = 0; // number of connected domain

  // first we should know that we find the black connected domain or white one, which depends on the color of origin.

  for(int i = 0; i < height; i++)
    for  (int j = 0; j < width; j++)
      {

      }

  return num;
}

int ChessBoard::set_num_of_around_piece(std::vector<Piece> pieces, int last_origin_status)
{
  int num = 0; // the number of pieces in the connected domain
  Piece::Coordinate offset[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      {
        if (pieces[i * width + j].get_status() == last_origin_status) // because last_origin_status != BLOCK certainly(restraint during user input), this operation also get rid of the situation that piece is blocked.
          {
            num++;
            // traverse four neighbors of this piece
            for (int k = 0; k < 4; k++)
              {
                Piece::Coordinate neighbor = {pieces[i * width + j].get_coordinate().x + offset[k].x, pieces[i * width + j].get_coordinate().y + offset[k].y};
                if (valid(neighbor) && pieces[neighbor.x * width + neighbor.y].get_status() == last_origin_status) // the coordinate is valid && not blocked && color the same
                  pieces[i * width + j].set_num_of_around_piece(pieces[i * width + j].get_num_of_around_piece() + 1);
              }
          }
      }
  return num;
}


bool ChessBoard::valid(Piece::Coordinate piece_coordinate) // whether a coordinate valid or not
{
  if (piece_coordinate.x >= 0 && piece_coordinate.x < height && piece_coordinate.y >= 0 && piece_coordinate.y < width)
    return true;
  else return false;
}
