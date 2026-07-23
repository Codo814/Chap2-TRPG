#include <iostream>
#define NOMINMAX

#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h>
#include <vector>
#include <limits>
#include <thread>
#include <chrono>
#include "Warrior.h"
#include "Mage.h"
#include "Thief.h"
#include "Archer.h"
#include "AlchemyWorkshop.h"
#include "Item.h"
#include "Monster.h"
#include "Inventory.h"

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

void ClearScreen()
{
    system("cls");
}

void WaitForEnter(const string& message = "Enter를 누르면 다음 턴으로 넘어갑니다.")
{
    cout << endl << message;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void PrintStatComparison(const int previousStat[], const int newStat[])
{
    cout << "===== 스탯 리롤 결과 =====" << endl << endl;
    cout << "HP      " << previousStat[HP] << " -> " << newStat[HP] << endl;
    cout << "MP      " << previousStat[MP] << " -> " << newStat[MP] << endl;
    cout << "공격력  " << previousStat[POWER] << " -> " << newStat[POWER] << endl;
    cout << "방어력  " << previousStat[DEFENCE] << " -> " << newStat[DEFENCE] << endl;
    cout << endl;
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

void GenerateRandomStats(int stat[])
{
    for (int i = 0; i < STAT_SIZE; i++)
    {
        stat[i] = rand() % 51 + 50;
    }
}

void InputCharacterName(string& name)
{
    PrintTitle();

    cout << "캐릭터 이름을 적어주세요. : ";
    cin >> name;

    ClearScreen();
}

void RollCharacterStats(const string& name, int stat[])
{
    int rerollCount = 3;
    int previousStat[STAT_SIZE] = { 0, 0, 0, 0 };
    bool hasPreviousStat = false;
    bool rerollLimitReached = false;
    GenerateRandomStats(stat);

    while (true)
    {
        ClearScreen();

        if (hasPreviousStat)
        {
            PrintStatComparison(previousStat, stat);
        }
        else
        {
            cout << "랜덤 능력치가 생성되었습니다." << endl;
            PrintCharacter(name, stat);
        }

        cout <<endl<< "남은 리롤 기회: " << rerollCount << "회" << endl;
        cout << "이 스탯으로 정하시겠습니까?" << endl;
        cout << "1. 예   2. 아니오" << endl;
        cout << "선택: ";

        int choice;
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "숫자만 입력해주세요." << endl;
            continue;
        }

        if (choice == 1)
        {
            cout << "능력치가 확정되었습니다." << endl;
            break;
        }

        if (choice == 2)
        {
            if (rerollCount > 0)
            {
                for (int i = 0; i < STAT_SIZE; i++)
                {
                    previousStat[i] = stat[i];
                }

                rerollCount--;
                GenerateRandomStats(stat);
                hasPreviousStat = true;
                continue;
            }
            rerollLimitReached = true;
            break;
        }

        cout << "1 또는 2를 선택해주세요." << endl;
    }

    if (rerollLimitReached)
    {
        ClearScreen();
        cout << "리롤 기회를 모두 사용했습니다. 현재 능력치로 확정됩니다." << endl;
        PrintCharacter(name, stat);
    }

    WaitForEnter("Enter를 누르면 캐릭터 설정 메뉴로 돌아갑니다.");
    ClearScreen();
}

void setPotion(int count, int* p_HPPotion, int* p_MPPotion) {
    *p_HPPotion = count;
    *p_MPPotion = count;
}

Player* CreatePlayerByJob(const string& name, int stat[])
{
    while (true)
    {
        ClearScreen();

        int jobChoice;
        string selectedJob;
        string selectedBonus;
        string selectedSkillDescription;

        cout << "============================================"<< endl;
        cout << "< 전직 시스템 >" << endl;
        cout << name << "님, 직업을 선택해주세요!" << endl;
        cout << "1. 전사   2. 마법사   3. 도적   4. 궁수" << endl;
        cout << "============================================" << endl;
        cout <<endl<< "선택: ";
        cin >> jobChoice;

        switch (jobChoice)
        {
        case 1:
            selectedJob = "전사";
            selectedBonus = "HP +20, 공격력 +10";
            selectedSkillDescription = "장검 휘두르기 - 공격력 x1.2, 1회 공격 (MP 20, 적 방어력 적용)";
            break;

        case 2:
            selectedJob = "마법사";
            selectedBonus = "MP +20, 공격력 +10";
            selectedSkillDescription = "파이어볼 - 공격력 x1.5, 1회 공격 (MP 25, 적 방어력 적용)";
            break;

        case 3:
            selectedJob = "도적";
            selectedBonus = "HP +10, 공격력 +20";
            selectedSkillDescription = "단검찌르기 - 적 방어력 무시, 공격력 x0.4, 2회 공격 (MP 20)";
            break;

        case 4:
            selectedJob = "궁수";
            selectedBonus = "HP +10, MP +10, 공격력 +10";
            selectedSkillDescription = "더블샷 - 적 방어력 무시, 공격력 x0.4, 2회 공격 (MP 20)";
            break;

        default:
            cout << "잘못된 직업 선택입니다." << endl;
            continue;
        }

        int confirmChoice;

        cout << endl;
        cout << "직업 보너스: " << selectedBonus << endl;
        if (!selectedSkillDescription.empty())
        {
            cout << "스킬: " << selectedSkillDescription << endl;
        }
        cout << selectedJob << "(으)로 선택하시겠습니까?" << endl;
        cout << "1. 예   2. 아니오" << endl;
        cout <<endl<< "선택: ";
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
            cout <<endl<< "전사로 전직했습니다. (HP +20, 공격력 +10)" << endl;
            return new Warrior(name, stat[HP], stat[MP], stat[POWER], stat[DEFENCE]);

        case 2:
            cout <<endl<< "마법사로 전직했습니다. (MP +20, 공격력 +10)" << endl;
            return new Mage(name, stat[HP], stat[MP], stat[POWER], stat[DEFENCE]);

        case 3:
            cout <<endl<< "도적으로 전직했습니다. (HP +10, 공격력 +20)" << endl;
            return new Thief(name, stat[HP], stat[MP], stat[POWER], stat[DEFENCE]);

        case 4:
            cout <<endl<< "궁수로 전직했습니다. (HP +10, MP +10, 공격력 +10)" << endl;
            return new Archer(name, stat[HP], stat[MP], stat[POWER], stat[DEFENCE]);
        }
    }
}

