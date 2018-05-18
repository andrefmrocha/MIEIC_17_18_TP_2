//
// Created by andrefmrocha on 06-05-2018.
//

#ifndef MIEIC_17_18_TP_2_PLAYER_H
#define MIEIC_17_18_TP_2_PLAYER_H

#include <ctime>
#include <string>
using namespace std;
class Player
{
public:
    Player(string name, string difficulty);
	/***************************************
 	****************finishGame*************
 	* Method to finish the user's game.
 	* @return the number of seconds used
 	*/
    unsigned long finishGame();
	/***************************************
 	****************updateTime*************
 	* Method to update user Time.
 	*/
    void updateTime();
	/***********************************
 	***************GetName*************
 	* @return the name of the player
 	*/
	string GetName();
	/***************************************
 	****************updateDifficulty*******
 	* Method to update Player Difficulty.
 	*/
	void updateDifficulty(int number);
	/***********************************
 	***************getDifficulty*************
 	* @return the difficulty chosen
 	*/
	int getDifficulty();
	/**************************************
	***************getTime*****************
	* @return the actual time of the player
	* game
	*/
	int getTime();
	/**********************************
	**********nameDifficulty***********
	* @return the difficulty chosen in
	* a string
	*/
	string nameDifficulty();
private:
    string playerName;
    unsigned long playerTime;
    int difficulty;
};


#endif //MIEIC_17_18_TP_2_PLAYER_H
