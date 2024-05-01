#include "EarthTank.h"
#include "../Game/Game.h"
#include "../Armies/EarthArmy.h"

EarthTank::EarthTank(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string EarthTank::GetType()
{
	return type;
}

void EarthTank::Attack(Game*& game, EarthArmy*& eartharmy, AlienArmy*& alienarmy)
{

}