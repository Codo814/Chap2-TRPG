#include "Player.h"

Player::Player(string name, int hp, int mp, int power, int defence) {
    this->name = name;
    this->hp = hp;
    this->mp = mp;
    this->power = power;
    this->defence = defence;
    this->level = 1;
    this->exp = 0;
    this->maxExp = 100;
}

int Player::getHP() {
    return hp;
}

void Player::setHP(int newHP) {
    hp = newHP;
}

void Player::setName(const string& newName) {
    name = newName;
}

int Player::getMP() {
    return mp;
}

void Player::setMP(int newMP) {
    mp = newMP;
}

int Player::getDefence() {
    return defence;
}

int Player::getPower() {
    return power;
}

void Player::printPlayerStatus() {
    cout << "------------------------------------" << endl;
    cout << "닉네임: " << name << " | 직업: " << job << " | Lv." << level << endl;
    cout << "HP: " << hp << " | MP: " << mp << " | 공격력: " << power << " | 방어력: " << defence << endl;

    cout << "경험치: " << exp << "/" << maxExp << endl;
    cout << "------------------------------------" << endl;
}
void Player::gainExp(int amount) {

    exp += amount;
    cout << "  -> 경험치 +" << amount
        << " 획득! (현재 경험치: "
        << exp << "/" << maxExp << ")" << endl;
    if (exp >= maxExp) {
        int beforeLevel = level;
        level++;
        hp += 10;
        mp += 5;
        power += 5;

        exp = 0;
        maxExp += 50;

        cout << "  -> 레벨 업! Lv."
            << beforeLevel << " -> Lv." << level << endl;

        cout << "  -> HP +10, MP +5, 공격력 +5 증가!" << endl;
    }
}
