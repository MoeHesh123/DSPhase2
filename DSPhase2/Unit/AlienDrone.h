#pragma once
#include "Unit.h"

class AlienDrone : public Unit
{

	string type = "AD";

public:

	AlienDrone(int ID, int JT, double H, int P, int AC);
	string GetType();

};