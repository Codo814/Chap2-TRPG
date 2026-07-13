#include <iostream>
#include <string>
#include <windows.h>
#include "Warrior.h"
#include "Mage.h"
#include "Thief.h"
#include "Archer.h"

using namespace std;

const int STAT_SIZE = 4;
const int HP = 0;
const int MP = 1;
const int POWER = 2;
const int DEFENCE = 3;

void PrintCharacter(const string& name, int stat[])
{
    cout << endl;
    cout << name << " 의 능력치" << endl;
    cout << "===========================================" << endl;
    cout << "체력 : " << stat[HP] << "    마나 : " << stat[MP] << endl;
    cout << "공격력 : " << stat[POWER] << "    방어력 : " << stat[DEFENCE] << endl;
    cout << "===========================================" << endl;
}

void PrintTitle()
{
    cout << "===========================================" << endl;
    cout << "[던전 탈출 텍스트 RPG]" << endl;
    cout << "===========================================" << endl;
}

void InputStatPair(const string& inputMessage, const string& errorMessage, int& firstStat, int& secondStat)
{
    while (true)
    {
        cout << inputMessage;
        cin >> firstStat >> secondStat;

        if (firstStat >= 50 && secondStat >= 50)
        {
            break;
        }

        cout << errorMessage << endl;
    }
}

void InputCharacter(string& name, int stat[])
{
    PrintTitle();

    cout << "캐릭터 이름을 적어주세요. : ";
    cin >> name;

    InputStatPair(
        "체력과 마나를 적어주세요. : ",
        "체력이나 마나값이 너무 작습니다. 다시 입력해주세요.",
        stat[HP],
        stat[MP]
    );

    InputStatPair(
        "공격력과 방어력을 적어주세요. : ",
        "공격력이나 방어력이 너무 작습니다. 다시 입력해주세요.",
        stat[POWER],
        stat[DEFENCE]
    );
}

void UsePotion(int& stat, int& potionCount, const string& statName, const string& potionName)
{
    if (potionCount > 0)
    {
        int beforeStat = stat;
        stat += 20;
        potionCount--;

        cout << endl << endl << "* " << statName << "가 20 증가했습니다. ("
            << beforeStat << " -> " << stat << ") "
            << "(" << potionName << " 포션 차감 : 남은 포션 " << potionCount << "개)" << endl;
    }
    else
    {
        cout << endl << endl << potionName << " 포션이 부족합니다." << endl;
    }
}

void DoubleStat(int& stat, const string& statName)
{
    int beforeStat = stat;
    stat *= 2;

    cout << endl << endl << "* " << statName << "이 2배 증가했습니다. ("
        << statName << " : " << beforeStat << " -> " << stat << ")" << endl;
}

void PrintUpgradeMenu()
{
    cout << "============================================" << endl;
    cout << "< 캐릭터 강화 >" << endl;
    cout << "1. HP UP    2. MP UP    3. 공격력 2배" << endl;
    cout << "4. 방어력 2배  5. 현재 능력치  0. 게임 시작" << endl;
    cout << "============================================" << endl;
    cout << "번호를 선택해주세요: ";
}

void RunUpgradeMenu(const string& name, int stat[])
{
    int hpPotion = 5;
    int mpPotion = 5;
    bool isGameStart = false;

    cout << endl << endl << "* HP 포션 5개, MP 포션 5개가 기본 지급되었습니다." << endl;

    while (!isGameStart)
    {
        int choice;
        PrintUpgradeMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            UsePotion(stat[HP], hpPotion, "HP", "HP");
            break;

        case 2:
            UsePotion(stat[MP], mpPotion, "MP", "MP");
            break;

        case 3:
            DoubleStat(stat[POWER], "공격력");
            break;

        case 4:
            DoubleStat(stat[DEFENCE], "방어력");
            break;

        case 5:
            cout << endl << endl;
            PrintCharacter(name, stat);
            cout << endl;
            break;

        case 0:
            cout << endl << endl << "============================================" << endl;
            cout << "이제 던전 탈출 게임을 시작합니다!" << endl;
            cout << "============================================" << endl;
            isGameStart = true;
            break;

        default:
            cout << "잘못된 번호입니다. 다시 선택해주세요." << endl;
            break;
        }
    }
}

