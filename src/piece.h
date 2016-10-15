#ifndef PIECE_H_
#define PIECE_H_

#include <iostream>
#include <vector>
#include <time.h>

class Piece // piece class
{
 public:
  struct Coordinate
  {
    int x;
    int y;
    Coordinate operator+(Coordinate rhs)
    {
      rhs.x += x;
      rhs.y += y;
      return rhs;
    }
    //TODO: add <<
  };

 Piece(int status, Coordinate coordinate): status(status), coordinate(coordinate), changed(false), num_of_around_piece(0) {}

  // get
  int get_status() {return status;}
  bool get_changed() {return changed;}
  bool get_num_of_around_piece() {return num_of_around_piece;}
  Coordinate get_coordinate() {return coordinate;}

  // set
  void set_status(int s) {status = s;}
  void set_changed(bool ch) {changed = ch;}
  void set_num_of_around_piece(bool num) {num_of_around_piece = num;}

 private:
  int status; //status == 1, white, status == 2, black, status == 3, blocked(no piece in this square)
  bool changed; // changed == true, we have already changed his color
  int num_of_around_piece; // number of pieces around this piece(4-neighborhood) with same color, ***set in the second step***
  Coordinate coordinate; // the coordiante of the piece
};



#endif // PIECE_H_
