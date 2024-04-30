#include "EarthArmy.h"

bool EarthArmy::isEmpty_ES()
{
	if (EScount == 0) return true;
	return false;
}

bool EarthArmy::addES(int jt, double h, int p, int AttC)
{
	if (EarthID < 999)
	{
		EarthSoldier* es = new EarthSoldier(++EarthID, jt, h, p, AttC);
		ES.enqueue(es);
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

bool EarthArmy::addET(int jt, double h, int p, int AttC)
{
	if (EarthID < 999)
	{
		EarthTank* et = new EarthTank(++EarthID, jt, h, p, AttC);
		ET.push(et);
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

bool EarthArmy::addEG(int jt, double h, int p, int AttC)
{
	if (EarthID < 999)
	{
		EarthGunnery* eg = new EarthGunnery(++EarthID, jt, h, p, AttC);
		int Priority = h + p;
		EG.enqueue(eg, Priority);
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

bool EarthArmy::isEmpty_HL()
{
	if (HUcount == 0) return true;
	return false;
}

bool EarthArmy::addHU(int jt, double h, int p, int AttC)
{
	if (EarthID < 999)
	{
		HealUnit* hu = new HealUnit(++EarthID, jt, h, p, AttC);
		HL.push(hu);
		HUcount++;
		return true;
	}
	return false;
}

bool EarthArmy::removeHU(HealUnit*& hu)
{
	if (isEmpty_HL()) return false;
	else
	{
		HL.pop(hu);
		HUcount--;
		return true;
	}
}

void EarthArmy::printHL()
{
	if (HL.isEmpty())
	{
		cout << "No Heal Units" << endl;
		return;
	}
	cout << HUcount << " HU [";
	Node<HealUnit*>* Traversal = HL.gettop();
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

StackList<HealUnit*> EarthArmy::getHL()
{
	return HL;
}

void EarthArmy::ReAddEarthUnit(Unit* unit)
{
	if (unit == nullptr) return;
	if (unit->GetType() == "ES")
	{
		EarthSoldier* es = dynamic_cast<EarthSoldier*>(unit);
		ES.enqueue(es);
		EScount++;
	}
	if (unit->GetType() == "ET")
	{
		EarthTank* et = dynamic_cast<EarthTank*>(unit);
		ET.push(et);
		EScount++;
	}
	if (unit->GetType() == "EG")
	{
		EarthGunnery* eg = dynamic_cast<EarthGunnery*>(unit);
		int Pri = eg->GetHealth() + eg->GetPower();
		EG.enqueue(eg, Pri);
		EGcount++;
	}
}