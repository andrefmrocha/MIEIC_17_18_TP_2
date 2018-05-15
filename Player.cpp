//
// Created by andrefmrocha on 06-05-2018.
//
#include "stdafx.h"
#include "Player.h"

Player::Player(string name, char difficulty)
{
    playerName = name;
    playerTime = time(NULL);
    switch (difficulty) //The difficulty is chosen
    {
        case 'E':
            this->difficulty = 5;
            break;
        case 'N':
            this->difficulty = 3;
            break;
        case 'H':
            this->difficulty = 1;
            break;
    }
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
 ***************GetName*************
 * @return the difficulty chosen
 */
int Player::getDifficulty()
{
    return difficulty;
}