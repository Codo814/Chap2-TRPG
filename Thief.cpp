#include "Thief.h"

Thief::Thief(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    job = "도적";
    this->power += 30;
}

void Thief::attack() {
<<<<<<< HEAD
    cout << job << "으로 전직하였습니다. (공격력 +30)" << endl;
    cout << "- 찌르기!" << endl;
=======
    cout << "- 찌르기" << endl;
>>>>>>> 702c9cd273f584e7ba18c1b3130ad297812baaef
}
