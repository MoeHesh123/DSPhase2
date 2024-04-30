#include "Game.h"

void Game::Readinput()
{
	ifstream myfile;
	myfile.open("Game/InputFile.txt");
	if (!(myfile.is_open())) {
		cout << "file not found";
	}
	else
	{
		myfile >> in.numOfUnits;
		myfile >> in.ES >> in.ET >> in.EG >> in.HU;
		myfile >> in.AS >> in.AM >> in.AD;
		myfile >> in.Prob;
		myfile >> in.minPowerEarth >> in.maxPowerEarth >> in.minHealthEarth >> in.maxHealthEarth >> in.minCapacityEarth >> in.maxCapacityEarth;
		myfile >> in.minPowerAlien >> in.maxPowerAlien >> in.minHealthAlien >> in.maxHealthAlien >> in.minCapacityAlien >> in.maxCapacityAlien;
		myfile.close();
	}
}

void Game::ProduceOutput()
{
	ofstream OutputFile("OutputFile.txt");

	Node<Unit*>* Current = KL.getfrontPtr();
	OutputFile << "Td   ID   Tj   Df   Dd   Db" << endl;
	while (Current) 
	{
		OutputFile /*<< Current->getItem()->GetTd()*/ << "  " << Current->getItem()->GetId() << "  " << Current->getItem()->GetJoinTime() << "  " /*<< Current->getItem()->GetDf()<<"" << Current->getItem()->GetDd()<<"" << Current->getItem()->GetDb()*/ << endl;
	    Current = Current->getNext();
	}

	//Output File win/loss/draw
	
	OutputFile << "Earth Army: " << endl;
	OutputFile << "ES ET EG" << endl;
	EarthArmy Earmy;
	OutputFile << Earmy.getEScount() << " " << Earmy.getETcount() << " " << Earmy.getEGcount() << endl;
	//OutputFile << (ESKilledcount / (Earmy.getEScount())) * 100 << " " << (ETKilledcount / (Earmy.getETcount())) * 100 << " " << (EGKilledcount / (Earmy.getEGcount())) * 100 << endl;
	//OutputFile << ((ESKilledcount + ETKilledcount + EGKilledcount) / (Earmy.getEScount() + Earmy.getETcount() + Earmy.getEGcount())) * 100;

	OutputFile << "Alien Army: " << endl;
	OutputFile << "AS AM AD" << endl;
	AlienArmy Aarmy;
	OutputFile << Aarmy.getAScount() << " " << Aarmy.getAMcount() << " " << Aarmy.getADcount() << endl;
	//OutputFile << (ASKilledcount / (Aarmy.getAMcount())) * 100 << " " << (AMKilledcount / (Aarmy.getAMcount())) * 100 << " " << (ADKilledcount / (Aarmy.getADcount())) * 100 << endl;
	//OutputFile << ((ASKilledcount + AMKilledcount + ADKilledcount) / (Aarmy.getAScount() + Aarmy.getAMcount() + Aarmy.getADcount())) * 100;

	OutputFile.close();
}

bool Game::isEmpty_ESUML()
{
	if (ESUMLcount == 0) return true;
	return false;
}

bool Game::addESToUML(EarthSoldier* esptr)
{
	if (esptr)
	{
		int Priority = 1000 - (esptr->GetHealth());
		ESUML.enqueue(esptr, Priority);
		ESUMLcount++;
		return true;
	}
	return false;
}

bool Game::removeESFromUML(EarthSoldier*& esptr, int& pri)
{
	if(isEmpty_ESUML()) return false;
	else
	{
		ESUML.dequeue(esptr, pri);
		ESUMLcount--;
		return true;
	}
}

bool Game::isEmpty_ETUML()
{
	if (ETUMLcount == 0) return true;
	return false;
}

bool Game::addETToUML(EarthTank* etptr)
{
	if (etptr)
	{
		ETUML.enqueue(etptr);
		ETUMLcount++;
		return true;
	}
	return false;
}

bool Game::removeETFromUML(EarthTank*& etptr)
{
	if (isEmpty_ETUML()) return false;
	else
	{
		ETUML.dequeue(etptr);
		ETUMLcount--;
		return true;
	}
}

void Game::printUML()
{
	if (ESUML.isEmpty() && ETUML.isEmpty())
	{
		cout << "No Units In Maintenance List" << endl;
		return;
	}
	cout << (ESUMLcount + ETUMLcount) << " units [";
	priNode<EarthSoldier*>* Traversal1 = ESUML.gethead();
	if (!ESUML.isEmpty())
	{
		while (Traversal1->getNext())
		{
			int Priority = Traversal1->getPri();
			cout << Traversal1->getItem(Priority)->GetId() << ", ";
			Traversal1 = Traversal1->getNext();
		}
		int Priority = Traversal1->getPri();
		cout << Traversal1->getItem(Priority)->GetId();
	}
	Node<EarthTank*>* Traversal2 = ETUML.getfrontPtr();
	if (!ETUML.isEmpty())
	{
		if (!ESUML.isEmpty()) cout << ", ";
		while (Traversal2->getNext())
		{
			cout << Traversal2->getItem()->GetId() << ", ";
			Traversal2 = Traversal2->getNext();
		}
		cout << Traversal2->getItem()->GetId();
	}
	cout << "]" << endl;
}

bool Game::isEmpty_HL()
{
	if (HUcount == 0) return true;
	return false;
}

bool Game::addHU(int jt, double h, int p, int AttC)
{
	EarthArmy ea;
	if (ea.getEarthID() < 999)
	{
		HealUnit* hu = new HealUnit(ea.IncrementEarthID(), jt, h, p, AttC);
		HL.push(hu);
		HUcount++;
		return true;
	}
	return false;
}

bool Game::removeHU(HealUnit*& hu)
{
	if (isEmpty_HL()) return false;
	else
	{
		HL.pop(hu);
		HUcount--;
		return true;
	}
}

void Game::printHL()
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

StackList<HealUnit*> Game::getHL()
{
	return HL;
}

void Game::AddToKilled(Unit* unit)
{
	if (unit != nullptr)
	{
		KL.enqueue(unit);
		KilledCount++;
		if (unit->GetType() == "ES") ESKilledcount++;
		else if (unit->GetType() == "ET") ETKilledcount++;
		else if (unit->GetType() == "EG") EGKilledcount++;
		else if (unit->GetType() == "AS") ASKilledcount++;
		else if (unit->GetType() == "AM") AMKilledcount++;
		else ADKilledcount++;
	}
}

void Game::PrintKilledList()
{
	if (KL.isEmpty())
	{
		cout << "No Killed Units" << endl;
		return;
	}
	cout << KilledCount << " units [";
	Node<Unit*>* Traversal = KL.getfrontPtr();
	while (Traversal->getNext())
	{
		cout << Traversal->getItem()->GetId() << ", ";
		Traversal = Traversal->getNext();
	}
	cout << Traversal->getItem()->GetId();
	cout << "]" << endl;
}

void Game::AddToTempList(Unit* unit)
{
	if (unit != nullptr) TL.enqueue(unit);
}

void Game::RemoveFromTempList(Unit* unit)
{
	TL.dequeue(unit);
}