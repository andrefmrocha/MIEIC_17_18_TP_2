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
    bool addWord(string position, string word);
    void eraseWord(string word);

protected:
    int lines;
    int columns;
    vector<vector <char>> board;

private:
    void clear();
    void writeAllWords();
    void writeWord(string position, string word);
    vector<pair<string, string>> wordPos;
};


#endif //PROJETO_2_BOARD_H
