#pragma once
#include "fstream"
#include"../Armies/AlienArmy.h"
#include"../Armies/EarthArmy.h"

struct input
{
	int numOfUnits, ES, ET, EG, HU, AS, AM, AD, Prob;
	int maxPowerEarth, minPowerEarth, maxHealthEarth, minHealthEarth, maxCapacityEarth, minCapacityEarth;
	int maxPowerAlien, minPowerAlien, maxHealthAlien, minHealthAlien, maxCapacityAlien, minCapacityAlien;
};

class Game
{

	LinkedQueue <Unit*> KL;
	LinkedQueue <Unit*> TL;

	StackList <HealUnit*> HL;
	int HUcount = 0;

	int KilledCount = 0;
	int TimeStep = 1;

public:

	input in;

	void AddToKilled(Unit* Unit);

	void AddToTempList(Unit* Unit);

	void RemoveFromTempList(Unit* Unit);

	void PrintKilledList();

	void Readinput();

	bool isEmpty_HL();
	bool addHU(int jt, double H, int P, int AttC);
	bool removeHU(HealUnit*& hu);
	void printHL();
	StackList <HealUnit*> getHL();

};