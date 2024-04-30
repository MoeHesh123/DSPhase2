#include "AlienMonster.h"

AlienMonster::AlienMonster(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string AlienMonster::GetType()
{
    return type;
}

void AlienMonster::Attack()
{
}
