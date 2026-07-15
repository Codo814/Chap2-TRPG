#include "Monster.h"
#include "Player.h"
#include <iostream>
#include <utility>

using namespace std;

Monster::Monster(
    string name,
    int hp,
    int power,
    int defence,
    string dropItemName,
    int dropItemPrice,
    int expReward
)
    : name(move(name)),
    hp(hp),
    power(power),
    defence(defence),
    dropItemName(move(dropItemName)),
    dropItemPrice(dropItemPrice),
    expReward(expReward)
{
}
string Monster::getName()
{
    return name;
}

int Monster::getHP()
{
    return hp;
}

void Monster::setHP(int newHP)
{
    hp = newHP;
}

int Monster::getDefence()
{
    return defence;
}

void Monster::attack(Player* player)
{
    int damage = power - player->getDefence();

    if (damage <= 0)
    {
        damage = 1;
    }

    int currentHP = player->getHP();
    player->setHP(currentHP - damage);

    cout << name << "이(가) 플레이어를 공격!" << endl;
    cout << "플레이어는 " << damage << "의 데미지를 입었다!" << endl;
}

Item Monster::getDropItem()
{
    return Item{ dropItemName, dropItemPrice };
}

int Monster::getExpReward() {
    return expReward;
}

Slime::Slime()
    : Monster("슬라임", 30, 20, 10, "맑은 물", 30, 30)
{
}

Goblin::Goblin()
    : Monster("고블린", 50, 30, 15, "허브", 50, 50)
{
}
