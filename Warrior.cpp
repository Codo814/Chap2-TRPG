#include "Warrior.h"

Warrior::Warrior(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    job = "전사";
    this->hp += 30;
}

void Warrior::attack() {
    cout << "- 검 휘두르기!" << endl;
}
