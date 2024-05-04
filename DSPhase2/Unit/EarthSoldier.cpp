#include "EarthSoldier.h"
#include "../Game/Game.h"
#include "../Armies/EarthArmy.h"

EarthSoldier::EarthSoldier(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string EarthSoldier::GetType()
{
    return type;
}

int EarthSoldier::GetJTUML()
{
    return JTUML;
}

void EarthSoldier::SetJTUML(int jtuml)
{
    JTUML = jtuml;
}

void EarthSoldier::Attack(Game* game, EarthArmy* eartharmy, AlienArmy* alienarmy)
{
    LinkedQueue<AlienSoldier*> tempList;
    EarthSoldier* ES;
    AlienSoldier* AS;
    eartharmy->peekES(ES);

    for (int i = 0; i < ES->GetAttackCapacity(); i++)
    {
        
        if (!alienarmy->isEmpty_AS()) 
        {
            alienarmy->removeAS(AS); 
            AS->SetHealth(AS->GetHealth() - ((ES->GetPower() * (ES->GetHealth()) / 100) / sqrt(AS->GetHealth())));
            if (AS->GetTa() == 0)
            {
                AS->SetTa( game->GetTimeStep());
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
        alienarmy->ReAddAlienUnit(AS);
    }
}