//
// Created by andrefmrocha on 02-05-2018.
//

#ifndef MIEIC_17_18_TP_2_CWCREATOR_H
#define MIEIC_17_18_TP_2_CWCREATOR_H


#include "Board.h"
#include "Dictionary.h"
#include <ctime>

class cwcreator: public Board, public Dictionary
{
public:
	cwcreator() :Dictionary(), Board() {};
    cwcreator(int lines, int columns, string infile): Board(lines,columns), Dictionary(infile){};
    /*************************************************************
    * ******************** addWord ******************************
    * addWord method has the purpose of checking if a word is valid for the given position by the user
    * A word is never added to the board itself, it is stored on our vector of pairs where we only store the word and the string
    * related to its position
    * @param position
    * @param word
    * @return true if word
    * is valid for the selected position
    */
	bool addWord(string position, string word);
    /************************************************
    **********************helpWord******************
    * The helpWord method is used to check for
    * possible words to be used in the given space
    * @param position
    * @return if it's a fitting position
    */
    bool helpWord(string position);
    /******************************************************************
    **************************getDictName*****************************
    * @return the name of the dictionary
    */
	string getDictName();
    /******************************************************************
    **************************board_save******************************
    * The board_save method saves the board, the dictionary and the
    * the words used in a .txt file for future use.
    */
	void board_save();
    /******************************************************************
    **************************getBoardName*****************************
    * This function will check what is the name of the board that the
    * user saves and @return it to be used in tha saving process. the name of the dictionary
    */
	string getBoardName();
    /********************************************************
    ***********************checkWords***********************
    * The checkWords method checks which words are valid
    * or not given the dictionary.
    */
	void checkWords();
	
private:
    /*****************************************************************
    ***************************wildcardMatch*************************
    * The wildcardMatch method was given in the previous work and
    * its function is to compare if a string meets the criteria given
    * by a sequence of '?', '*', or letters.
    * @param str
    * @param strWild
    * @return if a word is valid
 */
    bool wildcardMatch(const char *str, const char *strWild);
    /*********************************************************************
    *****************************wildcardWords***************************
    * The wildcardWords is used to run the wildcardMatch method through
    * all the words in the dictionary.
    * @param word
    * @param possiblewords
    */
    void wildcardWords(string word, vector<string> &possiblewords);

};


#endif //MIEIC_17_18_TP_2_CWCREATOR_H
