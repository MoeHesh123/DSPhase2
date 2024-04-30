#pragma once
#include "Unit.h"

class AlienMonster : public Unit
{

	string type = "AM";

public:

	AlienMonster(int ID, int JT, double H, int P, int AC);
	string GetType();
	void Attack();

};