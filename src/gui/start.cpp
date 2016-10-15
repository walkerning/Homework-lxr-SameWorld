#include "start.h"

int StartGui::ReadHistory()
{
  int level; // user is now at this level, level 0 means user plays at first time, level 1 means user pass the first level
  UserInput input; // save user's level infos

  //get the level which user stands
  std::ifstream level_file("level.txt");
  std::string level_line;
  if (level_file.is_open())
    {
      while(getline(level_file, level_line))// just one number
        {
          level = atoi(level_line.c_str());
        }
      level_file.close();
    }
  else std::cout << "Unable to open level file!!";

  // read level infos from "data.txt"
  std::ifstream data_file("data.txt"); // get levels data
  std::string line;
  int level_num = 0;

  if (data_file.is_open())
    {
      while(getline(data_file, line))
        {
          if (level_num + 1 == level)
            {
              QString qstr = QString::fromUtf8(line.c_str()); // convert string to QString
              QStringList list = qstr.split(" ", QString::SkipEmptyParts);
              // set height and width
              int height = list.at(1).toInt(); // height
              input.set_height(height);
              int width = list.at(2).toInt(); // width
              input.set_width(width);
              // set status(black, white or block)
              std::vector<int> status;
              for (int i = 0; i < input.get_height(); i++)
                for (int j = 0; j < input.get_width(); j++)
                  status.push_back(WHITE);
              QString black_pieces = list.at(3); // black pieces
              if (black_pieces != "-1") // exist black pieces
                {
                  QStringList black_pieces_index = black_pieces.split(",", QString::SkipEmptyParts);
                  for (int i = 0; i < black_pieces_index.size(); ++i)
                    status[black_pieces_index.at(i).toInt()] = BLACK;
                }
              QString block_pieces = list.at(4); // block pieces
              if (block_pieces != "-1") // exist block pieces
                {
                  QStringList block_pieces_index = block_pieces.split(",", QString::SkipEmptyParts);
                  for (int i = 0; i < block_pieces_index.size(); ++i)
                    status[block_pieces_index.at(i).toInt()] = BLOCK;
                }
              input.set_status(status);
              // set origin
              std::vector<Piece::Coordinate> origin;
              QString qorigin = list.at(5); // origin
              if (qorigin != "-1") // exist origin
                {
                  QStringList origin_index = qorigin.split(",", QString::SkipEmptyParts);
                  for (int i = 0; i < origin_index.size(); ++i)
                    {
                      int x = origin_index.at(i).toInt() / input.get_width();
                      int y = origin_index.at(i).toInt() % input.get_width();
                      Piece::Coordinate origin_point = {x, y};
                      origin.push_back(origin_point);
                    }
                  input.set_origin(origin);
                }
              break;
            }
          ++level_num;
        }
      data_file.close();
    }
  else std::cout << "Unable to open data file!!";

  return level;
  //return input;
}

void StartGui::OpenLevelPage()
{



}

void StartGui::CustomizeGame()
{
  // show a widget which lets user to select height and width first



  // show another widget which lets user to define pieces' status(black, white or block)




  // after design, user should click "ok", then computer will compute whether this new game has a solution or not. QMessage: No solution: "sorry this game doesn't has a solution", otherwise: "Congratulation! Your new game is created! Just try!"


}