void ShowInventorySummary(
    const Inventory<Item>& inventory,
    int HPPotion,
    int MPPotion)
{
    cout << "===== 인벤토리 =====" << endl;
    cout << "HP 포션: " << HPPotion << "개" << endl;
    cout << "MP 포션: " << MPPotion << "개" << endl;
    cout << "획득한 재료: " << inventory.GetSize() << "/30" << endl;

    if (inventory.GetSize() == 0 )
    {
        cout << "인벤토리에 저장된 재료가 없습니다." << endl;
        return;
    }
    inventory.PrintAllItems();
}

Player* RunCharacterSetupMenu(
    string& name,
    int stat[],
    const Inventory<Item>& inventory,
    int HPPotion,
    int MPPotion)
{
    bool statConfirmed = false;
    Player* player = nullptr;

    while (true)
    {
        ClearScreen();
        cout << "============================================" << endl;
        cout << "< 캐릭터 설정 >" << endl;
        cout << "1. 스탯 돌리기" << endl;
        cout << "2. 직업 선택하기" << endl;
        cout << "3. 현재 능력치 확인하기" << endl;
        cout << "4. 인벤토리 확인하기" << endl;
        cout << "5. 닉네임 변경하기" << endl;
        cout << "0. 게임 시작" << endl;
        cout << "============================================" << endl;
        cout << "스탯 확정: " << (statConfirmed ? "완료" : "미완료") << endl;
        cout << "직업 선택: " << (player != nullptr ? "완료" : "미완료") << endl;
        cout << "선택: ";

        int choice;
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "숫자만 입력해주세요." << endl;
            cout << "Enter를 누르면 설정 메뉴로 돌아갑니다.";
            cin.get();
            continue;
        }

        switch (choice)
        {
        case 1:
            if (statConfirmed)
            {
                cout << "스탯을 이미 확정한 상태라 변경할 수 없습니다." << endl;
                WaitForEnter("Enter를 누르면 설정 메뉴로 돌아갑니다.");
                break;
            }

            RollCharacterStats(name, stat);
            statConfirmed = true;
            break;

        case 2:
            if (!statConfirmed)
            {
                cout << "먼저 1번에서 스탯을 확정해주세요." << endl;
                WaitForEnter("Enter를 누르면 설정 메뉴로 돌아갑니다.");
                break;
            }

            {
                Player* newPlayer = CreatePlayerByJob(name, stat);

                delete player;
                player = newPlayer;

                player->printPlayerStatus();
                WaitForEnter("Enter를 누르면 설정 메뉴로 돌아갑니다.");
                ClearScreen();
            }
            break;

        case 3:
            ClearScreen();
            if (player != nullptr)
            {
                player->printPlayerStatus();
            }
            else if (statConfirmed)
            {
                PrintCharacter(name, stat);
                cout << "아직 직업을 선택하지 않았습니다." << endl;
            }
            else
            {
                cout << "아직 확정된 스탯이 없습니다." << endl;
            }
            WaitForEnter("Enter를 누르면 설정 메뉴로 돌아갑니다.");
            ClearScreen();
            break;

        case 4:
            ClearScreen();
            ShowInventorySummary(inventory, HPPotion, MPPotion);
            WaitForEnter("Enter를 누르면 설정 메뉴로 돌아갑니다.");
            ClearScreen();
            break;

        case 5:
            ClearScreen();
            cout << "현재 닉네임: " << name << endl;
            cout << "새로운 닉네임을 입력해주세요: ";
            cin >> name;

            if (player != nullptr)
            {
                player->setName(name);
            }

            cout << "닉네임이 " << name << "(으)로 변경되었습니다." << endl;
            WaitForEnter("Enter를 누르면 설정 메뉴로 돌아갑니다.");
            ClearScreen();
            break;

        case 0:
            if (!statConfirmed || player == nullptr)
            {
                if (!statConfirmed)
                {
                    cout << "스탯을 먼저 확정해야 합니다." << endl;
                }
                if (player == nullptr)
                {
                    cout << "직업을 먼저 선택해야 합니다." << endl;
                }
                WaitForEnter("Enter를 누르면 설정 메뉴로 돌아갑니다.");
                break;
            }

            ClearScreen();
            cout << "============================================" << endl;
            cout << "캐릭터 설정이 완료되었습니다." << endl;
            cout << "이제 던전 탈출 게임을 시작합니다!" << endl;
            cout << "============================================" << endl;
            player->printPlayerStatus();
            WaitForEnter("Enter를 누르면 메인 메뉴로 넘어갑니다.");
            ClearScreen();
            return player;

        default:
            cout << "잘못된 번호입니다." << endl;
            WaitForEnter("Enter를 누르면 설정 메뉴로 돌아갑니다.");
            break;
        }
    }
}

