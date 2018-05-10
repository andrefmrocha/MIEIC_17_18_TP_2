//
// Created by joaom on 26-04-2018.
//

#ifndef PROJETO_2_BOARD_H
#define PROJETO_2_BOARD_H
#ifdef __unix__
// UNIX specific
#include "unix_colors.h"
#else 
// WINDOWS specific
#include "windows_colors.h"
#endif
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Board {
public:
    Board();
    Board(unsigned int lines, unsigned int columns);
    void resizeBoard(unsigned int lines, unsigned int columns);
    void finishBoard();
    bool positionalCheck(string position);
    void board_show();
    bool eraseWord(string word);
    bool readFile(string iname);
	void fillBoard();
protected:
    int lines;
    int columns;
    vector<vector <char>> board;
    vector<pair<string, string>> wordPos;
    void writeAllWords();
    void clear();
    int countLine(string savingString);
    
	bool finished;
private:
    
    void writeWord(string position, string word);
};


#endif //PROJETO_2_BOARD_H
