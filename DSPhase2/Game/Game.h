#pragma once
#include "fstream"
#include"../Armies/AlienArmy.h"
#include"../Armies/EarthArmy.h"

struct input
{
	int numOfUnits, ES, ET, EG, AS, AM, AD, Prob;
	int maxPowerEarth, minPowerEarth, maxHealthEarth, minHealthEarth, maxCapacityEarth, minCapacityEarth;
	int maxPowerAlien, minPowerAlien, maxHealthAlien, minHealthAlien, maxCapacityAlien, minCapacityAlien;
};

class Game
{

	LinkedQueue <Unit*> KL;
	LinkedQueue <EarthSoldier*> TLES;
	LinkedQueue <EarthTank*> TLET;
	LinkedQueue <EarthGunnery*> TLEG;
	LinkedQueue <AlienSoldier*> TLAS;
	LinkedQueue <AlienDrone*> TLAD;
	LinkedQueue <AlienMonster*> TLAM;

	int KilledCount = 0;
	int TimeStep = 1;

public:

	input in;

	void AddESToKilled(EarthSoldier* es);
	void AddETToKilled(EarthTank* et);
	void AddEGToKilled(EarthGunnery* eg);
	void AddASToKilled(AlienSoldier* as);
	void AddADToKilled(AlienDrone* ad);
	void AddAMToKilled(AlienMonster* am);

	void AddESToTempList(EarthSoldier* es);
	void AddETToTempList(EarthTank* et);
	void AddEGToTempList(EarthGunnery* eg);
	void AddASToTempList(AlienSoldier* as);
	void AddADToTempList(AlienDrone* ad);
	void AddAMToTempList(AlienMonster* am);

	void RemoveESFromTempList(EarthSoldier* es);
	void RemoveETFromTempList(EarthTank* et);
	void RemoveEGFromTempList(EarthGunnery* eg);
	void RemoveASFromTempList(AlienSoldier* as);
	void RemoveADFromTempList(AlienDrone* ad);
	void RemoveAMFromTempList(AlienMonster* am);

	void PrintKilledList();
	void Readinput();

};