#pragma once
#include "Unit.h"

class EarthGunnery : public Unit
{

	string type = "EG";

public:

	EarthGunnery(int ID, int JT, double H, int P, int AC);
	string GetType();
	void Attack(Game* game);

};