//
// Created by joaom on 26-04-2018.
//

#ifndef PROJETO_2_BOARD_H
#define PROJETO_2_BOARD_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Board {
public:
    Board();
    Board(unsigned int lines, unsigned int columns);
   void board_show();
private:
    int lines;
    int columns;
    vector<vector <char>> board;
};


#endif //PROJETO_2_BOARD_H
