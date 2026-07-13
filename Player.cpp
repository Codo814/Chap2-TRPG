#include "Player.h"

Player::Player(string name, int hp, int mp, int power, int defence) {
    this->name = name;
    this->hp = hp;
    this->mp = mp;
    this->power = power;
    this->defence = defence;
    this->level = 1;
}

int Player::getHP() {
    return hp;
}

void Player::setHP(int newHP) {
    hp = newHP;
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
    cout << "------------------------------------" << endl;
}