void PauseBattleOutput()
{
    this_thread::sleep_for(chrono::milliseconds(700));
}

int InputBattleChoice(int minChoice, int maxChoice)
{
    while (true)
    {
        int choice;
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "숫자만 입력해주세요: ";
            continue;
        }

        if (choice < minChoice || choice > maxChoice)
        {
            cout << minChoice << "부터 " << maxChoice << " 사이의 번호를 입력해주세요: ";
            continue;
        }

        return choice;
    }
}

bool RunBattleInventory(
    Player* player,
    const Inventory<Item>& inventory,
    int& HPPotion,
    int& MPPotion)
{
    ClearScreen();
    cout << endl << "===== 전투 인벤토리 =====" << endl;
    cout << "획득한 재료: "<< inventory.GetSize() << "/"<< inventory.GetCapacity() << endl;
    inventory.PrintAllItems();
    cout << "1. HP 포션 사용 (" << HPPotion << "개)" << endl;
    cout << "2. MP 포션 사용 (" << MPPotion << "개)" << endl;
    cout << "0. 돌아가기" << endl;
    cout << "선택: ";

    int choice = InputBattleChoice(0, 2);

    if (choice == 0)
    {
        return false;
    }

    if (choice == 1)
    {
        if (HPPotion <= 0)
        {
            cout << "HP 포션이 부족합니다." << endl;
            return false;
        }

        int beforeHP = player->getHP();
        player->setHP(beforeHP + 20);
        HPPotion--;
        cout << "HP 포션을 사용했습니다. (HP: " << beforeHP << " -> "
             << player->getHP() << ", 남은 포션: " << HPPotion << "개)" << endl;
        return true;
    }

    if (MPPotion <= 0)
    {
        cout << "MP 포션이 부족합니다." << endl;
        return false;
    }

    int beforeMP = player->getMP();
    player->setMP(beforeMP + 20);
    MPPotion--;
    cout << "MP 포션을 사용했습니다. (MP: " << beforeMP << " -> "
         << player->getMP() << ", 남은 포션: " << MPPotion << "개)" << endl;
    return true;
}

void BattleMonster(
    Player* player,
    Monster* monster,
    Inventory<Item>& inventory,
    int& HPPotion,
    int& MPPotion);

void RunDungeon(
    Player* player,
    Inventory<Item>& inventory,
    int& HPPotion,
    int& MPPotion)
{
    Slime slime;
    Goblin goblin;
    Ork ork;
    Dragon dragon;

    vector<Monster*> rooms = {
        &slime,
        &goblin,
        &ork
    };

    for (int i = 0; i < rooms.size(); i++)
    {
        Monster* currentMonster = rooms[i];

        cout <<endl<< "[ 던전 " << i + 1 << "번 방 ]" << endl;
        cout << currentMonster->getName() << " 등장!" << endl;

        BattleMonster(
            player,
            currentMonster,
            inventory,
            HPPotion,
            MPPotion);

        if (player->getHP() <= 0)
        {
            return;
        }

        cout << i + 1 << "번 방 클리어!" << endl;
    }
    cout << "★ 보스방 개방!" << endl;
    cout << dragon.getName() << " 등장!" << endl;

    BattleMonster(
        player,
        &dragon,
        inventory,
        HPPotion,
        MPPotion);
    if (player->getHP() <= 0)
    {
        return;
    }

    cout << dragon.getName() << "을(를) 처치했습니다!" << endl;
    cout << "=== 게임 클리어! ===" << endl;
}
 

