#include "Thief.h"

Thief::Thief(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    job = "µµÀû";
    this->power += 30;
}

void Thief::attack() {
    cout << "- Âî¸£±â!" << endl;
}