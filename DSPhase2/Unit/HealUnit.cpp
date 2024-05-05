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
	LinkedQueue<EarthSoldier*> TempES;
	LinkedQueue<EarthTank*> TempET;
	HealUnit* HU = nullptr;
	bool HealCheck = false;
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
					if ((game->GetTimeStep() - ES->GetJTUML()) >= 10)
					{
						ES->SetTd(game->GetTimeStep());
				        game->AddToKilled(ES);
					}
					else
					{
						double OGH = ES->GetHealth();
						double HealthImprovement = (((HU->GetPower() * HU->GetHealth()) / 100) / sqrt(ES->GetHealth()));
						ES->SetHealth(ES->GetHealth() + HealthImprovement);
						game->IncrementHealedCount();
						if (ES->GetHealth() >= 0.2 * OGH) eartharmy->ReAddEarthUnit(ES);
						else TempES.enqueue(ES);
					}
				}
				HealCheck = true;
			}
			else if (!(game->isEmpty_ETUML()))
			{
				EarthTank* ET = nullptr;
				game->removeETFromUML(ET);
				if (ET)
				{
					if ((game->GetTimeStep() - ET->GetJTUML()) >= 10)
					{
						ET->SetTd(game->GetTimeStep());
						game->AddToKilled(ET);
					}
					else
					{
						double OGH = ET->GetHealth();
						double HealthImprovement = (((power * health) / 100) / sqrt(ET->GetHealth()));
						ET->SetHealth(ET->GetHealth() + HealthImprovement);
						game->IncrementHealedCount();
						if (ET->GetHealth() >= 0.2 * OGH) eartharmy->ReAddEarthUnit(ET);
						else TempET.enqueue(ET);
					}
				}
				HealCheck = true;
			}
			else break;
		}
		if (HealCheck) 
		{
			delete HU;
			HU = nullptr;
		}
		else game->ReAddHealUnit(HU);
		EarthSoldier* es = nullptr;
		while (TempES.dequeue(es)) game->addESToUML(es);
		EarthTank* et = nullptr;
		while (TempET.dequeue(et)) game->addETToUML(et);
	}
}