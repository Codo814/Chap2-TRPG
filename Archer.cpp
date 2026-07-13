#include "Archer.h"

Archer::Archer(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    job = "궁수";
    this->defence += 30;
}

void Archer::attack() {
<<<<<<< HEAD
    cout << job << "로 전직하였습니다. (방어력 +30)" << endl;
    cout << "- 화살을 쏜다!" << endl;
=======
    cout << "-활 쏘기!" << endl;
>>>>>>> 702c9cd273f584e7ba18c1b3130ad297812baaef
}
