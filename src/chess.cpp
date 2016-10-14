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
      pieces[Coordinate2Index(current_coordinate)].set_changed(true);
      pieces[Coordinate2Index(current_coordinate)].set_status(BLACK + WHITE - current_point_status); // inverse the color, 1->2, 2->1
      if (get_num_of_connected_domain(pieces, last_origin_status) == 1) // there's only one connected domain
        {
          // compute the attribute <num_of_around_piece>
          int num_of_remaining_pieces = set_num_of_around_piece(pieces, last_origin_status);
          Piece::Coordinate start_coordinate = origin.back();
          int status = pieces[Coordinate2Index(start_coordinate)].get_status();
          return SearchWayFoolStep2(num_of_remaining_pieces, pieces, start_coordinate, status);
        }
      else // continue to recur
        {
          return SearchWayFool(neighbor.get_coordinate(), pieces);
        }
    }
  return false;
}

bool ChessBoard::SearchWayFoolStep2(int num_of_remaining_pieces, std::vector<Piece> pieces, Piece::Coordinate current_coordinate, int current_status)
{
  Piece::Coordinate offset[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
  Piece::Coordinate possible_next_piece;
  int current_index = Coordinate2Index(current_coordinate);
  int valid_neighbor = 0;
  int attribute_neighbor = 0;// number of neighbor which <num_of_around_piece> is 1
  for(int k = 0; k < 4; k++)
    {
      Piece::Coordinate neighbor_coordinate = {current_coordinate.x + offset[k].x, current_coordinate.y + offset[k].y};
      if (valid(neighbor_coordinate) && pieces[Coordinate2Index(neighbor_coordinate)].get_status() == current_status)
        {
          valid_neighbor++;
          if(pieces[Coordinate2Index(neighbor_coordinate)].get_num_of_around_piece() == 1)
            {
              attribute_neighbor++;
              possible_next_piece.x = current_coordinate.x + offset[k].x;
              possible_next_piece.y = current_coordinate.y + offset[k].y;
            }
        }
    }
  if (valid_neighbor == 0) // no way to go
    {
      if (num_of_remaining_pieces == 1) // only remain itself
        return true;
      else return false;
    }
  if (attribute_neighbor >= 2) return false;
  else
    {
      // change color
      pieces[current_index].set_status(BLACK + WHITE - pieces[current_index].get_status());
      // modify the num_of_remaining_pieces of his neighbors
      for(int k = 0; k < 4; k++)
        {
          Piece::Coordinate neighbor_coordinate = {current_coordinate.x + offset[k].x, current_coordinate.y + offset[k].y};
          if (valid(neighbor_coordinate) && pieces[Coordinate2Index(neighbor_coordinate)].get_status() == current_status)
            pieces[Coordinate2Index(neighbor_coordinate)].set_num_of_around_piece(pieces[Coordinate2Index(neighbor_coordinate)].get_num_of_around_piece() - 1);
        }

      if (attribute_neighbor == 1) return SearchWayFoolStep2(num_of_remaining_pieces - 1, pieces, possible_next_piece, current_status);
      else // attribute_neighbor == 0
        {
          // search all neighbors
          for(int k = 0; k < 4; k++)
            {
              Piece::Coordinate neighbor_coordinate = {current_coordinate.x + offset[k].x, current_coordinate.y + offset[k].y};
              if (valid(neighbor_coordinate) && pieces[Coordinate2Index(neighbor_coordinate)].get_status() == current_status) // TODO: this line exists too many times in this function, we must find another way to simplify it
                {
                  bool flag = SearchWayFoolStep2(num_of_remaining_pieces - 1, pieces, neighbor_coordinate, current_status);
                  if (flag) return true;
                }
            }
          return false;
        }
    }
}

bool ChessBoard::SearchWayFool(Piece::Coordinate point, std::vector<Piece> pieces)
{
  Piece current_piece = pieces[Coordinate2Index(point)];
  int last_origin_status = pieces[Coordinate2Index(origin.back())].get_status();
  int current_point_status = current_piece.get_status();

  // search for the 4-neighbor of this point
  Piece::Coordinate neighbor_up = {point.x - 1, point.y};
  Piece::Coordinate neighbor_left = {point.x, point.y - 1};
  Piece::Coordinate neighbor_down = {point.x + 1, point.y};
  Piece::Coordinate neighbor_right = {point.x, point.y + 1};

  //TODO: maybe can merge the four "if" to one "for"
  if (neighbor_up.x >= 0) // the up neighbor
    {
      Piece neighbor = pieces[Coordinate2Index(neighbor_up)];
      if (RecurAgain(point, neighbor, pieces, last_origin_status, current_point_status))
        return true;
    }
  if (neighbor_left.y >= 0) // the left neighbor
    {
      Piece neighbor = pieces[Coordinate2Index(neighbor_left)];
      if (RecurAgain(point, neighbor, pieces, last_origin_status, current_point_status))
        return true;
    }
  if (neighbor_down.x < height) // the down neighbor
    {
      Piece neighbor = pieces[Coordinate2Index(neighbor_down)];
      if (RecurAgain(point, neighbor, pieces, last_origin_status, current_point_status))
        return true;
    }
  if (neighbor_right.y < width) // the right neighbor
    {
      Piece neighbor = pieces[Coordinate2Index(neighbor_right)];
      if (RecurAgain(point, neighbor, pieces, last_origin_status, current_point_status))
        return true;
    }
  return false;
}

int ChessBoard::get_num_of_connected_domain(std::vector<Piece> pieces, int last_origin_status)
{
  int num = 0; // number of connected domain
  // warning: you should consider the block situation

  std::vector<bool> is_traversed; // true: this piece is traversed
  for(int i = 0; i < height; i++)
    for  (int j = 0; j < width; j++)
      is_traversed.push_back(false); // to begin with, all pieces are not be traversed

  // use queue searching connected domain
  std::queue<Piece> piece_queue;
  for(int i = 0; i < height; i++)
    for  (int j = 0; j < width; j++)
      {
        if (!is_traversed[i * width + j] && pieces[i * width + j].get_status() == last_origin_status) // find the first right piece
          {
            piece_queue.push(pieces[i * width + j]); // push the first piece in queue
            is_traversed[i * width + j] = true;
            while(!piece_queue.empty())
              {
                Piece current_piece = piece_queue.front(); // get one piece from the head of the queue
                // add its neighbor to the tail of this queue(4-neighbor)
                Piece::Coordinate offset[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
                Piece::Coordinate current_coordinate = current_piece.get_coordinate();
                for (int k = 0; k < 4; k++)
                  {
                    Piece::Coordinate neighbor_coordinate = {current_coordinate.x + offset[k].x, current_coordinate.y + offset[k].y};
                    if (valid(neighbor_coordinate) && !is_traversed[Coordinate2Index(neighbor_coordinate)] && pieces[Coordinate2Index(neighbor_coordinate)].get_status() == last_origin_status)
                      {
                        piece_queue.push(pieces[Coordinate2Index(neighbor_coordinate)]); // push the first piece in queue
                        is_traversed[Coordinate2Index(neighbor_coordinate)] = true;
                      }
                  }
                piece_queue.pop(); // delete this piece
              }
            num++;
          }
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
            pieces[i * width + j].set_changed(false);
            // traverse four neighbors of this piece
            for (int k = 0; k < 4; k++)
              {
                Piece::Coordinate neighbor = {pieces[i * width + j].get_coordinate().x + offset[k].x, pieces[i * width + j].get_coordinate().y + offset[k].y};
                if (valid(neighbor) && pieces[Coordinate2Index(neighbor)].get_status() == last_origin_status) // the coordinate is valid && not blocked && color the same
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

int ChessBoard::Coordinate2Index(Piece::Coordinate coordinate)
{
  return coordinate.x * width + coordinate.y;
}
