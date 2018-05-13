//
// Created by andrefmrocha on 02-05-2018.
//

#ifndef MIEIC_17_18_TP_2_CWCREATOR_H
#define MIEIC_17_18_TP_2_CWCREATOR_H


#include "Board.h"
#include "Dictionary.h"
#include <ctime>

class cwcreator: public Board, public Dictionary
{
public:
	cwcreator() :Dictionary(), Board() {};
    cwcreator(int lines, int columns, string infile): Board(lines,columns), Dictionary(infile){};
	bool addWord(string position, string word);
    bool helpWord(string position);
	string getDictName();
	void board_save();
	string getBoardName();
	
private:
    bool wildcardMatch(const char *str, const char *strWild);
    void wildcardWords(string word, vector<string> &possiblewords);

};


#endif //MIEIC_17_18_TP_2_CWCREATOR_H
