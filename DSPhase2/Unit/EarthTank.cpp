#include "EarthTank.h"
#include "../Game/Game.h"
#include "../Armies/EarthArmy.h"

EarthTank::EarthTank(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string EarthTank::GetType()
{
	return type;
}

void EarthTank::Attack(Game* game)
{
	LinkedQueue<AlienSoldier*>tempAS;
	LinkedQueue<AlienMonster*>tempAM;

	AlienSoldier* AS = nullptr;
	AlienMonster* AM = nullptr;
	EarthTank* ET = nullptr;
	EarthSoldier* ES = nullptr;

	int attackCount = 0;
	int attackCountAM = 0;
	int attackCountAS = 0;

	game->GetEA()->peekET(ET);
	if (!(game->GetEA()->isEmpty_ET()))
	{
		if ((game->GetEA()->getEScount()) < (0.3 * (game->GetAA()->getAScount())))
		{
			while ((game->GetEA()->getEScount()) < (0.8 * game->GetAA()->getAScount()))
			{
				if (ET->GetAttackCapacity() % 2 == 0)
				{
					attackCount = (ET->GetAttackCapacity() / 2);
					for (int i = 0; i < attackCount; i++)
					{
						if (!(game->GetAA()->isEmpty_AS()))
						{
							game->GetAA()->removeAS(AS);
							AS->SetHealth(AS->GetHealth() - (ET->GetPower() * ((ET->GetHealth()) / 100)) / sqrt(AS->GetHealth()));
							if (AS->GetTa() == 0)
							{
								AS->SetTa(game->GetTimeStep());
							}
							if (AS->GetHealth() <= 0)
							{
								game->AddToKilled(AS);
								AS->SetTd(game->GetTimeStep());
							}
							else
							{
								tempAS.enqueue(AS);
							}
						}
						if (!(game->GetAA()->isEmpty_AM()))
						{
							game->GetAA()->removeAM(AM);
							AM->SetHealth(AM->GetHealth() - (ET->GetPower() * ((ET->GetHealth()) / 100)) / sqrt(AM->GetHealth()));
							if (AM->GetTa() == 0)
							{
								AM->SetTa(game->GetTimeStep());
							}
							if (AM->GetHealth() <= 0)
							{
								game->AddToKilled(AM);
								AM->SetTd(game->GetTimeStep());
							}
							else
							{
								tempAM.enqueue(AM);
							}
						}
					}
				}
				else
				{
					attackCountAS = ((ET->GetAttackCapacity()) / 2);
					attackCountAM = (ET->GetAttackCapacity() - attackCountAS);
					for (int i = 0; i < attackCountAS; i++)
					{
						if (!(game->GetAA()->isEmpty_AS()))
						{
							game->GetAA()->removeAS(AS);
							AS->SetHealth(AS->GetHealth() - (ET->GetPower() * ((ET->GetHealth()) / 100)) / sqrt(AS->GetHealth()));
							if (AS->GetTa() == 0)
							{
								AS->SetTa(game->GetTimeStep());
							}
							if (AS->GetHealth() <= 0)
							{
								game->AddToKilled(AS);
								AS->SetTd(game->GetTimeStep());
							}
							else
							{
								tempAS.enqueue(AS);
							}
						}
					}
					for (int i = 0; i < attackCountAM; i++)
					{
						if (!(game->GetAA()->isEmpty_AM()))
						{
							game->GetAA()->removeAM(AM);
							AM->SetHealth(AM->GetHealth() - (ET->GetPower() * ((ET->GetHealth()) / 100)) / sqrt(AM->GetHealth()));
							if (AM->GetTa() == 0)
							{
								AM->SetTa(game->GetTimeStep());
							}
							if (AM->GetHealth() <= 0)
							{
								game->AddToKilled(AM);
								AM->SetTd(game->GetTimeStep());
							}
							else
							{
								tempAM.enqueue(AM);
							}
						}
					}
				}
				break;
			}
		}
		else
		{
			for (int i = 0; i < ET->GetAttackCapacity(); i++)
			{
				if (!(game->GetAA()->isEmpty_AM()))
				{
					game->GetAA()->removeAM(AM);
					AM->SetHealth(AM->GetHealth() - (ET->GetPower() * ((ET->GetHealth()) / 100)) / sqrt(AM->GetHealth()));
					if (AM->GetTa() == 0)
					{
						AM->SetTa(game->GetTimeStep());
					}
					if (AM->GetHealth() <= 0)
					{
						game->AddToKilled(AM);
						AM->SetTd(game->GetTimeStep());
					}
					else
					{
						tempAM.enqueue(AM);
					}
				}
			}
		}
	}
	while (tempAS.dequeue(AS))
	{
		game->GetAA()->ReAddAlienUnit(AS);
	}
	while (tempAM.dequeue(AM))
	{
		game->GetAA()->ReAddAlienUnit(AM);
	}
}