///////////////////////////////////////////////////////////////////////////////
// poly_exp.cpp
//
// Definitions for two algorithms:
//
// soccer_exhaustive
// soccer_dyn_prog
//
///////////////////////////////////////////////////////////////////////////////


#include "poly_exp.hpp"
#include <stdexcept> 
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>


int algorithms::soccer_exhaustive(const std::vector<std::string> field) {

  // Invalid characters in field.
  for (int i = 0; i < field.size(); i++)
  {
      for (int j = 0; j < field[i].size(); j++)
      {
          if (field[i][j] != '.' && field[i][j] != 'X')
          {
              throw std::invalid_argument("Invalid char in field.");
          }
      }
  }

  // check for zeros
  if (field.size() == 0 || field[0].size() == 0)
  {
      throw std::invalid_argument("row, col cannot be zero");
  }

  if (field[0].size() == 1 && field.size() == 1)
  {
    return 1 ? field[0][0] == '.' : 0;
  }


  // Row is too short || Row is too long.
  for (int i = 1; i < field.size(); i++)
  {
      if (field[0].size() < field[i].size() || field[0].size() > field[i].size())
      {
          throw std::invalid_argument("A row that is too short.");
      }
  }

  int tooBig = field.size() + field[0].size() - 2;
  if (tooBig > 31)
  {
      throw std::invalid_argument("Rows over 31.");
  }

  unsigned int row = size(field);
  unsigned int col = size(field[0]);
  unsigned int len = row + col - 2;
  unsigned int searchLimit = pow(2, len);
  int counter = 0;

  for (unsigned int i = 0; i < searchLimit; i++) {

    bool isInvalid = false;
    unsigned int posRow = 0, posCol = 0;
    std::vector<std::string> candidate;

    for (unsigned int j = 0; j <= len - 1; j++) {
        bool bit = (i >> j) & 1;
        if (bit == 1) {
            candidate.push_back("down");
            posRow++;
            if (posRow >= row || field[posRow][posCol] != '.') {
                isInvalid = true;
                break;
            }
        }
        else {
            candidate.push_back("right");
            posCol++;
            if (posCol >= col || field[posRow][posCol] != '.') {
                isInvalid = true;
                break;
            }

        }
    }

    if ((posRow <= row - 1 && posCol <= col - 1) && (isInvalid == false) && field[row - 1][col - 1] == '.') {
        counter++;
    }
}
  return counter;
}

int algorithms::soccer_dyn_prog(const std::vector<std::string> field) {

  // Invalid characters in field.
  for (int i = 0; i < field.size(); i++)
  {
      for (int j = 0; j < field[i].size(); j++)
      {
          if (field[i][j] != '.' && field[i][j] != 'X')
          {
              throw std::invalid_argument("Invalid char in field.");
          }
      }
  }

  // check for zeros
  if (field.size() == 0 || field[0].size() == 0)
  {
      throw std::invalid_argument("row, col cannot be zero");
  }


  // Row is too short || Row is too long.
  for (int i = 1; i < field.size(); i++)
  {
      if (field[0].size() < field[i].size() || field[0].size() > field[i].size())
      {
          throw std::invalid_argument("A row that is too short.");
      }
  }


  int r = field.size(), c = field[0].size();

  // create a 2D-matrix and initializing
  // with value 0
  std::vector<std::vector<int>> paths(r, std::vector<int>(c, 0));

  // Initializing the left corner if
  // no obstacle there
  if (field[0][0] == '.') {
    paths[0][0] = 1;
  }

  // Initializing first column of
  // the 2D matrix
  for (int i = 1; i < r; i++)
  {
    // If not obstacle
    if (field[i][0] == '.') {
      paths[i][0] = paths[i - 1][0];
    }
  }

  // Initializing first row of the 2D matrix
  for (int j = 1; j < c; j++)
   {

       // If not obstacle
       if (field[0][j] == '.') {
         paths[0][j] = paths[0][j - 1];
       }
   }

   for (int i = 1; i < r; i++)
   {
     for (int j = 1; j < c; j++)
       {
         // If current cell is not obstacle
          if (field[i][j] == '.') {
            paths[i][j] = paths[i - 1][j] + paths[i][j - 1];
           }
       }
   }

   // Returning the corner value
   // of the matrix
   return paths[r-1][c-1];

}
