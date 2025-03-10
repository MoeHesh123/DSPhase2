#include "EarthGunnery.h"
#include "../Game/Game.h"
#include "../Armies/EarthArmy.h"

EarthGunnery::EarthGunnery(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string EarthGunnery::GetType()
{
    return type;
}

void EarthGunnery::Attack(Game* game)
{
    LinkedQueue<AlienMonster*>tempAM;
    LinkedQueue<AlienDrone*>tempAD;

    AlienDrone* AD = nullptr;
    AlienDrone* AD2 = nullptr;
    AlienMonster* AM = nullptr;
    EarthGunnery* EG = nullptr;

    int attackCAM = 0;
    int attackCAD = 0; 
    int piriority = 0;

    game->GetEA()->peekEG(EG, piriority);
    if (EG)
    {
        game->addEGAttack(EG);
    }
            attackCAM = (EG->GetAttackCapacity()) / 2;
            attackCAD = (EG->GetAttackCapacity() - attackCAM);


            for (int i = 0; i < attackCAM; i++)
            {
                if (!game->GetAA()->isEmpty_AM())
                {
                    game->GetAA()->peekAM(AM);
                    if (AM)
                    {
                        game->addEGAttack(AM);
                    }

                    game->GetAA()->removeAM(AM);

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
                else
                {
                    if (!game->GetAA()->isEmpty_AD())
                    {
                        if (game->GetAA()->getADcount() == 1)
                        {
                            game->GetAA()->peekADfront(AD);
                            if (AD)
                            {
                                game->addEGAttack(AD);
                            }

                            game->GetAA()->removeAD(AD, AD2);

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
                            game->GetAA()->peekADfront(AD);
                            if (AD) 
                            {
                                game->addEGAttack(AD); 
                            }



                            game->GetAA()->peekADback(AD2);
                            if (AD2)
                            {
                                game->addEGAttack(AD2);
                            }


                            game->GetAA()->removeAD(AD, AD2); 

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
            for (int i = 0; i < attackCAD; i++)
            {
                if (!game->GetAA()->isEmpty_AD())
                {
                    if (game->GetAA()->getADcount() == 1)
                    {
                        game->GetAA()->peekADfront(AD); 
                        if (AD) 
                        {
                            game->addEGAttack(AD); 
                        }

                        game->GetAA()->removeAD(AD, AD2);

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
                        game->GetAA()->peekADfront(AD); 
                        if (AD) 
                        {
                            game->addEGAttack(AD); 
                        }

                        game->GetAA()->peekADback(AD2); 
                        if (AD2) 
                        {
                            game->addEGAttack(AD2); 
                        }

                        game->GetAA()->removeAD(AD, AD2);

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
                else
                {
                    if (!game->GetAA()->isEmpty_AM()) 
                    {
                        game->GetAA()->peekAM(AM); 
                        if (AM) 
                        {
                            game->addEGAttack(AM); 
                        }

                        game->GetAA()->removeAM(AM); 

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
            }
        
    
    while (tempAM.dequeue(AM))
    {
        game->GetAA()->ReAddAlienUnit(AM);
    }
    while (tempAD.dequeue(AD))
    {
        game->GetAA()->ReAddAlienUnit(AD);
    }
}