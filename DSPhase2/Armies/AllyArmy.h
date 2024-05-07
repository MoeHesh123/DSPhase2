#pragma once
#include "../Unit/SaverUnit.h"

class AllyArmy
{
	int AllyID;

	LinkedQueue <SaverUnit*> SU;
	int SUcount;

public:

	AllyArmy();

	int GetSaverCount();
	bool isEmpty_SU();
	bool addSU(int jt, double h, int p, int AttC);
	bool removeSU(SaverUnit*& su);
	void printSU();
	LinkedQueue <SaverUnit*> getSU();
	bool peekSU(SaverUnit*& su);
	void ReAddSaverUnit(SaverUnit* su);

};