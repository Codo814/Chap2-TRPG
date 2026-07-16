#include "Warrior.h"

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

Warrior::Warrior(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence)
{
    job = "전사";
    this->hp += 20;
    this->power += 10;
}

void Warrior::attack(Monster* monster)
{
    int damage = CalculateDamage(power, monster->getDefence());
    monster->setHP(monster->getHP() - damage);

    cout << "[전사] 장검을 휘두른다! -> " << monster->getName()
         << "에게 " << damage << " 데미지!" << endl;
}

bool Warrior::skill(Monster* monster)
{
    const int manaCost = 20;

    if (mp < manaCost)
    {
        cout << "마나가 부족합니다. (필요 MP: " << manaCost << ")" << endl;
        return false;
    }

    mp -= manaCost;
    int damage = CalculateDamage(static_cast<int>(power * 1.2), monster->getDefence());
    monster->setHP(monster->getHP() - damage);

    cout << "[전사 스킬] 장검을 휘두른다! -> " << monster->getName()
         << "에게 " << damage << " 데미지! (남은 MP: " << mp << ")" << endl;
    return true;
}
