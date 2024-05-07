#include "AllyArmy.h"

AllyArmy::AllyArmy()
{
	AllyID = 3000;
	SUcount = 0;
}

int AllyArmy::GetSaverCount()
{
	return SUcount;
}

bool AllyArmy::isEmpty_SU()
{
	if (SUcount == 0) return true;
	return false;
}

bool AllyArmy::addSU(int jt, double h, int p, int AttC)
{
	if (AllyID < 3999)
	{
		SaverUnit* su = new SaverUnit(++AllyID, jt, h, p, AttC);
		SU.enqueue(su);
		SUcount++;
		return true;
	}
	return false;
}

bool AllyArmy::removeSU(SaverUnit*& su)
{
	if (isEmpty_SU()) return false;
	else
	{
		SU.dequeue(su);
		SUcount--;
		return true;
	}
}

void AllyArmy::printSU()
{
	if (SU.isEmpty())
	{
		cout << "No Saver Units" << endl;
		return;
	}
	cout << SUcount << " SU [";
	Node<SaverUnit*>* Traversal = SU.getfrontPtr();
	while (Traversal->getNext())
	{
		cout << Traversal->getItem()->GetId() << ", ";
		Traversal = Traversal->getNext();
	}
	cout << Traversal->getItem()->GetId();
	cout << "]" << endl;
}

LinkedQueue<SaverUnit*> AllyArmy::getSU()
{
	return SU;
}

bool AllyArmy::peekSU(SaverUnit*& su)
{
	if (isEmpty_SU()) return false;
	SU.peek(su);
	return true;
}

void AllyArmy::ReAddSaverUnit(SaverUnit* su)
{
	if (su)
	{
		SU.enqueue(su);
		SUcount++;
	}
}