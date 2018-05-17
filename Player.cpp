//
// Created by andrefmrocha on 06-05-2018.
//
#include "Player.h"

Player::Player(string name, string difficulty)
{
    playerName = name;
    playerTime = time(NULL);
	if (difficulty == "E")			//The difficulty is chosen
		this->difficulty = 5;
	else if (difficulty == "N")
		this->difficulty = 3;
	else
		this->difficulty = 1;
}

/***************************************
 ****************updateTime*************
 * Method to update user Time.
 */
void Player::updateTime()
{
    playerTime = time(NULL) - playerTime;
}

/***************************************
 ****************updateTime*************
 * Method to finish the user's game.
 * @return the number of seconds used
 */
unsigned long Player::finishGame()
{
    updateTime();
    return playerTime;
}

/***********************************
 ***************GetName*************
 * @return the name of the player
 */
string Player:: GetName() {
	return playerName;
}

/***************************************
 ****************updateTime*************
 * Method to update Player Difficulty.
 */
void Player::updateDifficulty(int number)
{
    difficulty = number;
}

/***********************************
 ***************getDifficulty*************
 * @return the difficulty chosen
 */
int Player::getDifficulty()
{
    return difficulty;
}

/**********************************
**********nameDifficulty***********
* @return the difficulty chosen in
* a string
*/
string Player::nameDifficulty()
{
	int difficulty = getDifficulty(); // gets the number of hints specific of each difficulty
	switch (difficulty)
	{
	case 5:
		return "Easy.";
	case 3:
		return "Normal.";
	case 1:
		return "Hard.";
	}
}

/**************************************
***************getTime*****************
* @return the actual time of the player
* game
*/
int Player::getTime()
{
	return playerTime;
}