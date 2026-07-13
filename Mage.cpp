#include "Mage.h"

Mage::Mage(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    job = "마법사";
    this->mp += 30;
}

void Mage::attack() {
    cout << job << "로 전직하였습니다. (MP +30)" << endl;
    cout << "- 파이어볼을 발사한다!" << endl;
}
