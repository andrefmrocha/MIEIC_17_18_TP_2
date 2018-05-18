//
// Created by andrefmrocha on 26-04-2018.
//
#include "Dictionary.h"
using namespace std;

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
    ifstream infile(name); //Opens the file
    string savingString;
    if(!infile.is_open()) //Checks if the file was opened
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
                if(i == ':') //When a ':' is found, it means our keyword was found
                {
//                toUpper(savingWord);
                    key = savingWord;
                    savingWord.clear();
                }
                if (i == ',' || i == '\r') //When a ',' or the end of the line is found
                {                          // The word is stored as another synonym
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
            words++;
            synonymDict.insert(pair<string, vector<string>>(key, synVec)); //The word and its synonyms are stored
        }
    }
    dictName = name; //The name of the dictionary used is stored
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
    vector<string> synonymVec = synonymDict[word]; //The vector of synonyms is grabbed
    srand(time(NULL));
    size_t index = rand() % synonymVec.size(); //A random index from it is chosen
    return synonymVec[index]; //The synonym is returned
}


void Dictionary::getDict(string iname)
{
    ifstream infile(iname);
    string dictName;
    getline(infile, dictName);
    openDict(dictName);
}
