#pragma once
#include"../Unit/AlienSoldier.h"
#include"../Unit/AlienMonster.h"
#include"../Unit/AlienDrone.h"
#include<cstdlib>
#include<ctime>


class AlienArmy
{

	int AlienID = 2000;

	LinkedQueue <AlienSoldier*> AS;
	int AScount = 0;

	DoubleEndedQueueList<AlienDrone*>AD;
	int ADcount = 0;

	bag<AlienMonster*>AM;
	int AMcount = 0;
	int alternating = 0;
public:

	bool isEmpty_AS();
	bool addAS(double H, int P, int AttC);
	bool removeAS(AlienSoldier*& as);
	void printAS();
	LinkedQueue <AlienSoldier*> getAS();

	bool isEmpty_AD();
	bool addAD(double H, int P, int AttC);
	bool removeAD(AlienDrone*& ad1, AlienDrone*& ad2);
	void printAD();
	DoubleEndedQueueList <AlienDrone*> getAD();

	bool isEmpty_AM();
	bool addAM(double H, int P, int AttC);
	bool removeAM(AlienMonster*& am);
	void printAM();
	bag <AlienMonster*> getAM();

	void ReAddAlienUnit(Unit* Unit);
};