//
// Created by andrefmrocha on 26-04-2018.
//
#include "stdafx.h"
#include "Dictionary.h"
//looool
Dictionary::Dictionary()
{
    dictName = "0";
}
Dictionary::Dictionary(string name)
{
    openDict(name);
}
void Dictionary::openDict(string name)
{
    ifstream infile(name);
    string savingString;
    if(!infile.is_open())
    {
        cout << endl << "File not opened" << endl;
        words = -1;
    }
    else
    {
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
            if(!savingWord.empty() && savingWord != "\r")
            {
                toUpper(savingWord);
                synVec.push_back(savingWord);
            }
//        synVec.push_back(savingWord);
            synonymDict.insert(pair<string, vector<string>>(key, synVec));
        }
    }
    dictName = name;
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

long Dictionary::getWords() {
	return words;
}

string Dictionary::randomsynDict(string word)
{
    vector<string> synonymVec = synonymDict[word];
    srand(time(NULL));
    size_t index = rand() % synonymVec.size();
    return synonymVec[index];
}