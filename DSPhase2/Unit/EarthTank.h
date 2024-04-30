#pragma once
#include "Unit.h"

class EarthTank : public Unit
{

	string type = "ET";

public:

	EarthTank(int ID, int JT, double H, int P, int AC);
	string GetType();
	void Attack();

};