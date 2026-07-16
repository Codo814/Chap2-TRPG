#include "Thief.h"

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

Thief::Thief(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence)
{
    job = "도적";
    this->hp += 10;
    this->power += 20;
}

void Thief::attack(Monster* monster)
{
    int damage = CalculateDamage(power, monster->getDefence());
    monster->setHP(monster->getHP() - damage);

    cout << "[도적] 단검으로 공격! -> " << monster->getName()
         << "에게 " << damage << " 데미지!" << endl;
}

bool Thief::skill(Monster* monster)
{
    const int manaCost = 20;

    if (mp < manaCost)
    {
        cout << "마나가 부족합니다. (필요 MP: " << manaCost << ")" << endl;
        return false;
    }

    mp -= manaCost;
    int damagePerHit = static_cast<int>(power * 0.4);
    if (damagePerHit <= 0)
    {
        damagePerHit = 1;
    }

    int totalDamage = 0;

    cout << "[도적 스킬] 단검찌르기!" << endl;

    for (int i = 0; i < 2; i++)
    {
        monster->setHP(monster->getHP() - damagePerHit);
        totalDamage += damagePerHit;

        cout << i + 1 << "타 -> " << monster->getName()
             << "에게 " << damagePerHit << " 데미지!" << endl;
    }

    cout << "-> 토탈 데미지: " << totalDamage << endl;
    cout << "남은 MP: " << mp << endl;
    return true;
}
