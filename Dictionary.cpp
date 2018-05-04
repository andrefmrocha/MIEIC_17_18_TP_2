//
// Created by andrefmrocha on 26-04-2018.
//
#include "stdafx.h"
#include "Dictionary.h"

Dictionary::Dictionary(string name)
{
    ifstream infile(name);
    string savingString;
    if(!infile.is_open())
    {
        cout << "File not opened" << endl;
        words = -1;
    }
    while(getline(infile, savingString))
    {
        if(savingString.empty())
            continue;
        string key, savingWord;
        vector<string> synVec;
        for(auto i: savingString)
        {
            if(i == ':')
            {
//                toUpper(savingWord);
                key = savingWord;
                words++;
                savingWord.clear();
            }
            if (i == ',' || i == '\r')
            {
//                toUpper(savingWord);
                synVec.push_back(savingWord);
                savingWord.clear();
            }
            if (i != ' ' && i != ',' && i != ':')
            {
                savingWord.push_back(toupper(i));
            }
        }
        if(!savingWord.empty())
        {
            toUpper(savingWord);
            synVec.push_back(savingWord);
        }
//        synVec.push_back(savingWord);
        synonymDict.insert(pair<string, vector<string>>(key, synVec));
    }
}

bool Dictionary::isWordinDict(string word)
{
//    toUpper(word);
    for(auto i: synonymDict)
    {
        if(i.first == word)
        {
            return true;
        }
    }
    return false;
}

void Dictionary::toUpper(string &word)
{
    for(auto &i: word)
    {
        toupper(i);
    }
}