#pragma once
#include <iostream>
using namespace std;

#include"../DataStructures/DoubleEndedQueue.h"
#include"../DataStructures/PriQueue.h"
#include"../DataStructures/Queue.h"
#include"../DataStructures/StackList.h"
#include"../DataStructures/ArrayOfPointers.h"

class Unit
{

protected:

	int id;
	int jointime;
	double health;
	int power;
	int attackCapacity;
	string type;

public:

	Unit(int ID, int JT, double H, int P, int AC);
	virtual int GetId();
	virtual int GetJoinTime();
	virtual double GetHealth();
	virtual int GetPower();
	virtual int GetAttackCapacity();
	virtual string GetType() = 0;
	virtual void SetHealth(double H);
	virtual void SetJT(int Timestep);
	void print();

};