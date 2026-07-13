#pragma once
#include <iostream>
#include <string>
using namespace std;

class Player {
protected:
    string name;
    string job;
    int level;
    int hp;
    int mp;
    int power;
    int defence;

public:
    Player(string name, int hp, int mp, int power, int defence);

    int getHP();
    void setHP(int newHP);
    int getDefence();
    int getPower();

    virtual void attack() = 0;
    virtual ~Player() {}

    void printPlayerStatus();
};
