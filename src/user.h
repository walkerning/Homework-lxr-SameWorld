#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <vector>
#include <time.h>
#include "chess.h"
#include "piece.h"

class UserInput
{
public:
  int get_height() {return height;}
  int get_width() {return width;}
  std::vector<bool> get_color() {return color;}
  std::vector<bool> get_block() {return block;}
  std::vector<Piece::Coordinate> get_origin() {return origin;}

  void set_height(int h) {height = h;}
  void set_width(int w) {width = w;}
  void set_color(std::vector<bool> c) {color = c;}
  void set_block(std::vector<bool> b) {block = b;}
  void set_origin(std::vector<Piece::Coordinate> o) {origin = o;}

private:
  int height;
  int width;
  std::vector<bool> color;
  std::vector<bool> block;
  std::vector<Piece::Coordinate> origin;
};

#endif // USER_H_
