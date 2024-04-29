#include "AlienArmy.h"

bool AlienArmy::isEmpty_AS()
{
	if (AScount == 0) return true;
	return false;
}

bool AlienArmy::addAS(double h, int p, int AttC)
{
	//Replace the 69 with get join time function in game manager

	if (AlienID < 2999)
	{
		AlienSoldier* as = new AlienSoldier(++AlienID, 69, h, p, AttC);
		AS.enqueue(as);
		AScount++;
		return true;
	}
	return false;
}

bool AlienArmy::addASFromTemp(AlienSoldier* asptr)
{
	if (asptr != nullptr)
	{
		AS.enqueue(asptr);
		AScount++;
		return true;
	}
	return false;
	//if (unit->GetType() == "AS");
    //if (unit->GetType() == "AD");
    //if (unit->GetType() == "AM");
}

bool AlienArmy::removeAS(AlienSoldier*& as)
{
	if (isEmpty_AS())
	{
		as = nullptr;
		return false;
	}
	else
	{
		AS.dequeue(as);
		AScount--;
		return true;
	}
}

void AlienArmy::printAS()
{
	if (AS.isEmpty())
	{
		cout << "No Alien Soldiers" << endl;
		return;
	}
	cout << AScount << " AS [";
	Node<AlienSoldier*>* Traversal = AS.getfrontPtr();
	while (Traversal->getNext())
	{
		cout << Traversal->getItem()->GetId() << ", ";
		Traversal = Traversal->getNext();
	}
	cout << Traversal->getItem()->GetId();
	cout << "]" << endl;
}

LinkedQueue <AlienSoldier*> AlienArmy::getAS()
{
	return AS;
}

bool AlienArmy::isEmpty_AD()
{
	if (ADcount == 0) return true;
	return false;
}

bool AlienArmy::addAD(double h, int p, int AttC)
{
	//Replace the 69 with get join time function in game manager

	if (AlienID < 2999)
	{
		AlienDrone* ad = new AlienDrone(++AlienID, 69, h, p, AttC);
		AD.enqueue(ad);
		ADcount++;
		return true;
	}
	return false;
}

bool AlienArmy::addADFromTemp(AlienDrone* adptr1, AlienDrone* adptr2)
{
	if (adptr1 != nullptr && adptr2 != nullptr)
	{
		AD.enqueue(adptr1);
		AD.enqueueFront(adptr2);
		ADcount = ADcount + 2;
		return true;
	}
	return false;
}

bool AlienArmy::removeAD(AlienDrone*& ad1, AlienDrone*& ad2)
{
	if (isEmpty_AD() || ADcount == 1)
	{
		ad1 = ad2 = nullptr;
		return false;
	}
	else if (ADcount == 2)
	{
		AD.dequeue(ad1);
		AD.dequeue(ad2);
		ADcount = ADcount - 2;
	}
	else
	{
		AD.dequeueBack(ad1);
		AD.dequeue(ad2);
		ADcount = ADcount - 2;
		return true;
	}
	return false;
}

void AlienArmy::printAD()
{
	if (AD.isEmpty())
	{
		cout << "No Alien Drones" << endl;
		return;
	}
	cout << ADcount << " AD [";
	Node<AlienDrone*>* Traversal = AD.getfrontPtr();
	while (Traversal->getNext())
	{
		cout << Traversal->getItem()->GetId() << ", ";
		Traversal = Traversal->getNext();
	}
	cout << Traversal->getItem()->GetId();
	cout << "]" << endl;
}

DoubleEndedQueueList <AlienDrone*> AlienArmy::getAD()
{
	return AD;
}

bool AlienArmy::isEmpty_AM()
{
	if (AMcount == 0) return true;
	return false;
}

bool AlienArmy::addAM(double h, int p, int AttC)
{
	//Replace the 69 with get join time function in game manager

	if (AlienID < 2999)
	{
		AlienMonster* am = new AlienMonster(++AlienID, 69, h, p, AttC);
		AM.insert(am);
		AMcount++;
		return true;
	}
	return false;
}

bool AlienArmy::addAMFromTemp(AlienMonster* amptr)
{
	if (amptr != nullptr)
	{
		AM.insert(amptr);
		AMcount++;
		return true;
	}
	return false;
}

bool AlienArmy::removeAM(AlienMonster*& am)
{
	if (isEmpty_AM()) return false;
	else
	{
		int index = rand() % AMcount;
		AM.remove(am, index);
		AMcount--;
		return true;
	}
}

void AlienArmy::printAM()
{
	if (AM.isEmpty())
	{
		cout << "No Alien Monsters" << endl;
		return;
	}
	cout << AMcount << " AM [";
	for (int i = 0; i < AMcount; i++)
	{
		if (i == AMcount - 1) cout << AM.getitem(i)->GetId();
		else cout << AM.getitem(i)->GetId() << ", ";
	}
	cout << "]" << endl;
}

bag <AlienMonster*> AlienArmy::getAM()
{
	return AM;
}