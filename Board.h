//
// Created by joaom on 26-04-2018.
//

#ifndef PROJETO_2_BOARD_H
#define PROJETO_2_BOARD_H

#include "unix_colors.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Board {
public:
    Board();
    Board(unsigned int lines, unsigned int columns);
    void board_show();
    void writeAllWords();
    void clear();
    bool addWord(string position, string word);
    void writeWord(string position, string word);
    void eraseWord(string word);
private:
    int lines;
    int columns;
    vector<vector <char>> board;
    vector<pair<string, string>> wordPos;
};


#endif //PROJETO_2_BOARD_H
