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
    board.addWord("CjV", "DEVOUR");
    board.finishBoard();
    board.board_save("meias.txt");
    cwplayer cw("dic.txt");
    cw.readFile("meias.txt");
    cw.startGame();
    cw.addPlayerWord("BaH", "DISSEMBLE");
    cw.addPlayerWord("CjV", "DEVOUR");
    cw.game_show();
    string a;
    cin >> a;
}
