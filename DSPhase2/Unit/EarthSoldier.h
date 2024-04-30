#pragma once
#include "Unit.h"

class EarthSoldier : public Unit
{

	string type = "ES";

public:

	EarthSoldier(int ID, int JT, double H, int P, int AC);
	string GetType();
	void Attack();

};