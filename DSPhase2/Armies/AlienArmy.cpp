#include "AlienArmy.h"

AlienArmy::AlienArmy()
{
	AlienID = 2000;
	AScount = 0;
	ADcount = 0;
	AMcount = 0;
	alternating = 0;
	AlienCount = 0;
}

int AlienArmy::GetAlienCount()
{
	return (AScount + ADcount + AMcount);
}

bool AlienArmy::isEmpty_AS()
{
	if (AScount == 0) return true;
	return false;
}

bool AlienArmy::addAS(int jt, double h, int p, int AttC)
{
	if (AlienID < 2999)
	{
		AlienSoldier* as = new AlienSoldier(++AlienID, jt, h, p, AttC);
		as->SetOgHealth(h);
		AS.enqueue(as);
		AScount++;
		return true;
	}
	return false;
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

int AlienArmy::getAScount()
{
	return AScount;
}

bool AlienArmy::peekAS(AlienSoldier*& as)
{
	if (isEmpty_AS()) return false;
	AS.peek(as);
	return true;
}

bool AlienArmy::isEmpty_AD()
{
	if (ADcount == 0) return true;
	return false;
}

bool AlienArmy::addAD(int jt, double h, int p, int AttC)
{
	if (AlienID < 2999)
	{
		AlienDrone* ad = new AlienDrone(++AlienID, jt, h, p, AttC);
		ad->SetOgHealth(h);
		AD.enqueue(ad);
		ADcount++;
		return true;
	}
	return false;
}

bool AlienArmy::removeAD(AlienDrone*& ad1, AlienDrone*& ad2)
{
	if (isEmpty_AD())
	{
		ad1 = ad2 = nullptr;
		return false;
	}
	else if(ADcount == 1)
	{
		AD.dequeue(ad1);
		ad2 = nullptr;
		ADcount--;
		return true;
	}
	else if (ADcount == 2)
	{
		AD.dequeue(ad1);
		AD.dequeue(ad2);
		ADcount = ADcount - 2;
		return true;
	}
	else
	{
		AD.dequeueBack(ad1);
		AD.dequeue(ad2);
		ADcount = ADcount - 2;
		return true;
	}
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

int AlienArmy::getADcount()
{
	return ADcount;
}

bool AlienArmy::peekADfront(AlienDrone*& ad)
{
	if (isEmpty_AD()) return false;
	AD.peek(ad);
	return true;
}

bool AlienArmy::peekADback(AlienDrone*& ad)
{
	if (isEmpty_AD()) return false;
	AD.peekBack(ad);
	return true;
}

bool AlienArmy::isEmpty_AM()
{
	if (AMcount == 0) return true;
	return false;
}

bool AlienArmy::addAM(int jt, double h, int p, int AttC)
{
	if (AlienID < 2999)
	{
		AlienMonster* am = new AlienMonster(++AlienID, jt, h, p, AttC);
		am->SetOgHealth(h);
		AM.insert(am);
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
int AlienArmy::getAMcount()
{
	return AMcount;
}
bool AlienArmy::peekAM(AlienMonster*& am)
{
	if (isEmpty_AM()) return false;
	else
	{
		int index = rand() % AMcount;
		AM.peek(am, index);
		return true;
	}
}
void AlienArmy::ReAddAlienUnit(Unit* unit)
{
	if (unit == nullptr) return;
	if (unit->GetType() == "AS")
	{
		AlienSoldier* as = dynamic_cast<AlienSoldier*>(unit);
		AS.enqueue(as);
		AScount++;
	}
	if (unit->GetType() == "AM")
	{
		AlienMonster* am = dynamic_cast<AlienMonster*>(unit);
		AM.insert(am);
		AMcount++;
	}
	if (unit->GetType() == "AD")
	{
		AlienDrone* ad = dynamic_cast<AlienDrone*>(unit);
		if (alternating % 2 == 0) 
		{
			AD.enqueue(ad);
			ADcount++;
			alternating++;
		}
		else 
		{
			AD.enqueueFront(ad);
			ADcount++;
			alternating++;
		}

	}
}

void AlienArmy::AlienArmyAttack(Game* game)
{
	AlienSoldier* AS;
	if (!(isEmpty_AS()))
	{
		peekAS(AS);
		if (AS) AS->Attack(game);
	}

	AlienDrone* AD;
	if (!(isEmpty_AD()))
	{
		peekADfront(AD);
		if (AD) AD->Attack(game);
	}

	AlienMonster* AM;
	if (!(isEmpty_AM()))
	{
		peekAM(AM);
		if (AM) AM->Attack(game);
	}
}