#include "Mage.h"

#include "Monster.h"

#include <iostream>

using namespace std;

namespace
{
    int CalculateDamage(int attackPower, int defence)
    {
        int damage = attackPower - defence;
        return damage > 0 ? damage : 1;
    }
}

Mage::Mage(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence)
{
    job = "마법사";
    this->mp += 20;
    this->power += 10;
}

void Mage::attack(Monster* monster)
{
    int damage = CalculateDamage(power, monster->getDefence());
    monster->setHP(monster->getHP() - damage);

    cout << "[마법사] 마법 지팡이로 공격! -> " << monster->getName()
         << "에게 " << damage << " 데미지!" << endl;
}

bool Mage::skill(Monster* monster)
{
    const int manaCost = 25;

    if (mp < manaCost)
    {
        cout << "마나가 부족합니다. (필요 MP: " << manaCost << ")" << endl;
        return false;
    }

    mp -= manaCost;
    int damage = CalculateDamage(static_cast<int>(power * 1.5), monster->getDefence());
    monster->setHP(monster->getHP() - damage);

    cout << "[마법사 스킬] 파이어볼! -> " << monster->getName()
         << "에게 " << damage << " 데미지! (남은 MP: " << mp << ")" << endl;
    return true;
}
