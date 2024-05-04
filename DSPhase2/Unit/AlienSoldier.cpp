#include "AlienSoldier.h"
#include "../Game/Game.h"
#include "../Armies/AlienArmy.h"

AlienSoldier::AlienSoldier(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string AlienSoldier::GetType()
{
    return type;
}

void AlienSoldier::Attack(Game* game, EarthArmy* eartharmy, AlienArmy* alienarmy)
{
    LinkedQueue<EarthSoldier*>templistES;
    AlienSoldier* ASp = nullptr;
    EarthSoldier* ESp = nullptr;
    alienarmy->peekAS(ASp);

    for (int i = 0; i < attackCapacity; i++)
    {
        eartharmy->removeES(ESp);
        if (ESp)
        {
            double oghealth = ESp->GetHealth();
            ESp->SetHealth(ESp->GetHealth() - (ASp->GetPower() * ((ASp->GetHealth()) / 100)) / sqrt(ESp->GetHealth()));
            if (ESp->GetTa() == 0)
            {
                ESp->SetTa(game->GetTimeStep());
            }
            if (ESp->GetHealth() <= 0)
            {
                game->AddToKilled(ESp);

                ESp->SetTd(game->GetTimeStep());
            }
            else if (ESp->GetHealth() > 0 && ESp->GetHealth() < 0.2 * oghealth)
            {
                game->addESToUML(ESp);
            }
            else
            {
                templistES.enqueue(ESp);
            }
        }
        while (templistES.dequeue(ESp))
        {
            eartharmy->ReAddEarthUnit(ESp);
        }
    }
}