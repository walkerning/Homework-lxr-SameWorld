#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include <iostream>
#include <vector>
#include <time.h>

#include "piece.h" // include piece class
#include "user.h" // include user class

class ChessBoard // chessboard class
{
 public:
 ChessBoard(UserInput input): height(input.get_height()), width(input.get_width()), origin(input.get_origin())
    {
      for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
          {
            Piece::Coordinate coordinate = {i, j};
            Piece piece(input.get_block()[i * width + j], input.get_color()[i * width + j], coordinate);
            pieces.push_back(piece);
          }
    }

  void Start();
  bool SearchWayFool(Piece::Coordinate point, std::vector<Piece> pieces); // use a foolish method to search for the right way, point is the current piece, pieces is the status of all pieces on the chessboard now

  int NumOfConnectedDomain(std::vector<Piece> pieces, bool last_origin_color); // find connected domain
  void set_num_of_around_piece(); // in the 2. step, set the nunmber of around pieces
  bool RecurAgain(Piece::Coordinate current_coordinate, Piece neighbor, std::vector<Piece> pieces, bool last_origin_color, bool current_point_color);

 private:
  int height; //height of chessboard
  int width; // width of chessboard
  std::vector<Piece> pieces;
  std::vector<Piece::Coordinate> origin; //several starting points


};

#endif // CHESSBOARD_H_
