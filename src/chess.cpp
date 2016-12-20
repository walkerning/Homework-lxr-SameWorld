#include "chess.h"

void ChessBoard::Start()
{
  // first version: only support two origin points
  // get a origin randomly
  Piece::Coordinate first_origin = origin.front();
  pieces[Coordinate2Index(first_origin)].set_changed(true);
  pieces[Coordinate2Index(first_origin)].set_status(BLACK + WHITE - pieces[Coordinate2Index(first_origin)].get_status()); // inverse the origin color, 1->2, 2->1
  std::vector<int> way;
  way.push_back(Coordinate2Index(first_origin));
  ChessStatus one_status(pieces, 1, 0, true, first_origin, way);
  chess_status.push_back(one_status); // push in the chess_status
  if (SearchWayFool(one_status)) // find one way
    {
      std::cout << "find one way!!!1\n";
    }
  else // use another origin
    {
      //TODO: detect symmetry to avoid recurring the second origin
      //TODO: if we have three origins or more, use a circulate rather than if...else...
      Piece::Coordinate last_origin = origin.back();
      std::cout <<"back" << origin.back().x << origin.back().y;
      pieces[Coordinate2Index(last_origin)].set_changed(true);
      pieces[Coordinate2Index(last_origin)].set_status(BLACK + WHITE - pieces[Coordinate2Index(last_origin)].get_status()); // inverse the origins color, 1->2, 2->1
      std::vector<int> way;
      way.push_back(Coordinate2Index(last_origin));
      ChessStatus one_status(pieces, 1, 0, true, last_origin, way);
      chess_status.push_back(one_status); // push in the chess_status
      if (SearchWayFool(one_status)) // find one way
        {
          std::cout << "find one way!!!2\n";
        }
      else
        {
          std::cout << "Sorry, we don't find a way!\n";
        }
    }
}

