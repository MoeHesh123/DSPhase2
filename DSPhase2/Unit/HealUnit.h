#pragma once
#include "Unit.h"
class Game;
class HealUnit : public Unit
{

	string type = "HU";

public:

	HealUnit(int ID, int JT, double H, int P, int AC);
	string GetType();
	//void Attack(Game*& game);
	void Attack();

};