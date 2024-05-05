#pragma once
#include "fstream"
#include <iomanip>
#include"../Armies/AlienArmy.h"
#include"../Armies/EarthArmy.h"

class RandGen;

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

	priQueue <EarthSoldier*> ESUML;
	int ESUMLcount = 0;

	LinkedQueue <EarthTank*> ETUML;
	int ETUMLcount = 0;

	int HealedCount = 0;

	float KilledCount = 0;
	float ESKilledcount = 0;
	float ETKilledcount = 0;
	float EGKilledcount = 0;
	float ASKilledcount = 0;
	float AMKilledcount = 0;
	float ADKilledcount = 0;
	float HUKilledcount = 0;

	int TimeStep = 1;

	int EndGame;

public:

	input in;

	void AddToKilled(Unit* Unit);
	void PrintKilledList();

	void Readinput();
	void ProduceOutput(Game* game, EarthArmy* earmy, AlienArmy* Aarmy);

	bool isEmpty_HL();
	bool addHU(int jt, double H, int P, int AttC, EarthArmy*& earmy);
	bool removeHU(HealUnit*& hu);
    void ReAddHealUnit(HealUnit* hu);
	void printHL();
	bool PeekHU(HealUnit*& HU);

	bool isEmpty_ESUML();
	bool addESToUML(EarthSoldier* esptr);
	bool removeESFromUML(EarthSoldier*& esptr, int& pri);
	//bool CheckESUMLKilled();

	bool isEmpty_ETUML();
	bool addETToUML(EarthTank* etptr);
	bool removeETFromUML(EarthTank*& etptr);
	//bool CheckETUMLKilled();

	void printUML();

	int GetHealedCount();
	void IncrementHealedCount();

	void StartGame();
	int GetTimeStep();
	void SetTimeStep(int TS);

	bool ContinueGame(Game* game, EarthArmy* earmy, AlienArmy* aarmy);
	void SetEndGameCondition(int flag);
	int GetEndGameCondition();
};