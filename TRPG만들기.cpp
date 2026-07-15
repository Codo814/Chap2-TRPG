#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h>
#include <vector>
#include <limits>
#include "Warrior.h"
#include "Mage.h"
#include "Thief.h"
#include "Archer.h"
#include "AlchemyWorkshop.h"
#include "Item.h"
#include "Monster.h"

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
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "숫자만 입력해주세요." << endl;
            continue;
        }
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

Player* CreatePlayerByJob(const string& name, int stat[])
{
    while (true)
    {
        int jobChoice;
        string selectedJob;

        cout << endl;
        cout << "< 전직 시스템 >" << endl;
        cout << name << "님, 직업을 선택해주세요!" << endl;
        cout << "1. 전사   2. 마법사   3. 도적   4. 궁수" << endl;
        cout << "선택: ";
        cin >> jobChoice;

        switch (jobChoice)
        {
        case 1:
            selectedJob = "전사";
            break;

        case 2:
            selectedJob = "마법사";
            break;

        case 3:
            selectedJob = "도적";
            break;

        case 4:
            selectedJob = "궁수";
            break;

        default:
            cout << "잘못된 직업 선택입니다." << endl;
            continue;
        }

        int confirmChoice;

        cout << endl;
        cout << selectedJob << "(으)로 선택하시겠습니까?" << endl;
        cout << "1. 예   2. 아니오" << endl;
        cout << "선택: ";
        cin >> confirmChoice;

        if (confirmChoice == 2)
        {
            cout << "직업을 다시 선택합니다." << endl;
            continue;
        }

        if (confirmChoice != 1)
        {
            cout << "잘못된 선택입니다. 직업을 다시 선택합니다." << endl;
            continue;
        }

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
        }
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

void BattleRandomMonster(Player* player, vector<Item>& inventory)
{
    Slime slime;
    Goblin goblin;

    Monster* monster = nullptr;

    int randomMonster = rand() % 2;

    if (randomMonster == 0)
    {
        monster = &slime;
    }
    else
    {
        monster = &goblin;
    }

    cout <<endl<<endl <<"던전을 탈출하던 중, " << monster->getName() << "이(가) 나타났습니다!" << endl;

    while (player->getHP() > 0 && monster->getHP() > 0)
    {
        int damage = CalculateDamage(player->getPower(), monster->getDefence());
        int currentMonsterHP = monster->getHP();

        monster->setHP(currentMonsterHP - damage);

        cout << "플레이어가 " << monster->getName() << "을(를) 공격!" << endl;
        cout << monster->getName() << "은(는) " << damage << "의 데미지를 입었다!" << endl;
        cout << monster->getName() << " 남은 HP: " << monster->getHP() << endl;

        if (monster->getHP() <= 0)
        {
            cout << monster->getName() << "을(를) 처치했습니다." << endl;
            Item droppedItem = monster->getDropItem();
            inventory.push_back(droppedItem);
            cout << "★★★ 전투 승리!★★★" << endl;
            cout << " ->인벤토리에 "<< droppedItem.name<< " 이(가) 저장되었습니다." << endl;
            break;
        }

        monster->attack(player);
        cout << "플레이어 남은 HP: " << player->getHP() << endl;

        if (player->getHP() <= 0)
        {
            cout << "플레이어가 쓰러졌습니다." << endl;
            break;
        }
    }
}

int main()
{
    srand(time(0));
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    vector<Item> inventory;
    AlchemyWorkshop workshop;

    string name;
    int stat[STAT_SIZE];
    // stat[HP] = 체력
    // stat[MP] = 마나
    // stat[POWER] = 공격력
    // stat[DEFENCE] = 방어력
    bool isGameRunning = true;

    InputCharacter(name, stat);
    PrintCharacter(name, stat);
    RunUpgradeMenu(name, stat);

    Player* player = CreatePlayerByJob(name, stat);

    if (player == nullptr)
    {
   return 0;
    }

    player->attack();

    while(isGameRunning){
        int choice;
        cout <<endl<< "===== 메인 메뉴 =====" << endl;
        cout << "1. 던전 입장" << endl;
        cout << "2. 인벤토리 확인" << endl;
        cout << "3. 포션 제작소" << endl;
        cout << "0. 게임 종료" << endl;
        cout << "선택: ";
        cin >> choice;

        switch (choice) {
        case 1:
            BattleRandomMonster(player, inventory);

            if (player->getHP() <= 0) {
                cout << "게임 오버." << endl;
                isGameRunning = false;
            }
            break;

        case 2:
            cout <<endl<<endl<< "[ 인벤토리 (" << inventory.size() << "/30) ]" << endl;
            if (inventory.empty()) {
                cout << "인벤토리가 비어있습니다." << endl;
            }
            else {
                for (const Item& item : inventory) {
                    item.PrintInfo();
                }
            }
            break;

        case 3:
            workshop.RunMenu();
            break;

        case 0:
            cout << "게임을 종료합니다." << endl;
            isGameRunning = false;
            break;

        default:
            cout << "잘못된 선택입니다. 다시 골라주세요." << endl;
            break;
        }
    }
    delete player;
}
