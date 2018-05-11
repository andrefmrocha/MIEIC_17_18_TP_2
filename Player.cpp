//
// Created by andrefmrocha on 06-05-2018.
//
#include "stdafx.h"
#include "Player.h"

Player::Player(string name)
{
    playerName = name;
    playerTime = time(NULL);
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