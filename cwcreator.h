//
// Created by andrefmrocha on 02-05-2018.
//

#ifndef MIEIC_17_18_TP_2_CWCREATOR_H
#define MIEIC_17_18_TP_2_CWCREATOR_H


#include "Board.h"
#include "Dictionary.h"

class cwcreator: public Board, public Dictionary
{
public:
    cwcreator(int lines, int columns, string infile): Board(lines,columns), Dictionary(infile){};
	bool addWord(string position, string word);
    bool helpWord(string position);

private:
    bool wildcardMatch(const char *str, const char *strWild);
    void wildcardWords(string word, vector<string> &possiblewords);

};


#endif //MIEIC_17_18_TP_2_CWCREATOR_H
