#pragma once
#include "Unit.h"

class EarthSoldier : public Unit
{

	string type = "ES";
	int JTUML = 0;

public:

	EarthSoldier(int ID, int JT, double H, int P, int AC);
	string GetType();
	int GetJTUML();
	void SetJTUML(int jtuml);
	void Attack(Game* game, EarthArmy* eartharmy, AlienArmy* alienarmy);

};