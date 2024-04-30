#include "AlienDrone.h"

AlienDrone::AlienDrone(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string AlienDrone::GetType()
{
    return type;
}

void AlienDrone::Attack()
{
}
