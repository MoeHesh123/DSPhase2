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
	HealUnit* HU;
	game->removeHU(HU);
	for (int i = 0; i < HU->GetAttackCapacity(); i++)
	{
		if (!(game->isEmpty_ESUML()))
		{
			EarthSoldier* es;
			int pri = 0;
			game->removeESFromUML(es, pri);
			double OriginalHealth = es->GetHealth();
			//if ((game->GetTimeStep() - es->GetJTUML()) >= 10) game->AddToKilled(es);
			//else
			{
				double HealthImprovement = (((HU->GetPower() * HU->GetHealth())/100)/sqrt(es->GetHealth()));
				es->SetHealth(es->GetHealth() + HealthImprovement);
				if (es->GetHealth() >= 0.2 * OriginalHealth) eartharmy->ReAddEarthUnit(es);
				else Temp.enqueue(es);
			}
		}
		else if (!(game->isEmpty_ETUML()))
		{

			EarthTank* et;
			game->removeETFromUML(et);
			double OriginalHealth = et->GetHealth();
			/*if ((game->GetTimeStep() - et->GetJTUML()) >= 10) game->AddToKilled(et);
			else*/
			{
				double HealthImprovement = (((power * health) / 100) / sqrt(et->GetHealth()));
				et->SetHealth(et->GetHealth() + HealthImprovement);
				if (et->GetHealth() >= 0.2 * OriginalHealth) eartharmy->ReAddEarthUnit(et);
				else Temp.enqueue(et);
			}
		}
		else break;
	}
	Node<Unit*>* Current = Temp.getfrontPtr();
	while (Current)
	{
		Unit* unit = nullptr;
		Temp.dequeue(unit);
		if (unit->GetType() == "ES")
		{
			EarthSoldier* es = (EarthSoldier*)(unit);
			game->addESToUML(es);
		}
		else
		{
			EarthTank* et = (EarthTank*)(unit);
			game->addETToUML(et);
		}
		Current = Current->getNext();
	}
}