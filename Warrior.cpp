#include "Warrior.h"

Warrior::Warrior(string name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    job = "전사";
    this->hp += 30;
}

void Warrior::attack() {
<<<<<<< HEAD
    cout << job << "로 전직하였습니다. (HP +30)" << endl;
    cout << "- 검을 휘두른다!" << endl;
=======
    cout << "- 검 휘두르기!" << endl;
>>>>>>> 702c9cd273f584e7ba18c1b3130ad297812baaef
}
