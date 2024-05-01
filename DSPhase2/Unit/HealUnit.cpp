#include "HealUnit.h"
#include"../Game/Game.h"

HealUnit::HealUnit(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string HealUnit::GetType()
{
	return type;
}

void HealUnit::Attack(Game*& game)
{
	LinkedQueue<Unit*> Temp;
	for (int i = 0; i < attackCapacity; i++)
	{
		if (!(game->isEmpty_ESUML()))
		{
			EarthSoldier* es;
			int pri = 0;
			game->removeESFromUML(es, pri);
			if (game->GetTimeStep() - es->GetJTUML() >= 10) game->AddToKilled(es);
			else
			{
				Temp.enqueue(es);

			}


		}
		else if (!(game->isEmpty_ETUML()))
		{

			EarthTank* et;
			game->removeETFromUML(et);
			if (game->GetTimeStep() - et->GetJTUML() >= 10) game->AddToKilled(et);
			else
			{
				Temp.enqueue(et);

			}


		}
		else break;

	}

}
