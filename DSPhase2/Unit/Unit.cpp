#include "Unit.h"

Unit::Unit(int ID, int JT, double H, int P, int AC)
{
	id = ID;
	jointime = JT;
	health = H;
	power = P;
	attackCapacity = AC;
}

int Unit::GetId()
{
	return id;
}

int Unit::GetJoinTime()
{
	return jointime;
}

double Unit::GetHealth()
{
	return health;
}

int Unit::GetPower()
{
	return power;
}

int Unit::GetAttackCapacity()
{
	return attackCapacity;
}

void Unit::SetHealth(double H)
{
	health = H;
}

void Unit::SetJT(int Timestep)
{
	jointime = Timestep;
}

void Unit::print()
{
	cout << "Unit Health" << GetHealth() << endl;
	cout << "Unit ID" << GetId() << endl;
	cout << "Unit JoinTime" << GetJoinTime() << endl;
	cout << "Unit Power" << GetJoinTime() << endl;
	cout << "Unit AttackCapacity" << GetAttackCapacity() << endl;
	cout << "Unit Type" << GetType() << endl;
}