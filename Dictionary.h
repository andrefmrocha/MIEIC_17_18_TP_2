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

    /**************************************
    ******************getWords************
    * @return the number of words in the
    * dictionary
    */
	long getWords();


	/*******************************************************
    **********************openDict*************************
    * The openDict method opens a dictionary and stores
    * all of its words in map.
     * @param name
    */
    void openDict(string name);
    /*********************************************
    ******************getDict********************
    * The getDict method grabs the name of the
    * dictionary from the .txt stored file and
    * opens it.
    * @param iname
    */
    void getDict(string iname);
    map<string, vector<string>> synonymDict;
protected:
    /********************************************
    *****************toUpper********************
    * Places a whole word to capital letters.
    * @param word
     */
    void toUpper(string &word);

    /*********************************************************
    **********************isWordinDict***********************
    * @param word
     * @return if the word is in the Dictionary
    */
    bool isWordinDict(string word);
    /********************************************
    *******************randomsynDict************
    * @param word
    * @return a random synonym of the given word
    */
    string randomsynDict(string word);
    string dictName;
private:
    long words;
};


#endif //MIEIC_17_18_TP_2_DICTIONARY_H
