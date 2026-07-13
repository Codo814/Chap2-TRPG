#include "Archer.h"

Archer::Archer(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    job = "궁수";
    this->defence += 30;
}

void Archer::attack() {
    cout << job << "로 전직하였습니다. (방어력 +30)" << endl;
    cout << "- 화살을 쏜다!" << endl;
}
