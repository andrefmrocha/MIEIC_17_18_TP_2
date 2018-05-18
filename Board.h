//
// Created by joaom on 26-04-2018.
//

#ifndef PROJETO_2_BOARD_H
#define PROJETO_2_BOARD_H
#ifdef __unix__
// UNIX specific
#include "unix_colors.h"
#else 
// WINDOWS specific
#include "windows_colors.h"
#endif
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Board {
public:

	/*************************************************************
 	*************************Board*******************************
 	* Board constructor creates class, usually for prompting
 	* the method readFile.
 	*/
    Board();

	/************************************************************
	 **********************Board*********************************
	 * Board constructor when the measures of the board are
 	* already known.
 	* @param lines
	 * @param columns
 	*/
    Board(unsigned int lines, unsigned int columns);
	/****************************************************************
 	**************************resizeBoard***************************
 	* resizeBoard method is used to create a board to fit the
 	* criteria given by the file.
 	* @param lines
 	* @param columns
 	*/
    void resizeBoard(unsigned int lines, unsigned int columns);

	/***********************************************************
 	***********************finishBoard*************************
 	* The finishBoard method searches for the 'F' character on
 	* the position string which indicates if a word is valid or
 	* not
	 */
    void finishBoard();

	/**************************************************
 	*******************positionalCheck****************
 	* @param position
 	* @return if a positional is valid to add a word
 	*/
    bool positionalCheck(string position);
	/******************************************************
 	********************board_show************************
 	* board_show methos is used to show the board to the
 	* user.
 	*/
    void board_show();
	/*************************************************************
	 *************************** eraseWord************************
 	* The eraseWord method gives the possibility to the user to
 	* delete a selected word from vector of pairs.
 	* @param word
 	*/
    bool eraseWord(string position);
	/**********************************************
 	******************readFile********************
 	* The readFile method is used to read a given
 	* .txt file and prepare a board accordingly
 	* @param iname
 	* @return if the word was saved
 	*/
    bool readFile(string iname);
	/************************************************************
	 ***********************fillBoard****************************
	 * The fillBoard method is used to fill the Board as a means
 	* of preparing it with all the given rules.
	 */
	void fillBoard();
	/***********************************************
	 *********************setBoardname**************
 	* Method to changed the board name.
 	* @param bname
 	*/
	void setBoardname(string bname);
	/***********************************************
 	******************giveBoardName****************
 	* @return the name of the board
 	*/
	string giveBoardName();
	/***********************************************
	 ******************checkFinished****************
 	* @return if the board is finished
 	*/
	bool checkFinished();
protected:
    int lines;
    int columns;
    vector<vector <char>> board;
    vector<pair<string, string>> wordPos;
	/*********************************************************
	 ********************* writeAllWords *********************
 	* writeAllWords method is used to run the vector of pairs
 	* and indicate to writeWord, the parameters for it to
 	* write.
	 */
    void writeAllWords();
	/*************************************************************
 	*************************** clear ***************************
 	* The clear method is used to clean the board after analyzing
 	* it. Our board has a standard to be left clean after each
 	* operation.
 	*/
    void clear();
	/*********************************************
	 **************countColumn*******************
 	* @param savingString
 	* @return number of columns in a board
 	*/
    int countColumn(string savingString);
	bool finished;
private:
	string boardname;
	/***************************************************************************
	* *************************** writeWord ***********************************
 	* writeWord method is used to actually write a Word a word in the board
 	* Various methods require a filled board to analyze and make several decisions
 	* @param position
 	* @param word
 	*/
    void writeWord(string position, string word);
};


#endif //PROJETO_2_BOARD_H
