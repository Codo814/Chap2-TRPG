#include "Thief.h"

Thief::Thief(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    job = "도적";
    this->power += 30;
}

void Thief::attack() {
    cout << "- 찌르기" << endl;
}
