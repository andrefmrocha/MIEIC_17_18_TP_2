//
// Created by andrefmrocha on 06-05-2018.
//
#include "stdafx.h"
#include "Player.h"

Player::Player(string name, int difficulty)
{
    playerName = name;
    playerTime = time(NULL);
    this->difficulty = difficulty;
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