bool ChessBoard::SearchWayFoolStep2(int num_of_remaining_pieces, std::vector<Piece> pieces, Piece::Coordinate current_coordinate, int current_status)
{
  Piece::Coordinate offset[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
  Piece::Coordinate possible_next_piece;

  int current_index = Coordinate2Index(current_coordinate);
  result.push(pieces[current_index]);
  int valid_neighbor = 0;
  int attribute_neighbor = 0;// number of neighbor which <num_of_around_piece> is 1
  // compute valid neighbor and attribute neighbor
  for(int k = 0; k < 4; k++)
    {
      Piece::Coordinate neighbor_coordinate = current_coordinate + offset[k];
      if (valid(Coordinate2Index(neighbor_coordinate)) && pieces[Coordinate2Index(neighbor_coordinate)].get_status() == current_status)
        {
          valid_neighbor++;
          if(pieces[Coordinate2Index(neighbor_coordinate)].get_num_of_around_piece() == 1)
            {
              attribute_neighbor++;
              possible_next_piece = current_coordinate + offset[k];
            }
        }
    }
  if (valid_neighbor == 0) // no way to go
    {
      if (num_of_remaining_pieces == 1) // only remain itself
        return true;
      else
        {
          result.pop();
          return false;
        }
    }
  if (attribute_neighbor >= 2)
    {
      result.pop();
      return false;
    }
  else
    {
      // change color
      pieces[current_index].set_status(BLACK + WHITE - pieces[current_index].get_status());
      // modify the num_of_remaining_pieces of his neighbors
      for(int k = 0; k < 4; k++)
        {
          Piece::Coordinate neighbor_coordinate = current_coordinate + offset[k];
          if (valid(Coordinate2Index(neighbor_coordinate)) && pieces[Coordinate2Index(neighbor_coordinate)].get_status() == current_status)
            pieces[Coordinate2Index(neighbor_coordinate)].set_num_of_around_piece(pieces[Coordinate2Index(neighbor_coordinate)].get_num_of_around_piece() - 1);
        }

      if (attribute_neighbor == 1)
        {
          if (SearchWayFoolStep2(num_of_remaining_pieces - 1, pieces, possible_next_piece, current_status))
            {
              return true;
            }
          else
            {
              result.pop();
              return false;
            }
        }

      else // attribute_neighbor == 0
        {
          // search all neighbors
          for(int k = 0; k < 4; k++)
            {
              Piece::Coordinate neighbor_coordinate = current_coordinate + offset[k];
              if (valid(Coordinate2Index(neighbor_coordinate)) && pieces[Coordinate2Index(neighbor_coordinate)].get_status() == current_status) // TODO: this line exists too many times in this function, we must find another way to simplify it
                {
                  result.push(pieces[Coordinate2Index(neighbor_coordinate)]);
                  bool flag = SearchWayFoolStep2(num_of_remaining_pieces - 1, pieces, neighbor_coordinate, current_status);
                  if (flag) return true;
                  else result.pop();
                }
            }
          result.pop();
          return false;
        }
    }
}

bool ChessBoard::SearchWayFool(ChessStatus one_status)
{
  // start to iterate
  if (one_status.step == true) // step 1
    {
      std::cout <<"step1    ";
      // compute this connected domain is 1 or not
      int domain_num = get_num_of_connected_domain(one_status.pieces, last_origin_status);
      if (domain_num == 1)
        {
          // go to step 2
          int index = Coordinate2Index(origin.back());
          one_status.pieces[index].set_changed(true);
          one_status.pieces[index].set_status(BLACK + WHITE - one_status.pieces[index].get_status());
          std::vector<int> way;
          for (int i = 0; i < one_status.way.size(); i++)
            way.push_back(one_status.way[i]);
          way.push_back(index);
          ChessStatus new_status(one_status.pieces, NumOfChangedPieces(one_status.pieces), 0, 0, origin.back(), way);// but don't change record last origin color
          chess_status.push_back(new_status);
          std::cout << "domain is 1\n";
          std::cout << NumOfChangedPieces(one_status.pieces) << std::endl;
        }
      //pop this chess_status
      chess_status.erase(chess_status.begin()); // remove the first element
      // search for all neighbors of this origin
      Piece::Coordinate offset[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
      for (int k = 0; k < 4; k++)
        {
          Piece::Coordinate neighbor_coordinate = one_status.origin + offset[k];
          int neighbor_index = Coordinate2Index(neighbor_coordinate);
          Piece neighbor = one_status.pieces[neighbor_index];
          if (valid(neighbor_index) && one_status.pieces[neighbor_index].get_status() != BLOCK && !one_status.pieces[neighbor_index].get_changed()) // valid coordinate && not block && not changed
            {
              std::cout << neighbor_index << " b ";
              // traverse neighbor's color
              bool origin_change = false;
              // this piece is the last_origin
              if (one_status.pieces[neighbor_index].get_coordinate() == origin.back())
                origin_change = true;
              one_status.pieces[neighbor_index].set_changed(true);
              one_status.pieces[neighbor_index].set_status(BLACK + WHITE - one_status.pieces[neighbor_index].get_status());
              // create a new ChessStatus
              int num_of_changes_pieces = NumOfChangedPieces(one_status.pieces);
              if (origin_change)
                {
                  last_origin_status = BLACK + WHITE - last_origin_status; // change color
                  std::vector<int> way;
                  for (int i = 0; i < one_status.way.size(); i++)
                    {  way.push_back(one_status.way[i]);
                      std::cout << way[i] << "   a ";
                    }
                  way.push_back(neighbor_index);
                  ChessStatus new_status(one_status.pieces, num_of_changes_pieces, 1, 1, neighbor_coordinate, way);
                  // put this new ChessStatus into chess_status vector
                  chess_status.push_back(new_status);
                }
              else
                {
                  std::vector<int> way;
                  for (int i = 0; i < one_status.way.size(); i++)
                    way.push_back(one_status.way[i]);
                  way.push_back(neighbor_index);
                  ChessStatus new_status(one_status.pieces, num_of_changes_pieces, 5, 1, neighbor_coordinate, way);
                  // put this new ChessStatus into chess_status vector
                  chess_status.push_back(new_status);
                }
              // sort according g+h to decide which is the next status
            }
        }
      if (chess_status.empty()) // no number
        {
          return false;
        }
      std::sort(chess_status.begin(), chess_status.end(), by_g_plus_h()); // from small to big
      SearchWayFool(chess_status[0]);
    }
  else // step 2
    {
      std::cout <<"step2   ";
      chess_status.erase(chess_status.begin()); // remove the first element
      int number = 0; // number of pieces whose status is like the origin now
      for (int i = 0; i < one_status.pieces.size(); ++i)
        {
          if (one_status.pieces[i].get_status() == last_origin_status)
            ++number;
        }
      if (number == 0)
        {
          PrintResult(one_status.way);
          return true;
        }

      //pop this chess_status
      chess_status.erase(chess_status.begin()); // remove the first element
      // search for all neighbors of this origin
      Piece::Coordinate offset[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
      for (int k = 0; k < 4; k++)
        {
          Piece::Coordinate neighbor_coordinate = one_status.origin + offset[k];
          int neighbor_index = Coordinate2Index(neighbor_coordinate);
          Piece neighbor = one_status.pieces[neighbor_index];
          if (valid(neighbor_index) && one_status.pieces[neighbor_index].get_status() == last_origin_status) // valid coordinate && same color
            {
              one_status.pieces[neighbor_index].set_changed(true);
              one_status.pieces[neighbor_index].set_status(BLACK + WHITE - one_status.pieces[neighbor_index].get_status());
              std::vector<int> way;
              for (int i = 0; i < one_status.way.size(); i++)
                way.push_back(one_status.way[i]);
              way.push_back(neighbor_index);
              ChessStatus new_status(one_status.pieces, number - 1, 0, 0, neighbor_coordinate, way);
              // put this new ChessStatus into chess_status vector
              chess_status.push_back(new_status);
            }
        }
      if (chess_status.empty()) // no number
        {
          return false;
        }
      std::sort(chess_status.begin(), chess_status.end(), by_g_plus_h()); // from small to big
      SearchWayFool(chess_status[0]);
    }
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
                    Piece::Coordinate neighbor_coordinate = current_coordinate + offset[k];
                    if (valid(Coordinate2Index(neighbor_coordinate)) && !is_traversed[Coordinate2Index(neighbor_coordinate)] && pieces[Coordinate2Index(neighbor_coordinate)].get_status() == last_origin_status)
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
                Piece::Coordinate neighbor = pieces[i * width + j].get_coordinate() + offset[k];
                if (valid(Coordinate2Index(neighbor)) && pieces[Coordinate2Index(neighbor)].get_status() == last_origin_status) // the coordinate is valid && not blocked && color the same
                  pieces[i * width + j].set_num_of_around_piece(pieces[i * width + j].get_num_of_around_piece() + 1);
              }
          }
      }
  return num;
}


bool ChessBoard::valid(int index) // whether a coordinate valid or not
{
  if (index >= 0 && index < height * width)
    return true;
  else return false;
}

int ChessBoard::Coordinate2Index(Piece::Coordinate coordinate)
{
  return coordinate.x * width + coordinate.y;
}

void ChessBoard::PrintResult(std::vector<int> way_result)
{
  std::cout << "begin print result\n";
  for (int i = 0; i < way_result.size(); ++i)
    {
      std::cout << way_result.front() << " ";
      way_result.pop_back();
    }
  std::cout << "size:  " << way_result.size() << std::endl;
}

int ChessBoard::NumOfChangedPieces(std::vector<Piece> pieces)
{
  int num = 0;
  for (size_t i = 0; i < pieces.size(); ++i)
    {
      if (pieces[i].get_changed() == true) ++num;
    }
  return num;
}
