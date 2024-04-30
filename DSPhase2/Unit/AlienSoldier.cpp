#include "AlienSoldier.h"

AlienSoldier::AlienSoldier(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string AlienSoldier::GetType()
{
    return type;
}

void AlienSoldier::Attack()
{
}
