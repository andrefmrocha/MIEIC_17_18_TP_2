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
    Player(string name);
    unsigned long finishGame();
    void updateTime();
	string GetName();
private:
    string playerName;
    unsigned long playerTime;
};


#endif //MIEIC_17_18_TP_2_PLAYER_H
