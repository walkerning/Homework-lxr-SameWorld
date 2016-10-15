#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <vector>
#include <time.h>
#include "piece.h"

class UserInput
{
public:
  int get_height() {return height;}
  int get_width() {return width;}
  std::vector<int> get_status() {return status;}
  std::vector<Piece::Coordinate> get_origin() {return origin;}

  void set_height(int h) {height = h;}
  void set_width(int w) {width = w;}
  void set_status(std::vector<int> s) {status = s;}
  void set_origin(std::vector<Piece::Coordinate> o) {origin = o;}

private:
  int height;
  int width;
  std::vector<int> status;
  std::vector<Piece::Coordinate> origin;
};

#endif // USER_H_
