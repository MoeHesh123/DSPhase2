#pragma once
#include"../Unit/EarthGunnery.h"
#include"../Unit/EarthSoldier.h"
#include"../Unit/EarthTank.h"

class EarthArmy
{

	int EarthID = 0;

	LinkedQueue <EarthSoldier*> ES;
	int EScount = 0;

	StackList <EarthTank*> ET;
	int ETcount = 0;

	priQueue <EarthGunnery*> EG;
	int EGcount = 0;

public:

	bool isEmpty_ES();
	bool addES(double H, int P, int AttC);
	bool addESFromTemp(EarthSoldier* esptr);
	bool removeES(EarthSoldier*& es);
	void printES();
	LinkedQueue <EarthSoldier*> getES();

	bool isEmpty_ET();
	bool addET(double H, int P, int AttC);
	bool addETFromTemp(EarthTank* etptr);
	bool removeET(EarthTank*& et);
	void printET();
	StackList <EarthTank*> getET();

	bool isEmpty_EG();
	bool addEG(double H, int P, int AttC);
	bool addEGFromTemp(EarthGunnery* egptr);
	bool removeEG(EarthGunnery*& eg, int& pri);
	void printEG();
	priQueue <EarthGunnery*> getEG();

};