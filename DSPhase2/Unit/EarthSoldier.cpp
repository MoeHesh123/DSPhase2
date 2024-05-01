#include "EarthSoldier.h"
#include "../Game/Game.h"
#include "../Armies/EarthArmy.h"

EarthSoldier::EarthSoldier(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string EarthSoldier::GetType()
{
    return type;
}

void EarthSoldier::Attack(Game*& game, EarthArmy*& eartharmy, AlienArmy*& alienarmy)
{

}