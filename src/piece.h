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
  };
 Piece(bool block, bool color, Coordinate coordinate): block(block), color(color), changed(false), coordinate(coordinate) {}

  // get
  bool get_color() {return color;}
  bool get_block() {return block;}
  bool get_changed() {return changed;}
  bool get_num_of_around_piece() {return num_of_around_piece;}
  Coordinate get_coordinate() {return cgaoordinate;}

  // set
  void set_color(bool c) {color = c;}
  void set_block(bool b) {block = b;}
  void set_changed(bool ch) {changed = ch;}
  void set_num_of_around_piece(bool num) {num_of_around_piece = num;}

 private:
  bool block; // block == true, there is no piece here
  bool color; // color == true, white; color == false, black
  bool changed; // changed == true, we have already changed his color
  int num_of_around_piece; // number of pieces around this piece(4-neighborhood) with same color, ***set in the second step***
  Coordinate coordinate; // the coordiante of the piece
};



#endif // PIECE_H_
