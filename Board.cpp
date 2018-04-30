//
// Created by joaom on 26-04-2018.
//

#include "Board.h"

 Board::Board(unsigned int lines, unsigned int columns) {
    this->lines=lines;
    this->columns=columns;
    vector<char> cenas;
     for (int i = 0; i < columns; i++) {
        cenas.push_back('.');
    }
    for (int j = 0; j < lines; j++){
        board.push_back(cenas);
    }
}

void Board::board_show() {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            cout << board.at(i).at(j) << "  ";
        }
        cout << endl;
    }
}
