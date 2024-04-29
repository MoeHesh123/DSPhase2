#include "EarthArmy.h"

bool EarthArmy::isEmpty_ES()
{
	if (EScount == 0) return true;
	return false;
}

bool EarthArmy::addES(double h, int p, int AttC)
{
	//Replace the 69 with get join time function in game manager

	if (EarthID < 999)
	{
		EarthSoldier* es = new EarthSoldier(++EarthID, 69, h, p, AttC);
		ES.enqueue(es);
		EScount++;
		return true;
	}
	return false;
}

bool EarthArmy::addESFromTemp(EarthSoldier* esptr)
{
	if (esptr != nullptr)
	{
		ES.enqueue(esptr);
		EScount++;
		return true;
	}
	return false;
}

bool EarthArmy::removeES(EarthSoldier*& es)
{
	if (isEmpty_ES()) return false;
	else
	{
		ES.dequeue(es);
		EScount--;
		return true;
	}
}

void EarthArmy::printES()
{
	if (ES.isEmpty())
	{
		cout << "No Earth Soldiers" << endl;
		return;
	}
	cout << EScount << " ES [";
	Node<EarthSoldier*>* Traversal = ES.getfrontPtr();
	while (Traversal->getNext())
	{
		cout << Traversal->getItem()->GetId() << ", ";
		Traversal = Traversal->getNext();
	}
	cout << Traversal->getItem()->GetId();
	cout << "]" << endl;
}

LinkedQueue <EarthSoldier*> EarthArmy::getES()
{
	return ES;
}

bool EarthArmy::isEmpty_ET()
{
	if (ETcount == 0) return true;
	return false;
}

bool EarthArmy::addET(double h, int p, int AttC)
{
	//Replace the 69 with get join time function in game manager

	if (EarthID < 999)
	{
		EarthTank* et = new EarthTank(++EarthID, 69, h, p, AttC);
		ET.push(et);
		ETcount++;
		return true;
	}
	return false;
}

bool EarthArmy::addETFromTemp(EarthTank* etptr)
{
	if (etptr != nullptr)
	{
		ET.push(etptr);
		ETcount++;
		return true;
	}
	return false;
}

bool EarthArmy::removeET(EarthTank*& et)
{
	if (isEmpty_ET()) return false;
	else
	{
		ET.pop(et);
		ETcount--;
		return true;
	}
}

void EarthArmy::printET()
{
	if (ET.isEmpty())
	{
		cout << "No Earth Tanks" << endl;
		return;
	}
	cout << ETcount << " ET [";
	Node<EarthTank*>* Traversal = ET.gettop();
	StackList<int> S;
	while (Traversal)
	{
		S.push(Traversal->getItem()->GetId());
		Traversal = Traversal->getNext();
	}
	Node<int>* Current = S.gettop();
	while (Current->getNext())
	{
		cout << Current->getItem() << ", ";
		Current = Current->getNext();
	}
	cout << Current->getItem();
	cout << "]" << endl;
}

StackList <EarthTank*> EarthArmy::getET()
{
	return ET;
}

bool EarthArmy::isEmpty_EG()
{
	if (EGcount == 0) return true;
	return false;
}

bool EarthArmy::addEG(double h, int p, int AttC)
{
	//Replace the 69 with get join time function in game manager

	if (EarthID < 999)
	{
		EarthGunnery* eg = new EarthGunnery(++EarthID, 69, h, p, AttC);
		int Priority = h + p;
		EG.enqueue(eg, Priority);
		EGcount++;
		return true;
	}
	return false;
}

bool EarthArmy::addEGFromTemp(EarthGunnery* egptr)
{
	if (egptr != nullptr)
	{
		int Pri = egptr->GetHealth() + egptr->GetPower();
		EG.enqueue(egptr, Pri);
		EGcount++;
		return true;
	}
	return false;
}

bool EarthArmy::removeEG(EarthGunnery*& eg, int& pri)
{
	if (isEmpty_EG()) return false;
	else
	{
		EG.dequeue(eg, pri);
		EGcount--;
		return true;
	}
}

void EarthArmy::printEG()
{
	if (EG.isEmpty())
	{
		cout << "No Earth Gunnery" << endl;
		return;
	}
	cout << EGcount << " EG [";
	priNode<EarthGunnery*>* Traversal = EG.gethead();
	while (Traversal->getNext())
	{
		int Priority = Traversal->getPri();
		cout << Traversal->getItem(Priority)->GetId() << ", ";
		Traversal = Traversal->getNext();
	}
	int Priority = Traversal->getPri();
	cout << Traversal->getItem(Priority)->GetId();
	cout << "]" << endl;
}

priQueue <EarthGunnery*> EarthArmy::getEG()
{
	return EG;
}