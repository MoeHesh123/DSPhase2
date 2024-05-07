#pragma once
#include"../Unit/EarthGunnery.h"
#include"../Unit/EarthSoldier.h"
#include"../Unit/EarthTank.h"

class EarthArmy
{

	int EarthID;

	LinkedQueue <EarthSoldier*> ES;
	int EScount;

	StackList <EarthTank*> ET;
	int ETcount;

	priQueue <EarthGunnery*> EG;
	int EGcount;

	int EarthCount;

public:

	EarthArmy();

	int GetEarthCount();

	bool isEmpty_ES();
	bool addES(int jt, double H, int P, int AttC);
	bool removeES(EarthSoldier*& es);
	void printES();
	LinkedQueue <EarthSoldier*> getES();
	int getEScount();
	bool peekES(EarthSoldier*& es);

	bool isEmpty_ET();
	bool addET(int jt, double H, int P, int AttC);
	bool removeET(EarthTank*& et);
	void printET();
	StackList <EarthTank*> getET();
	int getETcount();
	bool peekET(EarthTank*& et);

	bool isEmpty_EG();
	bool addEG(int jt, double H, int P, int AttC);
	bool removeEG(EarthGunnery*& eg, int& pri);
	void printEG();
	priQueue <EarthGunnery*> getEG();
	int getEGcount();
	bool peekEG(EarthGunnery*& eg, int& pri);

	int getEarthID();
	int IncrementEarthID();

	void ReAddEarthUnit(Unit* Unit);

};