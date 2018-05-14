//
// Created by andrefmrocha on 06-05-2018.
//
#include "stdafx.h"
#include "Player.h"

Player::Player(string name, char difficulty)
{
    playerName = name;
    playerTime = time(NULL);
    switch (difficulty)
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

void Player::updateTime()
{
    playerTime = time(NULL) - playerTime;
}

unsigned long Player::finishGame()
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