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

protected:
    bool isWordinDict(string word) const;
    map<string, vector<string>> synonymDict;
private:
    long words;
};


#endif //MIEIC_17_18_TP_2_DICTIONARY_H
