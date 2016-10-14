#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include <iostream>
#include <vector>
#include <time.h>

#include "piece.h" // include piece class
#include "user.h" // include user class

#define WHITE 1
#define BLACK 2
#define BLOCK 3

class ChessBoard // chessboard class
{
 public:
 ChessBoard(UserInput input): height(input.get_height()), width(input.get_width()), origin(input.get_origin())
    {
      for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
          {
            Piece::Coordinate coordinate = {i, j};
            Piece piece(input.get_status()[i * width + j], coordinate);
            pieces.push_back(piece);
          }
    }

  void Start();
  bool SearchWayFool(Piece::Coordinate point, std::vector<Piece> pieces); // use a foolish method to search for the right way, point is the current piece, pieces is the status of all pieces on the chessboard now
  bool SearchWayFoolStep2(int num_of_remaining_pieces); // search in the second step

  int NumOfConnectedDomain(std::vector<Piece> pieces, int last_origin_status); // find connected domain
  int set_num_of_around_piece(std::vector<Piece> pieces, int last_origin_status); // in the 2. step, set the nunmber of around pieces, return number of pieces in this connected domain
  bool RecurAgain(Piece::Coordinate current_coordinate, Piece neighbor, std::vector<Piece> pieces, int last_origin_status, int current_point_status);

 private:
  int height; //height of chessboard
  int width; // width of chessboard
  std::vector<Piece> pieces; // all pieces on the chessboard
  std::vector<Piece::Coordinate> origin; //several starting points

  bool valid(Piece::Coordinate piece_coordinate);

};

#endif // CHESSBOARD_H_