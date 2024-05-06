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
	AlienSoldier* AS = nullptr;
	AlienMonster* AM = nullptr;
	EarthTank* ET = nullptr;
	EarthSoldier* ES = nullptr;
	int attackCount = 0;
	int attackCountAM = 0;
	int attackCountAS = 0;

	eartharmy->peekET(ET);
	

		if (!eartharmy->isEmpty_ET()) {
			if ((eartharmy->getEScount()) < (0.3 * (alienarmy->getAScount())))
			{
				while ((eartharmy->getEScount()) < (0.8 * alienarmy->getAScount()))
				{
					if (ET->GetAttackCapacity() % 2 == 0) 
					{
						attackCount = (ET->GetAttackCapacity() / 2); 
						for (int i = 0; i < attackCount; i++) 
						{
							if (!(alienarmy->isEmpty_AS())) 
							{
								alienarmy->removeAS(AS); 


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
							if (!(alienarmy->isEmpty_AM())) 
							{
								alienarmy->removeAM(AM); 

								AM->SetHealth(AM->GetHealth() - (ET->GetPower() * ((ET->GetHealth()) / 100)) / sqrt(AM->GetHealth()));
								if (AM->GetTa() == 0)
								{
									AM->SetTa( game->GetTimeStep());
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
						attackCountAS =( (ET->GetAttackCapacity()) / 2);
						attackCountAM = (ET->GetAttackCapacity() - attackCountAS);
						for (int i = 0; i < attackCountAS; i++)
						{
							
							if (!(alienarmy->isEmpty_AS()));
							{
								alienarmy->removeAS(AS); 

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
							
							if (!(alienarmy->isEmpty_AM()))
							{
								alienarmy->removeAM(AM); 
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
			}

			else
			{
				for (int i = 0; i < ET->GetAttackCapacity(); i++)
				{
					
					if (!(alienarmy->isEmpty_AM()))
					{
						alienarmy->removeAM(AM); 
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
			alienarmy->ReAddAlienUnit(AS);
		}
		while (tempAM.dequeue(AM))
		{
			alienarmy->ReAddAlienUnit(AM);
		}

}