class Monster {
protected:
    string name;
    int hp;
    int power;
    int defence;
    string dropItemName;
    int dropItemPrice;

public:
    Monster(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice) {
        this->name = name;
        this->hp = hp;
        this->power = power;
        this->defence = defence;
        this->dropItemName = dropItemName;
        this->dropItemPrice = dropItemPrice;
    }

    string getName() {
        return name;
    }

    int getHP() {
        return hp;
    }

    void setHP(int newHP) {
        hp = newHP;
    }

    int getDefence() {
        return defence;
    }

    void attack(Player* player) {
        int damage = power - player->getDefence();

        if (damage <= 0) {
            damage = 1;
        }

        int currentHP = player->getHP();
        player->setHP(currentHP - damage);

        cout << name << "이(가) 플레이어를 공격!" << endl;
        cout << "플레이어는 " << damage << "의 데미지를 입었다!" << endl;
    }
};

class Slime : public Monster {
public:
    Slime()
        : Monster("슬라임", 30, 20, 10, "물컹물컹한 액체", 30) {
    }
};

Player* CreatePlayerByJob(const string& name, int stat[])
{
    int jobChoice;

    cout << "< 전직 시스템 >" << endl;
    cout << name << "님, 직업을 선택해주세요!" << endl;
    cout << "1. 전사   2. 마법사   3. 도적   4. 궁수" << endl;
    cout << "선택: ";
    cin >> jobChoice;

    switch (jobChoice)
    {
    case 1:
        return new Warrior(name, stat[HP], stat[MP], stat[POWER], stat[DEFENCE]);

    case 2:
        return new Mage(name, stat[HP], stat[MP], stat[POWER], stat[DEFENCE]);

    case 3:
        return new Thief(name, stat[HP], stat[MP], stat[POWER], stat[DEFENCE]);

    case 4:
        return new Archer(name, stat[HP], stat[MP], stat[POWER], stat[DEFENCE]);

    default:
        cout << "잘못된 직업 선택입니다." << endl;
        return nullptr;
    }
}

int CalculateDamage(int attackPower, int defence)
{
    int damage = attackPower - defence;

    if (damage <= 0)
    {
        damage = 1;
    }

    return damage;
}

void BattleSlime(Player* player)
{
    Slime slime;

    while (player->getHP() > 0 && slime.getHP() > 0) {
        int damage = CalculateDamage(player->getPower(), slime.getDefence());
        int currentSlimeHP = slime.getHP();
        slime.setHP(currentSlimeHP - damage);

        cout << "플레이어가 " << slime.getName() << "을(를) 공격!" << endl;
        cout << slime.getName() << "은(는) " << damage << "의 데미지를 입었다!" << endl;
        cout << slime.getName() << " 남은 HP: " << slime.getHP() << endl;

        if (slime.getHP() <= 0) {
            cout << slime.getName() << "을(를) 처치했습니다." << endl;
            break;
        }

        slime.attack(player);
        cout << "플레이어 남은 HP: " << player->getHP() << endl;

        if (player->getHP() <= 0) {
            cout << "플레이어가 쓰러졌습니다." << endl;
            break;
        }
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    string name;
    int stat[STAT_SIZE];
    // stat[HP] = 체력
    // stat[MP] = 마나
    // stat[POWER] = 공격력
    // stat[DEFENCE] = 방어력

    InputCharacter(name, stat);
    PrintCharacter(name, stat);
    RunUpgradeMenu(name, stat);

    Player* player = CreatePlayerByJob(name, stat);

    if (player != nullptr)
    {
        player->attack();
        player->printPlayerStatus();
        BattleSlime(player);
    }

    delete player;
}
