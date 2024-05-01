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

	int jointime;
	int Ta;
	int Td;
	int Df;
	int Dd;
	int Db;
	double UAP;

	int id;
	double health;
	int power;
	int attackCapacity;
	string type;
	int JTUML = 0;

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

	virtual int GetTa();
	virtual int GetTd();
	virtual int GetDf();
	virtual int GetDd();
	virtual int GetDb();
	virtual double GetUAP();
    virtual void SetTa(int ta);
	virtual void SetTd(int td);
	virtual void SetUAP(double damage);
	virtual void Attack() = 0;
	int GetJTUML();
	void SetJTUML(int jtuml);

};