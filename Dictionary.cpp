//
// Created by andrefmrocha on 26-04-2018.
//

#include "Dictionary.h"

Dictionary::Dictionary()
{
    string inName;
    cout << "Please specify the name of the dictionary: ";
    cin >> inName;
    ifstream infile("dic.txt"); // Name for testing purposes
    string savingString;
    if(!infile.is_open())
    {
        cout << "File not opened";
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
        synonymDic.insert(pair<string, vector<string>>(key, synVec));
    }
}