#include "HealUnit.h"
#include "../Game/Game.h"
#include "../Armies/EarthArmy.h"

HealUnit::HealUnit(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string HealUnit::GetType()
{
	return type;
}

void HealUnit::Attack(Game* game, EarthArmy* eartharmy, AlienArmy* alienarmy)
{
	LinkedQueue<Unit*> Temp;
	HealUnit* HU = nullptr;
	game->removeHU(HU);
	if (HU)
	{
		for (int i = 0; i < HU->GetAttackCapacity(); i++)
		{
			if (!(game->isEmpty_ESUML()))
			{
				EarthSoldier* ES = nullptr;
				int PRI = 0;
				game->removeESFromUML(ES, PRI);
				if (ES)
				{
					double OGH = ES->GetHealth();
				}
			}
		}
	}
}