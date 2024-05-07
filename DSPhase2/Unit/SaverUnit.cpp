#include "SaverUnit.h"
#include "../Game/Game.h"
#include "../Armies/AllyArmy.h"

SaverUnit::SaverUnit(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string SaverUnit::GetType()
{
	return type;
}

void SaverUnit::Attack(Game* game)
{
    LinkedQueue<AlienSoldier*> tempList;

    SaverUnit* SU = nullptr;
    AlienSoldier* AS = nullptr;

    game->GetAllies()->peekSU(SU);
    if (SU)
    {
        game->addSUAttack(SU);
    }
    for (int i = 0; i < SU->GetAttackCapacity(); i++)
    {
        if (!game->GetAA()->isEmpty_AS())
        {
            game->GetAA()->peekAS(AS);
            if (AS)
            {
                game->addESAttack(AS);
            }
            game->GetAA()->removeAS(AS);
            AS->SetHealth(AS->GetHealth() - ((SU->GetPower() * (SU->GetHealth()) / 100) / sqrt(AS->GetHealth())));
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