void BattleMonster(
    Player* player,
    Monster* monster,
    Inventory<Item>& inventory,
    int& HPPotion,
    int& MPPotion)
{
    cout << endl << endl
        << "던전을 탈출하던 중, "
        << monster->getName()
        << "이(가) 나타났습니다!" << endl;
    WaitForEnter("Enter를 누르면 전투를 시작합니다.");

    while (player->getHP() > 0 && monster->getHP() > 0)
    {
        ClearScreen();
        cout << "===== 전투 =====" << endl;
        cout << "플레이어 HP: " << player->getHP()
             << " | MP: " << player->getMP() << endl;
        cout << monster->getName() << " HP: " << monster->getHP() << endl;

        bool playerActed = false;
        bool isDefending = false;

        while (!playerActed)
        {
            cout << endl << "무엇을 할까?" << endl;
            cout << "1. 공격" << endl;
            cout << "2. 스킬" << endl;
            cout << "3. 방어" << endl;
            cout << "4. 인벤토리 (포션 사용)" << endl;
            cout << "5. 턴 넘기기" << endl;
            cout << "선택: ";

            int choice = InputBattleChoice(1, 5);

            switch (choice)
            {
            case 1:
                player->attack(monster);
                playerActed = true;
                break;

            case 2:
                playerActed = player->skill(monster);
                break;

            case 3:
                cout << "방어 자세를 취했습니다." << endl;
                isDefending = true;
                playerActed = true;
                break;

            case 4:
                playerActed = RunBattleInventory(
                    player,
                    inventory,
                    HPPotion,
                    MPPotion);
                break;

            case 5:
                cout << "아무 행동도 하지 않고 턴을 넘겼습니다." << endl;
                playerActed = true;
                break;
            }
        }

        int displayedMonsterHP = monster->getHP();
        if (displayedMonsterHP < 0)
        {
            displayedMonsterHP = 0;
        }
        cout << monster->getName() << " 남은 HP: " << displayedMonsterHP << endl;

        if (monster->getHP() <= 0)
        {
            cout << monster->getName() << "을(를) 처치했습니다." << endl;
            Item droppedItem = monster->getDropItem();
            inventory.AddItem(droppedItem);
            cout <<endl<< "★★★ 전투 승리!★★★" << endl;
            player->gainExp(monster->getExpReward());
            player->printPlayerStatus();
            cout << " ->인벤토리에 "<< droppedItem.name<< " 이(가) 저장되었습니다." << endl;
            WaitForEnter("Enter를 누르면 다음 방으로 돌아갑니다.");
            ClearScreen();
            break;
        }

        cout << endl << "--- 몬스터의 턴 ---" << endl;
        PauseBattleOutput();
        monster->attack(player, isDefending);
        cout << "플레이어 남은 HP: " << player->getHP() << endl;
        PauseBattleOutput();

        if (player->getHP() <= 0)
        {
            cout << "플레이어가 쓰러졌습니다." << endl;
            WaitForEnter("Enter를 누르면 전투를 종료합니다.");
            ClearScreen();
            break;
        }

        WaitForEnter();
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    Inventory<Item> inventory(3);
    AlchemyWorkshop workshop;

    string name;
    int stat[STAT_SIZE] = { 0, 0, 0, 0 };
    // stat[HP] = 체력
    // stat[MP] = 마나
    // stat[POWER] = 공격력
    // stat[DEFENCE] = 방어력

    int HPPotion;
    int MPPotion;

    setPotion(5, &HPPotion, &MPPotion);

    bool isGameRunning = true;

    InputCharacterName(name);
    Player* player = RunCharacterSetupMenu(
        name,
        stat,
        inventory,
        HPPotion,
        MPPotion);

    if (player == nullptr)
    {
   return 0;
    }

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
            RunDungeon(player, inventory, HPPotion, MPPotion);

            if (player->getHP() <= 0)
            {
                cout << "게임 오버!" << endl;
            
            }

            isGameRunning = false;
            break;

        case 2:
            ClearScreen();
            ShowInventorySummary(inventory, HPPotion, MPPotion);
            WaitForEnter("Enter를 누르면 메인 메뉴로 돌아갑니다.");
            ClearScreen();
            break;

        case 3:
            workshop.RunMenu();
            ClearScreen();
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
