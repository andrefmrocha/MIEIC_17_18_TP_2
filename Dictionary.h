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
#include <ctime>

using namespace std;

class Dictionary {
public:
    Dictionary();
    Dictionary(string name);
	long getWords();
    void openDict(string name);
    map<string, vector<string>> synonymDict;
protected:
    void toUpper(string &word);
    bool isWordinDict(string word);
    string randomsynDict(string word);
    string dictName;
private:
    long words;
};


#endif //MIEIC_17_18_TP_2_DICTIONARY_H
