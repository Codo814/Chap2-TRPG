#include "Archer.h"

Archer::Archer(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    job = "마법사";
    this->defence += 30;
}

void Archer::attack() {
    cout << "- È­»ìÀ» ½ð´Ù!" << endl;
}
