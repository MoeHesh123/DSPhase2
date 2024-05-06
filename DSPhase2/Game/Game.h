#pragma once
#include "fstream"
#include <iomanip>
#include"../Armies/AlienArmy.h"
#include"../Armies/EarthArmy.h"

class RandGen;

enum EndGameConditions 
{
	Neutral = 0,
	Lose = 1,
	Win = 2,
	Draw = 3
};

struct input
{
	int numOfUnits, ES, ET, EG, HU, AS, AM, AD, Prob;
	int maxPowerEarth, minPowerEarth, maxHealthEarth, minHealthEarth, maxCapacityEarth, minCapacityEarth;
	int maxPowerAlien, minPowerAlien, maxHealthAlien, minHealthAlien, maxCapacityAlien, minCapacityAlien;
};

class Game
{
	int TimeStep;

	LinkedQueue <Unit*> ESAttack;
	LinkedQueue <Unit*> ETAttack;
	LinkedQueue <Unit*> EGAttack;
	LinkedQueue <Unit*> ASAttack;
	LinkedQueue <Unit*> AMAttack;
	LinkedQueue <Unit*> ADAttack;
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

	EndGameConditions EndGameCondition ;

public:

	Game();

	input in;
	void Readinput();

	void AddToKilled(Unit* Unit);
	void PrintKilledList();

	bool isEmpty_HL();
	bool addHU(int jt, double H, int P, int AttC, EarthArmy*& earmy);
	bool removeHU(HealUnit*& hu);
    void ReAddHealUnit(HealUnit* hu);
	void printHL();
	bool PeekHU(HealUnit*& HU);
	void IncrementHealedCount();

	bool isEmpty_ESUML();
	bool addESToUML(EarthSoldier* esptr);
	bool removeESFromUML(EarthSoldier*& esptr, int& pri);

	bool isEmpty_ETUML();
	bool addETToUML(EarthTank* etptr);
	bool removeETFromUML(EarthTank*& etptr);

	void printUML();

	bool addESAttack(Unit* unit);
	bool addETAttack(Unit* unit);
	bool addEGAttack(Unit* unit);
	bool addASAttack(Unit* unit);
	bool addAMAttack(Unit* unit);
	bool addADAttack(Unit* unit);
	void printAttacking();

	void StartGame();
	int GetTimeStep();

	bool CheckGameEnded(EarthArmy* earmy, AlienArmy* aarmy);

	void ProduceOutput(EarthArmy* earmy, AlienArmy* Aarmy);
};