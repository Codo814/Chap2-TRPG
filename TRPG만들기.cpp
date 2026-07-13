#include <iostream>
#include "Warrior.h"
#include "Mage.h"
#include "Thief.h"
#include "Archer.h"

using namespace std;

void PrintCharacter(string name, int stat[])
{
    cout << endl;
    cout << name << " 의 능력치" << endl;
    cout << "===========================================" << endl;
    cout << "체력 : " << stat[0] << "    마나 : " << stat[1] << endl;
    cout << "공격력 : " << stat[2] << "    방어력 : " << stat[3] << endl;
    cout << "===========================================" << endl;
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

int main()
{
    string name;
    const int SIZE = 4;
    int stat[SIZE];
    // stat[0] = 체력
    // stat[1] = 마나
    // stat[2] = 공격력
    // stat[3] = 방어력

    cout << "===========================================" << endl;
    cout << "[던전 탈출 텍스트 RPG]" << endl;
    cout << "===========================================" << endl;
    cout << "캐릭터 이름을 적어주세요. : ";
    cin >> name;

    while (true)
    {
        cout << "체력과 마나를 적어주세요. : ";
        cin >> stat[0] >> stat[1];

        if (stat[0] >= 50 && stat[1] >= 50)
        {
            break;
        }

        cout << "체력이나 마나값이 너무 작습니다. 다시 입력해주세요." << endl;
    }

    while (true)
    {
        cout << "공격력과 방어력을 적어주세요. : ";
        cin >> stat[2] >> stat[3];

        if (stat[2] >= 50 && stat[3] >= 50)
        {
            break;
        }

        cout << "공격력이나 방어력이 너무 작습니다. 다시 입력해주세요." << endl;
    }

    PrintCharacter(name, stat);

    int hpPotion = 5;
    int mpPotion = 5;
    bool isGameStart = false;
    int choice;

    cout << endl << endl << "* HP 포션 5개, MP 포션 5개가 기본 지급되었습니다." << endl;

    while (!isGameStart)
    {
        cout << "============================================" << endl;
        cout << "< 캐릭터 강화 >" << endl;
        cout << "1. HP UP    2. MP UP    3. 공격력 2배" << endl;
        cout << "4. 방어력 2배  5. 현재 능력치  0. 게임 시작" << endl;
        cout << "============================================" << endl;
        cout << "번호를 선택해주세요: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (hpPotion > 0)
            {
                int beforeHP = stat[0];
                stat[0] += 20;
                hpPotion--;
                cout << endl << endl << "* HP가 20 증가했습니다. (" << beforeHP << " -> " << stat[0] << ") "
                    << "(HP 포션 차감 : 남은 포션 " << hpPotion << "개)" << endl;
            }
            else
            {
                cout << endl << endl << "HP 포션이 부족합니다." << endl;
            }
            break;

        case 2:
            if (mpPotion > 0)
            {
                int beforeMP = stat[1];
                stat[1] += 20;
                mpPotion--;
                cout << endl << endl << "* MP가 20 증가했습니다. (" << beforeMP << " -> " << stat[1] << ") "
                    << "(MP 포션 차감 : 남은 포션 " << mpPotion << "개)" << endl;
            }
            else
            {
                cout << endl << endl << "MP 포션이 부족합니다." << endl;
            }
            break;

        case 3:
        {
            int beforeATK = stat[2];
            stat[2] *= 2;
            cout << endl << endl << "* 공격력이 2배 증가했습니다. (공격력 : " << beforeATK << " -> " << stat[2] << ")" << endl;
            break;
        }

        case 4:
        {
            int beforeDEF = stat[3];
            stat[3] *= 2;
            cout << endl << endl << "* 방어력이 2배 증가했습니다. (방어력 : " << beforeDEF << " -> " << stat[3] << ")" << endl;
            break;
        }

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

    Player* player = nullptr;
    int jobChoice;

    cout << "< 전직 시스템 >" << endl;
    cout << name << "님, 직업을 선택해주세요!" << endl;
    cout << "1. 전사   2. 마법사   3. 도적   4. 궁수" << endl;
    cout << "선택: ";
    cin >> jobChoice;

    switch (jobChoice)
    {
    case 1:
        player = new Warrior(name, stat[0], stat[1], stat[2], stat[3]);
        break;

    case 2:
        player = new Mage(name, stat[0], stat[1], stat[2], stat[3]);
        break;

    case 3:
        player = new Thief(name, stat[0], stat[1], stat[2], stat[3]);
        break;

    case 4:
        player = new Archer(name, stat[0], stat[1], stat[2], stat[3]);
        break;

    default:
        cout << "잘못된 직업 선택입니다." << endl;
        break;
    }

    if (player != nullptr)
    {
        player->attack();
        player->printPlayerStatus();

        Slime slime;
        while (player->getHP() > 0 && slime.getHP() > 0) {
            int damage = player->getPower() - slime.getDefence();

            if (damage <= 0) {
                damage = 1;
            }

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

    delete player;
}
