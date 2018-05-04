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
                key = savingWord;
                words++;
                savingWord.clear();
            }
            if (i == ',' || i == '\r')
            {
                synVec.push_back(savingWord);
                savingWord.clear();
            }
            if (i != ' ' && i != ',' && i != ':')
            {
                savingWord.push_back(i);
            }
        }
        if(!savingWord.empty())
            synVec.push_back(savingWord);
//        synVec.push_back(savingWord);
        synonymDict.insert(pair<string, vector<string>>(key, synVec));
    }
}

bool Dictionary::isWordinDict(string word) const
{
    for(auto i: synonymDict)
    {
        if(i.first == word)
        {
            return true;
        }
    }
    return false;
}