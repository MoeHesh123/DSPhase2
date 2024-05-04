#pragma once
#include "Unit.h"

class EarthTank : public Unit
{

	string type = "ET";
	int JTUML = 0;

public:

	EarthTank(int ID, int JT, double H, int P, int AC);
	string GetType();
	int GetJTUML();
	void SetJTUML(int jtuml);
	void Attack(Game* game, EarthArmy* eartharmy, AlienArmy* alienarmy);

};