#pragma once
#include "Unit.h"

class AlienSoldier : public Unit
{

	string type = "AS";

public:

	AlienSoldier(int ID, int JT, double H, int P, int AC);
	string GetType();
	void Attack(Game*& game, EarthArmy*& eartharmy, AlienArmy*& alienarmy);

};