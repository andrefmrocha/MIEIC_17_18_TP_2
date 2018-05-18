//
// Created by andrefmrocha on 04-05-2018.
//

#ifndef MIEIC_17_18_TP_2_CWPLAYER_H
#define MIEIC_17_18_TP_2_CWPLAYER_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Board.h"
#include "Dictionary.h"

using namespace std;

class cwplayer: public Board, public Dictionary
{
public:
    cwplayer(): Board(), Dictionary(){};
	/*******************************************
 	****************startGame******************
 	* The startGame method is used to first
 	* initiliaze a game for the user to play.
 	*/
    void startGame();
	/*****************************************************************
 	**********************addPlayerWord******************************
 	* @param position
	 * @param word
 	* @return if the word was added
 	*/
    bool addPlayerWord(string position, string word);
	/******************************************
 	******************game_show***************
 	* The game_show methos shows the board to
 	* the user
 	*/
    void game_show();
	/**********************************************************
 	*********************checkBoard***************************
 	* @return if the board was currectly filled
 	*/
    bool checkBoard();
	/*******************************************************
 	***********************removePlayerWord****************
 	* The removePlayerWord method is used to remove a word
 	* from the board
 	* @param position
 	* @return
 	*/
    bool removePlayerWord(string position);
    /****************************************************
    *********************helpPlayerword*****************
    * The helpPlayerword method is used to give out a
    * synonym as help for the user.
    * @param position
    * @return
    */
	bool helpPlayerword(string position);
    /*************************************************
     ******************findPosition*******************
    * @param word
    * @return the position of a word
    */
	string findPosition(string word);
    /****************************************
    ******************getNumHints***********
    * @return the number of hints already used
    */
	int getNumHints();
    /****************************************
     *******************NumHintsInc**********
     *The method increments the number
    * of hints used.
    */
	void NumHintsInc();
private:
    /******************************************
    ******************spacing*****************
    * The spacing method is used to separate
    * words without losing organization
    * @param word
    */
    void spacing(int word);
    /*****************************************
    ****************prepareBoard*************
    * The prepareBoard method prepares the
    * the board for the beggining of the game
    */
    void prepareBoard();
    /****************************************
    **************sepWords******************
    * The sepWords method is used to separate
    * words into 2 groups: horizontal and
    * vertical ones.
    */
    void sepWords();
    /********************************************************
    **********************removeWord************************
    * The removeWord method replaces all the spaces with
    * characters with dots.
    * @param position
    * @param size
    */
    void removeWord(string position, int size);
    bool writePlayerWord(string position, string word);
    vector<pair<string, string>> vertiWord;
    vector<pair<string, string>> horiWord;
    vector<pair<string, string>> userWordPos;
	int numHints;
};


#endif //MIEIC_17_18_TP_2_CWPLAYER_H
