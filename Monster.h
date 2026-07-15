#pragma once

#include "Item.h"

#include <string>

class Player;

class Monster
{
protected:
    std::string name;
    int hp;
    int power;
    int defence;
    std::string dropItemName;
    int dropItemPrice;

public:
    Monster(std::string name, int hp, int power, int defence, std::string dropItemName, int dropItemPrice);

    std::string getName();
    int getHP();
    void setHP(int newHP);
    int getDefence();
    void attack(Player* player);
    Item getDropItem();
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
