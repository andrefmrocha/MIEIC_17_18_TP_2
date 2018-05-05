//
// Created by andrefmrocha on 04-05-2018.
//

#ifndef MIEIC_17_18_TP_2_CWPLAYER_H
#define MIEIC_17_18_TP_2_CWPLAYER_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Board.h"
#include "Dictionary.h"

using namespace std;

class cwplayer: public Board, public Dictionary
{
public:
    cwplayer(string name): Board(), Dictionary(name){};
    void startGame();
    bool addPlayerWord(string position, string word);
    void game_show();
private:
    void spacing(int word);
    void prepareBoard();
    void sepWords();
    vector<pair<string, string>> vertiWord;
    vector<pair<string, string>> horiWord;
    vector<pair<string, string>> userWordPos;
};


#endif //MIEIC_17_18_TP_2_CWPLAYER_H
