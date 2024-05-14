#include "AlienMonster.h"
#include "../Game/Game.h"
#include "../Armies/AlienArmy.h"

AlienMonster::AlienMonster(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string AlienMonster::GetType()
{
    return type;
}

void AlienMonster::Attack(Game* game)
{
    LinkedQueue<EarthSoldier*>tempES;
    LinkedQueue<EarthTank*>tempET;

    AlienMonster* AM = nullptr;
    EarthSoldier* ES = nullptr;
    EarthTank* ET = nullptr;

    double oghealthES = 0;
    double oghealthET = 0;
    int attackCes = 0;
    int attackCet = 0;

    game->GetAA()->peekAM(AM);
    {
        if (AM)
        {
            game->addAMAttack(AM);
        }
        attackCes = (AM->GetAttackCapacity() / 2);
        attackCet = (AM->GetAttackCapacity() - attackCes);
        for (int i = 0; i < attackCes; i++)
        {
            if (!game->GetEA()->isEmpty_ES())
            {
                game->GetEA()->peekES(ES);
                if (ES)
                {
                    game->addAMAttack(ES);
                }
                game->GetEA()->removeES(ES);
                oghealthES = ES->GetOgHealth();
                ES->SetHealth(ES->GetHealth() - (AM->GetPower() * ((AM->GetHealth()) / 100)) / sqrt(ES->GetHealth()));
                int Infect = 0;
                Infect = 1 + (rand() % 100);
                if (Infect <= game->in.InfectionProb)
                {
                    ES->SetInfectedCheck(true);
                    game->IncrementInfectedCount();
                }
                if (ES->GetTa() == 0)
                {
                    ES->SetTa(game->GetTimeStep());
                }
                if (ES->GetHealth() <= 0)
                {
                    game->AddToKilled(ES);
                    ES->SetTd(game->GetTimeStep());
                }
                else if (ES->GetHealth() > 0 && ES->GetHealth() < 0.2 * oghealthES)
                {
                    game->addESToUML(ES);
                }
                else
                {
                    tempES.enqueue(ES);
                }
            }
            else
            {
                if (!game->GetEA()->isEmpty_ET()) 
                {
                    game->GetEA()->peekET(ET); 
                    if (ET)
                    {
                        game->addAMAttack(ET); 
                    }
                    game->GetEA()->removeET(ET); 
                    oghealthET = ET->GetOgHealth(); 
                    ET->SetHealth(ET->GetHealth() - (AM->GetPower() * ((AM->GetHealth()) / 100)) / sqrt(ET->GetHealth())); 
                    if (ET->GetTa() == 0) 
                    {
                        ET->SetTa(game->GetTimeStep()); 
                    }
                    if (ET->GetHealth() <= 0) 
                    {
                        game->AddToKilled(ET); 
                        ET->SetTd(game->GetTimeStep()); 
                    }
                    else if (ET->GetHealth() > 0 && ET->GetHealth() < 0.2 * oghealthET) 
                    {
                        game->addETToUML(ET); 
                    }
                    else
                    {
                        tempET.enqueue(ET); 
                    }
                }
            }
        }
        for (int i = 0; i < attackCet; i++)
        {
            if (!game->GetEA()->isEmpty_ET())
            {
                game->GetEA()->peekET(ET);
                if (ET)
                {
                    game->addAMAttack(ET);
                }
                game->GetEA()->removeET(ET);
                oghealthET = ET->GetOgHealth();
                ET->SetHealth(ET->GetHealth() - (AM->GetPower() * ((AM->GetHealth()) / 100)) / sqrt(ET->GetHealth()));
                if (ET->GetTa() == 0)
                {
                    ET->SetTa(game->GetTimeStep());
                }
                if (ET->GetHealth() <= 0)
                {
                    game->AddToKilled(ET);
                    ET->SetTd(game->GetTimeStep());
                }
                else if (ET->GetHealth() > 0 && ET->GetHealth() < 0.2 * oghealthET)
                {
                    game->addETToUML(ET);
                }
                else
                {
                    tempET.enqueue(ET);
                }
            }
            else
            {
                if (!game->GetEA()->isEmpty_ES())
                {
                    game->GetEA()->peekES(ES);
                    if (ES)
                    {
                        game->addAMAttack(ES);
                    }
                    game->GetEA()->removeES(ES);
                    oghealthES = ES->GetOgHealth();
                    ES->SetHealth(ES->GetHealth() - (AM->GetPower() * ((AM->GetHealth()) / 100)) / sqrt(ES->GetHealth()));
                    int Infect = 0;
                    Infect = 1 + (rand() % 100);
                    if (Infect <= game->in.InfectionProb)
                    {
                        ES->SetInfectedCheck(true);
                        game->AddInfectedES(ES);
                    }
                    if (ES->GetTa() == 0)
                    {
                        ES->SetTa(game->GetTimeStep());
                    }
                    if (ES->GetHealth() <= 0)
                    {
                        game->AddToKilled(ES);
                        ES->SetTd(game->GetTimeStep());
                    }
                    else if (ES->GetHealth() > 0 && ES->GetHealth() < 0.2 * oghealthES)
                    {
                        game->addESToUML(ES);
                    }
                    else
                    {
                        tempES.enqueue(ES);
                    }
                }
            }
        }
    }
    while (tempES.dequeue(ES))
    {
        game->GetEA()->ReAddEarthUnit(ES);
    }
    while (tempET.dequeue(ET))
    {
        game->GetEA()->ReAddEarthUnit(ET);
    }
}