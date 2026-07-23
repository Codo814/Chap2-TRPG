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

void Monster::attack(Player* player, bool isDefending)
{
    int damage = power - player->getDefence();

    if (isDefending)
    {
        damage /= 2;
    }

    if (damage <= 0)
    {
        damage = 1;
    }

    int currentHP = player->getHP();
    player->setHP(currentHP - damage);

    cout << name << "이(가) 플레이어를 공격!" << endl;
    if (isDefending)
    {
        cout << "방어에 성공해 받는 피해가 감소했습니다!" << endl;
    }
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
    : Monster("슬라임",30, 15, 0, "맑은 물", 30, 30)
{
}

Goblin::Goblin()
    : Monster("고블린", 50, 25, 0, "허브", 50, 50)
{
}

Ork::Ork()
    : Monster("오크", 80, 35, 0, "오크의 뿔", 70, 70)
{
}

Dragon::Dragon()
    : Monster("1층보스 드래곤", 200, 60, 20, "드래곤의 비늘", 150, 150)
{

}