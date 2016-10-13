#include <iostream>
#include <vector>
#include <time.h>

#include "chess.h"
#include "user.h"

UserInput initial()
{
  UserInput input;
  input.set_height(4);
  input.set_width(4);

  // set color
  std::vector<bool> color;
  for (int i = 0; i < input.get_height(); i++)
    for (int j = 0; j < input.get_width(); j++)
      color.push_back(true);
  color[4] = false;
  color[5] = false;
  color[7] = false;
  color[8] = false;
  color[10] = false;
  color[11] = false;
  input.set_color(color);

  //set block
  std::vector<bool> block;
  for (int i = 0; i < input.get_height(); i++)
    for (int j = 0; j < input.get_width(); j++)
      block.push_back(false); // no block
  input.set_block(block);

  //set origin
  std::vector<Piece::Coordinate> origin;
  Piece::Coordinate origin_point = {2, 0}, origin_point2 = {1, 3};
  origin.push_back(origin_point);
  origin.push_back(origin_point2);
  input.set_origin(origin);

  return input;
}

int main()
{
  UserInput input = initial();
  ChessBoard chess_board(input); // initial a chess board
  chess_board.Start();
  return 0;
}
