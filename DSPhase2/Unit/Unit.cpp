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

int Unit::GetJoinTime()
{
	return jointime;
}

int Unit::GetTa()
{
	return Ta;
}

int Unit::GetTd()
{
	return Td;
}

int Unit::GetDf()
{
	return (Ta - jointime);
}

int Unit::GetDd()
{
	return (Td - Ta);
}

int Unit::GetDb()
{
	return (Td - jointime);
}

double Unit::GetUAP()
{
	return UAP;
}

double Unit::GetOgHealth()
{
	return OriginalHealth;
}

void Unit::SetJT(int Timestep)
{
	jointime = Timestep;
}

void Unit::SetTa(int ta)
{
	Ta = ta;
}

void Unit::SetTd(int td)
{
	Td = td;
}

void Unit::SetUAP(double damage)
{
	UAP = damage;
}

void Unit::SetHealth(double H)
{
	health = H;
}

void Unit::SetOgHealth(double H)
{
	OriginalHealth = H;
}

int Unit::GetJTUML()
{
	return JTUML;
}

void Unit::SetJTUML(int jtuml)
{
	JTUML = jtuml;
}

bool Unit::GetInfectedCheck()
{
	return InfectedCheck;
}

void Unit::SetInfectedCheck(bool Infected)
{
	InfectedCheck = Infected;
}

bool Unit::GetImmunity()
{
	return Immunity;
}

void Unit::SetImmunity(bool immunity)
{
	Immunity = immunity;
}