//
// Created by andrefmrocha on 26-04-2018.
//

#include "cwcreator.h"

int main()
{
    int a;
    cwcreator cw(10,10,"dic.txt");
    cw.addWord("AbV", "Dissemble");
    cw.board_show();
    cin >> a;
}