#pragma once

#include "Item.h"
#include <string>
using namespace std;

class Player;

class Monster
{
protected:
    string name;
    int hp;
    int power;
    int defence;
    string dropItemName;
    int dropItemPrice;
    int expReward;

public:
    Monster(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice, int expReward);

    string getName();
    int getHP();
    void setHP(int newHP);
    int getDefence();
    void attack(Player* player, bool isDefending = false);
    Item getDropItem();
    int getExpReward();
};

class Slime : public Monster
{
public:
    Slime();
};

class Goblin : public Monster
{
public:
    Goblin();
};
