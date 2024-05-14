#include "EarthSoldier.h"
#include "../Game/Game.h"
#include "../Armies/EarthArmy.h"

EarthSoldier::EarthSoldier(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string EarthSoldier::GetType()
{
    return type;
}

void EarthSoldier::Attack(Game* game)
{
    LinkedQueue<AlienSoldier*> tempList;
    LinkedQueue<EarthSoldier*> tempListInfected;

    EarthSoldier* ES = nullptr;
    EarthSoldier* ES2 = nullptr;
    AlienSoldier* AS = nullptr;

    game->GetEA()->peekES(ES);
    if (ES)
    {
        if (ES->GetInfectedCheck())
        {
            game->addInfectedAttack(ES);
            if (!game->GetEA()->isEmpty_ES()) 
            { 
                game->GetEA()->removeES(ES2);
            }
            if (ES2)
            {
                if (!ES2->GetInfectedCheck())
                {
                    for (int i = 0; i < ES->GetAttackCapacity(); i++)
                    {
                        if (!game->GetEA()->isEmpty_ES())
                        {
                            game->GetEA()->peekES(ES2);
                            if (ES2)
                            {
                                game->addInfectedAttack(ES2);
                            }
                            game->GetEA()->removeES(ES2);
                            double oghealth = ES2->GetOgHealth();
                            ES2->SetHealth(ES2->GetHealth() - (ES->GetPower() * ((ES->GetHealth()) / 100)) / sqrt(ES2->GetHealth()));
                            if (ES2->GetTa() == 0)
                            {
                                ES2->SetTa(game->GetTimeStep());
                            }
                            if (ES2->GetHealth() <= 0)
                            {
                                game->AddToKilled(ES2);
                                ES2->SetTd(game->GetTimeStep());
                            }
                            else if (ES2->GetHealth() > 0 && ES2->GetHealth() <= 0.2 * oghealth)
                            {
                                game->addESToUML(ES2);
                            }
                            else
                            {
                                tempListInfected.enqueue(ES2);
                            }
                        }
                    }
                    while (tempListInfected.dequeue(ES2))
                    {
                        game->GetEA()->ReAddEarthUnit(ES2);
                    }
                }
                else game->GetEA()->ReAddEarthUnit(ES2);
            }
        }
        else
        {
            game->addESAttack(ES);
            for (int i = 0; i < ES->GetAttackCapacity(); i++)
            {
                if (!game->GetAA()->isEmpty_AS())
                {
                    game->GetAA()->peekAS(AS);
                    if (AS)
                    {
                        game->addESAttack(AS);
                    }
                    game->GetAA()->removeAS(AS);
                    AS->SetHealth(AS->GetHealth() - ((ES->GetPower() * (ES->GetHealth()) / 100) / sqrt(AS->GetHealth())));
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
                        tempList.enqueue(AS);
                    }
                }
            }
            while (tempList.dequeue(AS))
            {
                game->GetAA()->ReAddAlienUnit(AS);
            }
        }
    }
}