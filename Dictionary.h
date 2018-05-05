//
// Created by andrefmrocha on 26-04-2018.
//

#ifndef MIEIC_17_18_TP_2_DICTIONARY_H
#define MIEIC_17_18_TP_2_DICTIONARY_H

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
using namespace std;

class Dictionary {
public:
    Dictionary(string name);
	long getWords();

protected:
    void toUpper(string &word);
    bool isWordinDict(string word);
    map<string, vector<string>> synonymDict;
	
private:
    long words;
};


#endif //MIEIC_17_18_TP_2_DICTIONARY_H
