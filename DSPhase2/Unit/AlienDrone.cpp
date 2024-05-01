#include "AlienDrone.h"
#include "../Game/Game.h"
#include "../Armies/AlienArmy.h"

AlienDrone::AlienDrone(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string AlienDrone::GetType()
{
    return type;
}

void AlienDrone::Attack(Game* game, EarthArmy* eartharmy, AlienArmy* alienarmy)
{

}