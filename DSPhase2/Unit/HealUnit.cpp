#include "HealUnit.h"
#include"../Game/Game.h"

HealUnit::HealUnit(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string HealUnit::GetType()
{
	return type;
}

void HealUnit::Attack(Game*& game)
{
	LinkedQueue<Unit*> Temp;
	Node<Unit*>* Current = nullptr;
	if (!(game->isEmpty_ESUML())) 
	{



	}

}
