#pragma once
#include "Unit.h"

class SaverUnit : public Unit
{

	string type = "SU";

public:

	SaverUnit(int ID, int JT, double H, int P, int AC);
	string GetType();
	void Attack(Game* game);

};