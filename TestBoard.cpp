//
// Created by joaom on 26-04-2018.
//
#include "stdafx.h"
#include "cwcreator.h"
int main ()
{
    cwcreator b1 (7, 4);
//    b1.board_show();
    b1.addWord("AbV", "Meia");
    b1.addWord("BaH", "Meia");
    b1.board_show();
/*    b1.eraseWord("Fuck");
    b1.board_show();*/
	b1.board_save("balas.txt");
}