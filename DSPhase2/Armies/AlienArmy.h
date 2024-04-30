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
	bool addAS(int jt, double H, int P, int AttC);
	bool removeAS(AlienSoldier*& as);
	void printAS();
	LinkedQueue <AlienSoldier*> getAS();
	int getAScount();

	bool isEmpty_AD();
	bool addAD(int jt, double H, int P, int AttC);
	bool removeAD(AlienDrone*& ad1, AlienDrone*& ad2);
	void printAD();
	DoubleEndedQueueList <AlienDrone*> getAD();
	int getADcount();

	bool isEmpty_AM();
	bool addAM(int jt, double H, int P, int AttC);
	bool removeAM(AlienMonster*& am);
	void printAM();
	bag <AlienMonster*> getAM();
	int getAMcount();

	void ReAddAlienUnit(Unit* Unit);
};