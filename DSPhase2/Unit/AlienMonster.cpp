#include "AlienMonster.h"
#include "../Game/Game.h"
#include "../Armies/AlienArmy.h"

AlienMonster::AlienMonster(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string AlienMonster::GetType()
{
    return type;
}

void AlienMonster::Attack(Game* game, EarthArmy* eartharmy, AlienArmy* alienarmy)
{
    LinkedQueue<EarthSoldier*>tempES;
    LinkedQueue<EarthTank*>tempET;
    AlienMonster* AM = nullptr;
    EarthSoldier* ES = nullptr;
    EarthTank* ET = nullptr;
    //int index = 0;
    double oghealthES = 0;
    double oghealthET = 0;
    int attackCes = 0;
    int attackCet = 0;
    //Don't forget og heatlth of ET and ES ibnside the for loop
    alienarmy->peekAM(AM);
    {
        attackCes = (AM->GetAttackCapacity() / 2);
        attackCet = (AM->GetAttackCapacity() - attackCes);
        for (int i = 0; i < attackCes; i++)
        {
            if (!eartharmy->isEmpty_ES())
            {
                eartharmy->removeES(ES);
                oghealthES = ES->GetHealth();
                ES->SetHealth(ES->GetHealth() - (AM->GetPower() * ((AM->GetHealth()) / 100)) / sqrt(ES->GetHealth()));
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
        for (int i = 0; i < attackCet; i++)
        {
            if (!eartharmy->isEmpty_ET())
            {
                eartharmy->removeET(ET);
                oghealthET = ET->GetHealth();
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
    while (tempES.dequeue(ES))
    {
        eartharmy->ReAddEarthUnit(ES);
    }
    while (tempET.dequeue(ET))
    {
        eartharmy->ReAddEarthUnit(ET);

    }
}