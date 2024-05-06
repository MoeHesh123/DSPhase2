#pragma once
#include"../Unit/AlienSoldier.h"
#include"../Unit/AlienMonster.h"
#include"../Unit/AlienDrone.h"
#include<cstdlib>
#include<ctime>


class AlienArmy
{

	int AlienID;

	LinkedQueue <AlienSoldier*> AS;
	int AScount;

	DoubleEndedQueueList<AlienDrone*>AD;
	int ADcount;

	bag<AlienMonster*>AM;
	int AMcount;
	int alternating;

	int AlienCount;

public:

	AlienArmy();

	int GetAlienCount();

	bool isEmpty_AS();
	bool addAS(int jt, double H, int P, int AttC);
	bool removeAS(AlienSoldier*& as);
	void printAS();
	LinkedQueue <AlienSoldier*> getAS();
	int getAScount();
	bool peekAS(AlienSoldier*& as);

	bool isEmpty_AD();
	bool addAD(int jt, double H, int P, int AttC);
	bool removeAD(AlienDrone*& ad1, AlienDrone*& ad2);
	void printAD();
	DoubleEndedQueueList <AlienDrone*> getAD();
	int getADcount();
	bool peekADfront(AlienDrone*& ad);
	bool peekADback(AlienDrone*& ad);

	bool isEmpty_AM();
	bool addAM(int jt, double H, int P, int AttC);
	bool removeAM(AlienMonster*& am);
	void printAM();
	bag <AlienMonster*> getAM();
	int getAMcount();
	bool peekAM(AlienMonster*& am);

	void ReAddAlienUnit(Unit* Unit);
};