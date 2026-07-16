#pragma once
#include <iostream>
#include <string>
using namespace std;

class Monster;

class Player {
protected:
    string name;
    string job;
    int level;
    int exp;
    int maxExp;
    int hp;
    int mp;
    int power;
    int defence;

public:
    Player(string name, int hp, int mp, int power, int defence);

    int getHP();
    void setHP(int newHP);
    void setName(const string& newName);
    int getMP();
    void setMP(int newMP);
    int getDefence();
    int getPower();
    void gainExp(int amount);

    virtual void attack(Monster* monster) = 0;
    virtual bool skill(Monster* monster) = 0;
    virtual ~Player() {}

    void printPlayerStatus();
};
