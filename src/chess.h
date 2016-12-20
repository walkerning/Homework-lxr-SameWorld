#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <time.h>

#include "piece.h" // include piece class
#include "user.h" // include user class

#define WHITE 1
#define BLACK 2
#define BLOCK 3

class ChessStatus;

class ChessBoard // chessboard class
{
 public:
 ChessBoard(UserInput input): height(input.get_height()), width(input.get_width()), origin(input.get_origin())
    {
      std::vector<int> status_list = input.get_status();
      for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
          {
            Piece::Coordinate coordinate = {i, j};
            Piece piece(status_list[i * width + j], coordinate);
            pieces.push_back(piece);
          }
    }
  int Height() { return height; }
  int Width() { return width; }
  const std::vector<Piece::Coordinate>& Origin() { return origin; }
  const std::vector<Piece>& Pieces() { return pieces; }
  void Start();

  bool SearchWayFool(ChessStatus one_status); // use a foolish method to search for the right way, point is the current piece, pieces is the status of all pieces on the chessboard now
  bool SearchWayFoolStep2(int num_of_remaining_pieces, std::vector<Piece> pieces, Piece::Coordinate current_coordinate, int current_status); // search in the second step

  int get_num_of_connected_domain(std::vector<Piece> pieces, int last_origin_status); // find connected domain
  int set_num_of_around_piece(std::vector<Piece> pieces, int last_origin_status); // in the 2. step, set the nunmber of around pieces, return number of pieces in this connected domain
  void PrintResult(std::vector<int> pieces);

  // test functions
  void TestConnectedDomain() {std::cout << get_num_of_connected_domain(pieces, BLACK)<< std::endl;}

  void PrintVector(std::vector<int> a) {
    for (int i = 0; i < a.size(); ++i)
      std::cout << a[i] << "  ";
    std::cout << std::endl;
  }

 private:
  int height; //height of chessboard
  int width; // width of chessboard
  std::vector<Piece> pieces; // all pieces on the chessboard
  std::vector<Piece::Coordinate> origin; //several starting points
  int last_origin_status;

  bool valid(int index); // verify a coordinate valid or not
  int Coordinate2Index(Piece::Coordinate coordinate); // convert coordinate to index
  int NumOfChangedPieces(std::vector<Piece> pieces);

  std::stack<Piece> result; // save the result in order to detect
  std::vector<ChessStatus> chess_status; // status of chess, use one list to store because of its order
};

//use g+h to sort
class ChessStatus
{
 public:
 ChessStatus(std::vector<Piece> pieces, int g, int h, bool step, Piece::Coordinate origin, std::vector<int> way): pieces(pieces), g(g), h(h), step(step), origin(origin), way(way) {}
  std::vector<Piece> pieces; // height * width
  int g; // g function, number of all changed pieces, call NumOfChangedPieces
  int h; // h function, if no connected domain ,h = 1, else h = 0
  bool step; // 1: step 1, 0: step 2
  Piece::Coordinate origin; //  index of origin of this status
  std::vector<int> way; // changed color
};

struct by_g_plus_h {
    bool operator()(ChessStatus const &a, ChessStatus const &b) {
        return a.g + a.h < b.g + b.h;
    }
};

#endif // CHESSBOARD_H_
