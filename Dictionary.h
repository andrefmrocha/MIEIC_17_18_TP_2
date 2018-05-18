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


class Dictionary {
public:
    Dictionary();
    Dictionary(std::string name);

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
    void openDict(std::string name);
    /*********************************************
    ******************getDict********************
    * The getDict method grabs the name of the
    * dictionary from the .txt stored file and
    * opens it.
    * @param iname
    */
    void getDict(std::string iname);
    std::map<std::string, std::vector<std::string>> synonymDict;
protected:
    /********************************************
    *****************toUpper********************
    * Places a whole word to capital letters.
    * @param word
     */
    void toUpper(std::string &word);

    /*********************************************************
    **********************isWordinDict***********************
    * @param word
     * @return if the word is in the Dictionary
    */
    bool isWordinDict(std::string word);
    /********************************************
    *******************randomsynDict************
    * @param word
    * @return a random synonym of the given word
    */
    std::string randomsynDict(std::string word);
    std::string dictName;
private:
    long words;
};


#endif //MIEIC_17_18_TP_2_DICTIONARY_H
