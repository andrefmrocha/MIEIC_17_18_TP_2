//
// Created by andrefmrocha on 06-05-2018.
//
#include "Player.h"
using namespace std;

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


void Player::updateTime()
{
    playerTime = time(NULL) - playerTime;
}


time_t Player::finishGame()
{
    updateTime();
    return playerTime;
}


string Player:: GetName() {
	return playerName;
}


void Player::updateDifficulty(int number)
{
    difficulty = number;
}


int Player::getDifficulty()
{
    return difficulty;
}


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
	return "Not found";
}


time_t Player::getTime()
{
	return playerTime;
}