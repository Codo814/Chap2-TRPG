#pragma once
#include "Player.h"

class Mage : public Player {
public:
    Mage(string name, int hp, int mp, int power, int defence);
    void attack(Monster* monster) override;
    bool skill(Monster* monster) override;
};
