//
// Created by andrefmrocha on 06-05-2018.
//

#ifndef MIEIC_17_18_TP_2_PLAYER_H
#define MIEIC_17_18_TP_2_PLAYER_H

#include <ctime>
#include <string>
class Player
{
public:
    Player(std::string name, std::string difficulty);
	/***************************************
 	****************finishGame*************
 	* Method to finish the user's game.
 	* @return the number of seconds used
 	*/
   std::time_t finishGame();
	/***************************************
 	****************updateTime*************
 	* Method to update user Time.
 	*/
    void updateTime();
	/***********************************
 	***************GetName*************
 	* @return the name of the player
 	*/
	std::string GetName();
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
	std::time_t getTime();
	/**********************************
	**********nameDifficulty***********
	* @return the difficulty chosen in
	* a string
	*/
	std::string nameDifficulty();
private:
    std::string playerName;
    std::time_t playerTime;
    int difficulty;
};


#endif //MIEIC_17_18_TP_2_PLAYER_H
