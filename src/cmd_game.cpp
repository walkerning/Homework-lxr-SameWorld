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

  // set status(no block)
  std::vector<int> status;
  for (int i = 0; i < input.get_height(); i++)
    for (int j = 0; j < input.get_width(); j++)
      status.push_back(WHITE);
  status[4] = BLACK;
  status[5] = BLACK;
  status[7] = BLACK;
  status[8] = BLACK;
  status[10] = BLACK;
  status[11] = BLACK;
  input.set_status(status);

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
  chess_board.PrintResult();
  return 0;
}
