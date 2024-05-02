#include "EarthTank.h"
#include "../Game/Game.h"
#include "../Armies/EarthArmy.h"

EarthTank::EarthTank(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string EarthTank::GetType()
{
	return type;
}

void EarthTank::Attack(Game* game, EarthArmy* eartharmy, AlienArmy* alienarmy)
{
	LinkedQueue<AlienSoldier*>tempAS;
	LinkedQueue<AlienMonster*>tempAM;
	AlienSoldier* AS;
	AlienMonster* AM;
	EarthTank* ET;
	EarthSoldier* ES;
	int attackCount = 0;
	int attackCountAM = 0;
	int attackCountAS = 0;

		eartharmy->getET().peek(ET);

		if (ET) {
			if (eartharmy->getES().getCount() < 0.3 * alienarmy->getAS().getCount())
			{
				while (eartharmy->getES().getCount() < 0.8 * alienarmy->getAS().getCount())
				{
					if (ET->GetAttackCapacity() % 2 == 0)
					{
						attackCount = ET->GetAttackCapacity() / 2;
						for (int i = 0; i < attackCount; i++)
						{
							alienarmy->removeAS(AS);
							alienarmy->removeAM(AM);
							if (AS && AM)
							{
								AS->SetHealth(AS->GetHealth() - (ET->GetPower() * ((ET->GetHealth()) / 100)) / sqrt(AS->GetHealth()));
								if (Ta == 0)
								{
									Ta = game->GetTimeStep();
								}
								if (AS->GetHealth() <= 0)
								{
									game->AddToKilled(AS);
									Td = game->GetTimeStep();
								}
								else
								{
									tempAS.enqueue(AS);
								}
								AM->SetHealth(AM->GetHealth() - (ET->GetPower() * ((ET->GetHealth()) / 100)) / sqrt(AM->GetHealth()));
								if (Ta == 0)
								{
									Ta = game->GetTimeStep();
								}
								if (AM->GetHealth() <= 0)
								{
									game->AddToKilled(AM);
									Td = game->GetTimeStep();
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
						attackCountAS = (ET->GetAttackCapacity()) / 2;
						attackCountAM = (ET->GetAttackCapacity() - attackCountAS);
						for (int i = 0; i < attackCountAS; i++)
						{
							alienarmy->removeAS(AS);
							if (AS)
							{
								AS->SetHealth(AS->GetHealth() - (ET->GetPower() * ((ET->GetHealth()) / 100)) / sqrt(AS->GetHealth()));
								if (Ta == 0)
								{
									Ta = game->GetTimeStep();
								}
								if (AS->GetHealth() <= 0)
								{
									game->AddToKilled(AS);
									Td = game->GetTimeStep();
								}
								else
								{
									tempAS.enqueue(AS);
								}
							}
						}
						for (int i = 0; i < attackCountAM; i++)
						{
							alienarmy->removeAM(AM);
							if (AM)
							{
								AM->SetHealth(AM->GetHealth() - (ET->GetPower() * ((ET->GetHealth()) / 100)) / sqrt(AM->GetHealth()));
								if (Ta == 0)
								{
									Ta = game->GetTimeStep();
								}
								if (AM->GetHealth() <= 0)
								{
									game->AddToKilled(AM);
									Td = game->GetTimeStep();
								}
								else
								{
									tempAM.enqueue(AM);
								}
							}

						}

					}

				}
			}

			else
			{
				for (int i = 0; i < ET->GetAttackCapacity(); i++)
				{
					alienarmy->removeAM(AM);
					if (AM)
					{
						AM->SetHealth(AM->GetHealth() - (ET->GetPower() * ((ET->GetHealth()) / 100)) / sqrt(AM->GetHealth()));
						if (Ta == 0)
						{
							Ta = game->GetTimeStep();
						}
						if (AM->GetHealth() <= 0)
						{
							game->AddToKilled(AM);
							Td = game->GetTimeStep();
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
			alienarmy->ReAddAlienUnit(AS);
		}
		while (tempAM.dequeue(AM))
		{
			alienarmy->ReAddAlienUnit(AM);
		}

}