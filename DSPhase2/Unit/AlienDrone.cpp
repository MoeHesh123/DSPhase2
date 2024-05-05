#include "AlienDrone.h"
#include "../Game/Game.h"
#include "../Armies/AlienArmy.h"

AlienDrone::AlienDrone(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string AlienDrone::GetType()
{
    return type;
}

void AlienDrone::Attack(Game* game, EarthArmy* eartharmy, AlienArmy* alienarmy)
{
    LinkedQueue<EarthGunnery*> tempEG;
    LinkedQueue<EarthTank*> tempET;
    EarthGunnery* EG = nullptr;
    EarthTank* ET = nullptr;
    AlienDrone* ADFront= nullptr;
    AlienDrone* ADBack=nullptr;
    int pri = 0;
    int attackETF=0;
    int attackEGF = 0;
    int attackETB = 0;
    int attackEGB = 0;
    double oghealthB = 0;
    if (alienarmy->getADcount() > 1)
    {
        alienarmy->peekADback(ADBack);

        attackEGB = ADBack->GetAttackCapacity() / 2; 
        attackETB = ADBack->GetAttackCapacity() - attackEGB;
        if (attackEGB == 0)
        {
            attackEGB = 1;
        }
        for (int i = 0; i < attackEGB; i++)
        {
            if (!eartharmy->isEmpty_EG())
            {
                eartharmy->removeEG(EG,pri);
                EG->SetHealth(EG->GetHealth() - (ADBack->GetPower() * ((ADBack->GetHealth()) / 100)) / sqrt(EG->GetHealth()));
                if (EG->GetTa() == 0)
                {
                    EG->SetTa(game->GetTimeStep()); 
                }
                if (EG->GetHealth() <= 0) 
                {
                    game->AddToKilled(EG); 
                    EG->SetTd(game->GetTimeStep()); 

                }
                else
                {
                    tempEG.enqueue(EG); 
                 
                }

            }
        }
        for (int i = 0; i < attackETB; i++)
        {
            if (!eartharmy->isEmpty_ET())
            {
                eartharmy->removeET(ET);
                oghealthB = ET->GetHealth();
                ET->SetHealth(ET->GetHealth() - (ADBack->GetPower() * ((ADBack->GetHealth()) / 100)) / sqrt(ET->GetHealth()));
                if (ET->GetTa() == 0)
                {
                    ET->SetTa(game->GetTimeStep());
                }
                if (ET->GetHealth() <= 0)
                {
                    game->AddToKilled(ET);
                    ET->SetTd(game->GetTimeStep());

                }
                else if (ET->GetHealth() > 0 && ET->GetHealth() < 0.2 * oghealthB)
                {
                    game->addETToUML(ET);
                }
                else
                {
                    tempET.enqueue(ET);
                }


            }
        }
        alienarmy->peekADfront(ADFront);
        attackEGF = (ADFront->GetAttackCapacity() / 2); 
        attackETF = (ADFront->GetAttackCapacity() - attackEGF); 
        if (attackEGF==0)
        {
            attackEGF = 1;
        }
        for (int i = 0; i < attackETF; i++) 
        {
            if (!eartharmy->isEmpty_ET())
            {
                eartharmy->removeET(ET);
                double oghealth = ET->GetHealth();
                ET->SetHealth(ET->GetHealth() - (ADFront->GetPower() * ((ADFront->GetHealth()) / 100)) / sqrt(ET->GetHealth())); 
                if (ET->GetTa() == 0)
                {
                    ET->SetTa(game->GetTimeStep());
                }
                if (ET->GetHealth() <= 0)
                {
                    game->AddToKilled(ET);
                    ET->SetTd(game->GetTimeStep());
                }
                else if (ET->GetHealth() > 0 && ET->GetHealth() < 0.2 * oghealth)
                {
                    game->addETToUML(ET);
                }
                else
                {
                    tempET.enqueue(ET);
                }
            }

        }
        for (int i = 0; i < attackEGF; i++)
        {
            if (!eartharmy->isEmpty_EG())
            {
                eartharmy->removeEG(EG, pri); 
                EG->SetHealth(EG->GetHealth() - (ADFront->GetPower() * ((ADFront->GetHealth()) / 100)) / sqrt(EG->GetHealth()));
                if (EG->GetTa() == 0)
                {
                    EG->SetTa(game->GetTimeStep());
                }
                if (EG->GetHealth() <= 0)
                {
                    game->AddToKilled(EG);
                    EG->SetTd(game->GetTimeStep());

                }
                else
                {
                    tempEG.enqueue(EG);
                }
            }
        }
        while (tempEG.dequeue(EG))
        {
            alienarmy->ReAddAlienUnit(EG);
        }
        while (tempET.dequeue(ET))
        {
            alienarmy->ReAddAlienUnit(ET);
        }
    }

}
