#include "Mage.h"

Mage::Mage(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    job = "마법사";
    this->mp += 30;
}

void Mage::attack() {
    cout << "- 파이어볼을 발사한다!" << endl;
}