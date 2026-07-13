#include "Archer.h"

Archer::Archer(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    job = "궁수";
    this->defence += 30;
}

void Archer::attack() {
    cout << "-활 쏘기!" << endl;
}
