//
// Created by andrefmrocha on 26-04-2018.
//

#include "cwcreator.h"
#include "cwplayer.h"

int main()
{
    cwcreator board(10,10,"dic.txt");
    board.addWord("AbV","DISSEMBLE");
    board.addWord("BaH", "DISSEMBLE");
//    board.finishBoard();
    board.board_save("meias.txt");
    cwplayer cw;
    cw.readFile("meias.txt");
    cw.board_show();
}