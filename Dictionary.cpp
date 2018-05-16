//
// Created by andrefmrocha on 26-04-2018.
//
#include "Dictionary.h"

Dictionary::Dictionary()
{
    dictName = "0";
}
Dictionary::Dictionary(string name)
{
    openDict(name);
}

/*******************************************************
 **********************openDict*************************
 * The openDict method opens a dictionary and stores
 * all of its words in map.
 * @param name
 */
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
/*********************************************************
 **********************isWordinDict***********************
 * @param word
 * @return if the word is in the Dictionary
 */
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

/********************************************
 *****************toUpper********************
 * Places a whole word to capital letters.
 * @param word
 */
void Dictionary::toUpper(string &word)
{
    for(auto &i: word)
    {
        toupper(i);
    }
}


/**************************************
 ******************getWords************
 * @return the number of words in the
 * dictionary
 */
long Dictionary::getWords() {
	return words;
}

/********************************************
 *******************randomsynDict************
 * @param word
 * @return a random synonym of the given word
 */
string Dictionary::randomsynDict(string word)
{
    vector<string> synonymVec = synonymDict[word]; //The vector of synonyms is grabbed
    srand(time(NULL));
    size_t index = rand() % synonymVec.size(); //A random index from it is chosen
    return synonymVec[index]; //The synonym is returned
}

/*********************************************
 ******************getDict********************
 * The getDict method grabs the name of the
 * dictionary from the .txt stored file and
 * opens it.
 * @param iname
 */
void Dictionary::getDict(string iname)
{
    ifstream infile(iname);
    string dictName;
    getline(infile, dictName);
    openDict(dictName);
}
