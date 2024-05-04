#pragma once
#include <iostream>
using namespace std;

#include"../DataStructures/DoubleEndedQueue.h"
#include"../DataStructures/PriQueue.h"
#include"../DataStructures/Queue.h"
#include"../DataStructures/StackList.h"
#include"../DataStructures/ArrayOfPointers.h"

class Game;
class EarthArmy;
class AlienArmy;

class Unit
{
protected:

	int id;
	double health;
	int power;
	int attackCapacity;
	string type;

	int jointime = 0;
	int Ta = 0;
	int Td = 0;
	int Df = 0;
	int Dd = 0;
	int Db = 0;
	double UAP = 0.0;

	int JTUML = 0;

public:

	Unit(int ID, int JT, double H, int P, int AC);
	virtual int GetId();
	virtual double GetHealth();
	virtual int GetPower();
	virtual int GetAttackCapacity();

	virtual int GetJoinTime();
	virtual int GetTa();
	virtual int GetTd();
	virtual int GetDf();
	virtual int GetDd();
	virtual int GetDb();
	virtual double GetUAP();

	virtual void SetJT(int Timestep);
	virtual void SetTa(int ta);
	virtual void SetTd(int td);
	virtual void SetUAP(double damage);
	virtual void SetHealth(double H);

	int GetJTUML();
	void SetJTUML(int jtuml);

	virtual string GetType() = 0;
	virtual void Attack(Game* game, EarthArmy* eartharmy, AlienArmy* alienarmy) = 0;
};