#include "AlienMonster.h"
#include "../Game/Game.h"
#include "../Armies/AlienArmy.h"

AlienMonster::AlienMonster(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string AlienMonster::GetType()
{
    return type;
}

void AlienMonster::Attack(Game* game, EarthArmy* eartharmy, AlienArmy* alienarmy)
{

}