#include "EarthGunnery.h"
#include "../Game/Game.h"
#include "../Armies/EarthArmy.h"

EarthGunnery::EarthGunnery(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string EarthGunnery::GetType()
{
    return type;
}

void EarthGunnery::Attack(Game* game, EarthArmy* eartharmy, AlienArmy* alienarmy)
{
    LinkedQueue<AlienMonster*>tempAM;
    LinkedQueue<AlienDrone*>tempAD;
    AlienDrone* AD = nullptr;
    AlienDrone* AD2 = nullptr;
    AlienMonster* AM = nullptr;
    EarthGunnery* EG = nullptr;
    int attackC = 0;
    int attackCAD = 0; 
    int piriority = 0;
    eartharmy->peekEG(EG, piriority);

    if (EG)
    {
        if (((EG->GetAttackCapacity()) % 2) == 0)
        {
            attackC = (EG->GetAttackCapacity()) / 2;

            for (int i = 0; i < attackC; i++)
            {
                if (!alienarmy->isEmpty_AM())
                {
                    alienarmy->removeAM(AM);
                    AM->SetHealth(AM->GetHealth() - (EG->GetPower() * ((EG->GetHealth()) / 100)) / sqrt(AM->GetHealth()));
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
                
                if (! alienarmy->isEmpty_AD())
                {
                    
                    if (alienarmy->getADcount() == 1)
                    {
                        alienarmy->removeAD(AD, AD2); 

                        AD->SetHealth(AD->GetHealth() - (EG->GetPower() * ((EG->GetHealth()) / 100)) / sqrt(AD->GetHealth()));
                        if (AD->GetTa() == 0) 
                        {
                            AD->SetTa(game->GetTimeStep());
                        }
                        if (AD->GetHealth() <= 0)  
                        {
                            game->AddToKilled(AD);
                            AD->SetTd(game->GetTimeStep()); 

                        }
                        else
                        {
                            tempAD.enqueue(AD); 
                        }

                    }
                    else
                    {
                        alienarmy->removeAD(AD, AD2); 
                        AD->SetHealth(AD->GetHealth() - (EG->GetPower() * ((EG->GetHealth()) / 100)) / sqrt(AD->GetHealth()));
                        AD2->SetHealth(AD2->GetHealth() - (EG->GetPower() * ((EG->GetHealth()) / 100)) / sqrt(AD2->GetHealth()));

                        if (AD->GetTa() == 0) 
                        {
                            AD->SetTa(game->GetTimeStep()); 
                        }
                        if (AD2->GetTa() == 0) 
                        {
                            AD2->SetTa(game->GetTimeStep()); 
                        }

                        if (AD->GetHealth() <= 0) 
                        {
                            game->AddToKilled(AD); 
                            AD->SetTd(game->GetTimeStep()); 

                        }
                        else
                        {
                            tempAD.enqueue(AD); 
                        }

                        if (AD2->GetHealth() <= 0)
                        {
                            game->AddToKilled(AD2);
                            AD2->SetTd(game->GetTimeStep());

                        }
                        else
                        {
                            tempAD.enqueue(AD2); 
                        }
                    }
                }
            }
        }
        else
        {
            attackC = (EG->GetAttackCapacity()) / 2;
            attackCAD = (EG->GetAttackCapacity() - attackC);

            for (int i = 0; i < attackC; i++)
            {
                if (!alienarmy->isEmpty_AM())
                {
                    alienarmy->removeAM(AM);
                    AM->SetHealth(AM->GetHealth() - (EG->GetPower() * ((EG->GetHealth()) / 100)) / sqrt(AM->GetHealth()));
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

            for (int i = 0; i < attackCAD; i++)
            {
                if (!alienarmy->isEmpty_AD())
                {
                    
                    if (alienarmy->getADcount() == 1)
                    {
                        alienarmy->removeAD(AD, AD2);
                        AD->SetHealth(AD->GetHealth() - (EG->GetPower() * ((EG->GetHealth()) / 100)) / sqrt(AD->GetHealth()));
                        if (AD->GetTa() == 0)
                        {
                            AD->SetTa(game->GetTimeStep());
                        }
                        if (AD->GetHealth() <= 0)
                        {
                            game->AddToKilled(AD);
                            AD->SetTd(game->GetTimeStep());

                        }
                        else
                        {
                            tempAD.enqueue(AD);
                        }

                    }
                    else
                    {
                        alienarmy->removeAD(AD, AD2);
                        AD->SetHealth(AD->GetHealth() - (EG->GetPower() * ((EG->GetHealth()) / 100)) / sqrt(AD->GetHealth()));
                        AD2->SetHealth(AD2->GetHealth() - (EG->GetPower() * ((EG->GetHealth()) / 100)) / sqrt(AD2->GetHealth()));

                        if (AD->GetTa() == 0)
                        {
                            AD->SetTa(game->GetTimeStep());
                        }
                        if (AD2->GetTa() == 0)
                        {
                            AD2->SetTa(game->GetTimeStep());
                        }

                        if (AD->GetHealth() <= 0)
                        {
                            game->AddToKilled(AD);
                            AD->SetTd(game->GetTimeStep());

                        }
                        else
                        {
                            tempAD.enqueue(AD);
                        }

                        if (AD2->GetHealth() <= 0)
                        {
                            game->AddToKilled(AD2);
                            AD2->SetTd(game->GetTimeStep());

                        }
                        else
                        {
                            tempAD.enqueue(AD2);
                        }
                    }
                }










            }
        }
    }
    while (tempAM.dequeue(AM))
    {
        alienarmy->ReAddAlienUnit(AM);
    }
    while (tempAD.dequeue(AD))
    {
        alienarmy->ReAddAlienUnit(AD);
    }

}