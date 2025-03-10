#include "Game.h"
#include"../RandGen/RandGen.h"

Game::Game()
{
	EndGameCondition = Neutral;
	TimeStep = 1;
}

void Game::Readinput()
{
	ifstream myfile;
	myfile.open("Game/InputFile.txt");
	if (!(myfile.is_open())) 
	{
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
		myfile >> in.minPowerAlly >> in.maxPowerAlly >> in.minHealthAlly >> in.maxHealthAlly >> in.minCapacityAlly >> in.maxCapacityAlly;
		myfile >> in.InfectionProb >> in.InfectionThreshold;
		myfile.close();
	}
}

void Game::ProduceOutput()
{
	cout << "Please Enter The Output File Name: ";
	string file;
	cin >> file;
	ofstream OutputFile(file + ".txt");

	OutputFile << "============================================================================" << endl;

	OutputFile << "Killed Units: " << KilledCount << endl;
	Node<Unit*>* Current = KL.getfrontPtr();
	OutputFile 
	<< setw(6) << left << "Td"
	<< setw(6) << left << "ID"
	<< setw(6) << left << "Tj"
	<< setw(6) << left << "Df"
	<< setw(6) << left << "Dd"
	<< setw(6) << left << "Db" << endl; 

	float ESumDd = 0, ESumDb = 0, ESumDf = 0, ASumDd = 0, ASumDb = 0, ASumDf = 0, EarthKilled = 0, AlienKilled = 0;

	while (Current) 
	{
		if ((Current->getItem()->GetType() == "ES") || (Current->getItem()->GetType() == "ET") || (Current->getItem()->GetType() == "EG"))
		{
			EarthKilled++;
			ESumDd += Current->getItem()->GetDd();
			ESumDb += Current->getItem()->GetDb();
			ESumDf += Current->getItem()->GetDf();
		}
		else
		{
			AlienKilled++;
			ASumDd += Current->getItem()->GetDd();
			ASumDb += Current->getItem()->GetDb();
			ASumDf += Current->getItem()->GetDf();
		}
		OutputFile
		<< setw(6) << left << Current->getItem()->GetTd()
		<< setw(6) << left << Current->getItem()->GetId()
		<< setw(6) << left << Current->getItem()->GetJoinTime()
		<< setw(6) << left << Current->getItem()->GetDf()
		<< setw(6) << left << Current->getItem()->GetDd()
		<< setw(6) << left << Current->getItem()->GetDb() <<endl;
		Current = Current->getNext();
	}

	OutputFile << "============================================================================" << endl;

	OutputFile << "Battle result: ";
	if (EndGameCondition == 2) OutputFile << "Earth Army Won!";
	else if (EndGameCondition == 1) OutputFile << "Earth Army Lost!";
	else OutputFile << "Draw!";

	OutputFile << endl << "============================================================================" << endl;

	OutputFile
	<< "Total Earth Army Units Alive: " << endl
	<< setw(6) << left << "ES"
	<< setw(6) << left << "ET"
	<< setw(6) << left << "EG"
	<< setw(6) << left << "ESUML" 
	<< setw(6) << left << "ETUML" << endl;
	OutputFile 
	<< setw(6) << left << EA->getEScount()  
	<< setw(6) << left << EA->getETcount() 
	<< setw(6) << left << EA->getEGcount()
	<< setw(6) << left << ESUMLcount
	<< setw(6) << left << ETUMLcount;

	OutputFile << endl << endl << "Percentage Of Destructed Earth Units Relative To Their Total: " << endl
	<< setw(6) << left << "ES"
	<< setw(6) << left << "ET"
	<< setw(6) << left << "EG" << endl;

	if ((EA->getEScount() + ESKilledcount + ESUMLcount) == 0) OutputFile << setw(6) << left << "0";
	else OutputFile << setw(6) << left << round((ESKilledcount / (EA->getEScount() + ESKilledcount + ESUMLcount)) * 100);

	if ((EA->getETcount() + ETKilledcount + ETUMLcount) == 0) OutputFile << setw(6) << left << "0";
	else OutputFile << setw(6) << left << round((ETKilledcount / (EA->getETcount() + ETKilledcount + ETUMLcount)) * 100);

	if ((EA->getEGcount() + EGKilledcount) == 0) OutputFile << setw(6) << left << "0";
	else OutputFile << setw(6) << left << round((EGKilledcount / (EA->getEGcount() + EGKilledcount)) * 100);

	OutputFile << endl << endl << "Percentage Of Earth Units Healed Relative To Their Total: ";
	if ((EA->getEScount() + EA->getETcount() + EA->getEGcount() + EarthKilled + ESUMLcount + ETUMLcount) == 0) OutputFile << "0";
	else OutputFile << round(HealedCount / (EA->getEScount() + EA->getETcount() + EA->getEGcount() + EarthKilled + ESUMLcount + ETUMLcount) * 100);

	OutputFile << endl << endl << "Percentage Of Total Destructed Earth units Relative To Total Earth Units: ";
	if((EA->getEScount() + EA->getETcount() + EA->getEGcount() + EarthKilled + ESUMLcount + ETUMLcount) == 0) OutputFile <<"0";
	else OutputFile << round(EarthKilled / (EA->getEScount() + EA->getETcount() + EA->getEGcount() + EarthKilled + ESUMLcount + ETUMLcount) * 100);

	OutputFile << endl << endl << "Average of Df,Dd & Db for Earth Units:" <<endl
	<< setw(6) << left << "DfAVG"
	<< setw(6) << left << "DdAVG"
	<< setw(6) << left << "DbAVG" << endl;
	if (EarthKilled == 0)
	{
		OutputFile
	    << setw(6) << left << "0"
		<< setw(6) << left << "0"
		<< setw(6) << left << "0";
	}
	else 
	{
		OutputFile
		<< setw(6) << left << round(ESumDf / EarthKilled)
		<< setw(6) << left << round(ESumDd / EarthKilled)
		<< setw(6) << left << round(ESumDb / EarthKilled);
	}

	OutputFile << endl << endl << "Earth Df/Db%: ";
	if (ESumDb == 0) OutputFile << "0";
	else OutputFile << round((ESumDf / ESumDb) * 100);
	OutputFile << endl <<"Earth Dd/Db%: ";
	if (ESumDb == 0) OutputFile << "0";
	else OutputFile << round((ESumDd / ESumDb) * 100);

	OutputFile << endl << "============================================================================" << endl;

	OutputFile
	<< "Total Alien Army Units Alive: " << endl
	<< setw(6) << left << "AS"
	<< setw(6) << left << "AM"
	<< setw(6) << left << "AD" << endl;
	OutputFile
	<< setw(6) << left << AA->getAScount()
	<< setw(6) << left << AA->getAMcount()
	<< setw(6) << left << AA->getADcount();

	OutputFile << endl << endl << "Percentage Of Destructed Alien Units Relative To Their Total: " << endl
	<< setw(6) << left << "AS"
	<< setw(6) << left << "AM"
	<< setw(6) << left << "AD" << endl;

	if ((AA->getAScount() + ASKilledcount) == 0) OutputFile << setw(6) << left << "0";
	else OutputFile << setw(6) << left << round((ASKilledcount / (AA->getAScount() + ASKilledcount)) * 100);

	if ((AA->getAMcount() + AMKilledcount) == 0) OutputFile << setw(6) << left << "0";
	else OutputFile << setw(6) << left << round((AMKilledcount / (AA->getAMcount() + AMKilledcount)) * 100);

	if ((AA->getADcount() + ADKilledcount) == 0) OutputFile << setw(6) << left << "0";
	else OutputFile << setw(6) << left << round((ADKilledcount / (AA->getADcount() + ADKilledcount)) * 100);

	OutputFile << endl << endl << "Percentage Of Total Destructed Alien units Relative To Total Alien Units: ";
	if (((AA->getAScount() + ASKilledcount) + (AA->getAMcount() + AMKilledcount) + (AA->getADcount() + ADKilledcount)) == 0) OutputFile << "0";
    else OutputFile << round((ASKilledcount + AMKilledcount + ADKilledcount) / ((AA->getAScount() + ASKilledcount) + (AA->getAMcount() + AMKilledcount) + (AA->getADcount() + ADKilledcount)) * 100);

	OutputFile << endl << endl << "Average of Df,Dd & Db for Alien Units: " << endl
	<< setw(6) << left << "DfAVG"
	<< setw(6) << left << "DdAVG"
	<< setw(6) << left << "DbAVG" << endl;
	if (AlienKilled == 0)
	{
		OutputFile
		<< setw(6) << left << "0"
		<< setw(6) << left << "0"
		<< setw(6) << left << "0";
	}
	else
	{
		OutputFile
		<< setw(6) << left << round(ASumDf / AlienKilled)
		<< setw(6) << left << round(ASumDd / AlienKilled)
		<< setw(6) << left << round(ASumDb / AlienKilled);
	}

	OutputFile << endl << endl << "Alien Df/Db%: ";
	if (ASumDb == 0) OutputFile << "0";
	else OutputFile << round((ASumDf / ASumDb) * 100);
	OutputFile << endl << "Alien Dd/Db%: ";
	if (ASumDb == 0) OutputFile << "0";
	else OutputFile << round((ASumDd / ASumDb) * 100);

	OutputFile << endl << "============================================================================";
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
		esptr->SetJTUML(TimeStep);
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
		etptr->SetJTUML(TimeStep);
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
			cout << Traversal1->getItem(Priority)->GetId();
			if (Traversal1->getItem(Priority)->GetInfectedCheck()) cout << "<X>";
		    cout << ", ";
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

bool Game::addESAttack(Unit* unit)
{
	if (unit)
	{
		ESAttack.enqueue(unit);
		return true;
	}
	return false;
}

bool Game::addETAttack(Unit* unit)
{
	if (unit)
	{
		ETAttack.enqueue(unit);
		return true;
	}
	return false;
}

bool Game::addEGAttack(Unit* unit)
{
	if (unit)
	{
		EGAttack.enqueue(unit);
		return true;
	}
	return false;
}

bool Game::addASAttack(Unit* unit)
{
	if (unit)
	{
		ASAttack.enqueue(unit);
		return true;
	}
	return false;
}

bool Game::addAMAttack(Unit* unit)
{
	if (unit)
	{
		AMAttack.enqueue(unit);
		return true;
	}
	return false;
}

bool Game::addADAttack(Unit* unit)
{
	if (unit)
	{
		ADAttack.enqueue(unit);
		return true;
	}
	return false;
}

bool Game::addSUAttack(Unit* unit)
{
	if (unit)
	{
		SUAttack.enqueue(unit);
		return true;
	}
	return false;
}

bool Game::addInfectedAttack(Unit* unit)
{
	if (unit)
	{
		InfectedAttack.enqueue(unit);
		return true;
	}
	return false;
}

void Game::printAttacking()
{
	Unit* unit = nullptr;
	if (ESAttack.isEmpty() || ESAttack.getCount() == 1)
	{
		cout << "No Earth Soldiers Attacking" << endl;
		ESAttack.dequeue(unit);
	}
	else
	{
		ESAttack.dequeue(unit);
		Node<Unit*>* Traversal = ESAttack.getfrontPtr();
		cout << "ES " << unit->GetId() << " Shoots [";
		while (Traversal->getNext())
		{
			cout << Traversal->getItem()->GetId() << ", ";
			Traversal = Traversal->getNext();
		}
		cout << Traversal->getItem()->GetId();
		cout << "]" << endl;
		while (ESAttack.dequeue(unit));
	}
	if (ETAttack.isEmpty() || ETAttack.getCount() == 1)
	{
		cout << "No Earth Tanks Attacking" << endl;
		ETAttack.dequeue(unit);
	}
	else
	{
		ETAttack.dequeue(unit);
		Node<Unit*>* Traversal = ETAttack.getfrontPtr();
		cout << "ET " << unit->GetId() << " Shoots [";
		while (Traversal->getNext())
		{
			cout << Traversal->getItem()->GetId() << ", ";
			Traversal = Traversal->getNext();
		}
		cout << Traversal->getItem()->GetId();
		cout << "]" << endl;
		while (ETAttack.dequeue(unit));
	}
	if (EGAttack.isEmpty() || EGAttack.getCount() == 1)
	{
		cout << "No Earth Gunneries Attacking" << endl;
		EGAttack.dequeue(unit);
	}
	else
	{
		EGAttack.dequeue(unit);
		Node<Unit*>* Traversal = EGAttack.getfrontPtr();
		cout << "EG " << unit->GetId() << " Shoots [";
		while (Traversal->getNext())
		{
			cout << Traversal->getItem()->GetId() << ", ";
			Traversal = Traversal->getNext();
		}
		cout << Traversal->getItem()->GetId();
		cout << "]" << endl;
		while (EGAttack.dequeue(unit));
	}
	if (ASAttack.isEmpty() || ASAttack.getCount() == 1)
	{
		cout << "No Alien Soldiers Attacking" << endl;
		ASAttack.dequeue(unit);
	}
	else
	{
		ASAttack.dequeue(unit);
		Node<Unit*>* Traversal = ASAttack.getfrontPtr();
		cout << "AS " << unit->GetId() << " Shoots [";
		while (Traversal->getNext())
		{
			cout << Traversal->getItem()->GetId() << ", ";
			Traversal = Traversal->getNext();
		}
		cout << Traversal->getItem()->GetId();
		cout << "]" << endl;
		while (ASAttack.dequeue(unit));
	}
	if (AMAttack.isEmpty() || AMAttack.getCount() == 1)
	{
		cout << "No Alien Monsters Attacking" << endl;
		AMAttack.dequeue(unit);
	}
	else
	{
		AMAttack.dequeue(unit);
		Node<Unit*>* Traversal = AMAttack.getfrontPtr();
		cout << "AM " << unit->GetId() << " Shoots [";
		while (Traversal->getNext())
		{
			cout << Traversal->getItem()->GetId() << ", ";
			Traversal = Traversal->getNext();
		}
		cout << Traversal->getItem()->GetId();
		cout << "]" << endl;
		while (AMAttack.dequeue(unit));
	}
	if (ADAttack.isEmpty() || ADAttack.getCount() == 2)
	{
		cout << "No Alien Drones Attacking" << endl;
		while (ADAttack.dequeue(unit));
	}
	else
	{
		ADAttack.dequeue(unit);
		cout << "AD " << unit->GetId() << " & AD ";
		ADAttack.dequeue(unit);
		cout << unit->GetId() << " Shoots [";
		Node<Unit*>* Traversal = ADAttack.getfrontPtr();
		while (Traversal->getNext())
		{
			cout << Traversal->getItem()->GetId() << ", ";
			Traversal = Traversal->getNext();
		}
		cout << Traversal->getItem()->GetId();
		cout << "]" << endl;
		while (ADAttack.dequeue(unit));
	}
	if (SUAttack.isEmpty() || SUAttack.getCount() == 1)
	{
		cout << "No Saver Units Attacking" << endl;
		SUAttack.dequeue(unit);
	}
	else
	{
		SUAttack.dequeue(unit);
		Node<Unit*>* Traversal = SUAttack.getfrontPtr();
		cout << "SU " << unit->GetId() << " Shoots [";
		while (Traversal->getNext())
		{
			cout << Traversal->getItem()->GetId() << ", ";
			Traversal = Traversal->getNext();
		}
		cout << Traversal->getItem()->GetId();
		cout << "]" << endl;
		while (SUAttack.dequeue(unit));
	}
	if (InfectedAttack.isEmpty() || InfectedAttack.getCount() == 1)
	{
		cout << "No Infected Earth Soldiers Attacking" << endl;
		InfectedAttack.dequeue(unit);
	}
	else
	{
		InfectedAttack.dequeue(unit);
		Node<Unit*>* Traversal = InfectedAttack.getfrontPtr();
		cout << "ES " << unit->GetId() <<"<X>" << " Shoots [";
		while (Traversal->getNext())
		{
			cout << Traversal->getItem()->GetId() << ", ";
			Traversal = Traversal->getNext();
		}
		cout << Traversal->getItem()->GetId();
		cout << "]" << endl;
		while (InfectedAttack.dequeue(unit));
	}
}

void Game::IncrementHealedCount()
{
	HealedCount++;
}

bool Game::isEmpty_HL()
{
	if (HUcount == 0) return true;
	return false;
}


bool Game::addHU(int jt, double h, int p, int AttC)
{
	if (EA->getEarthID() < 999)
	{
		HealUnit* hu = new HealUnit(EA->IncrementEarthID(), jt, h, p, AttC);
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

void Game::ReAddHealUnit(HealUnit* hu)
{
	HL.push(hu);
	HUcount++;
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

bool Game::PeekHU(HealUnit*& HU)
{
	if (isEmpty_HL()) return false;
	HL.peek(HU);
	return true;
}

EarthArmy* Game::GetEA()
{
	return EA;
}

AlienArmy* Game::GetAA()
{
	return AA;
}

AllyArmy* Game::GetAllies()
{
	return Allies;
}

void Game::AddToKilled(Unit* unit)
{
	if (unit)
	{
		if (unit->GetType() == "ES") 
		{
			KL.enqueue(unit);
			KilledCount++;
			ESKilledcount++;
		}
		else if (unit->GetType() == "ET")
		{
			KL.enqueue(unit);
			KilledCount++;
			ETKilledcount++;
		}
		else if (unit->GetType() == "EG")
		{
			KL.enqueue(unit);
			KilledCount++;
			EGKilledcount++;
		}
		else if (unit->GetType() == "AS")
		{
			KL.enqueue(unit);
			KilledCount++;
			ASKilledcount++;
		}
		else if (unit->GetType() == "AM")
		{
			KL.enqueue(unit);
			KilledCount++;
			AMKilledcount++;
		}
		else if (unit->GetType() == "AD")
		{
			KL.enqueue(unit);
			KilledCount++;
			ADKilledcount++;
		}
		else
		{
			KL.enqueue(unit);
			KilledCount++;
			HUKilledcount++;
		}
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
		cout << Traversal->getItem()->GetId();
		if (Traversal->getItem()->GetInfectedCheck()) cout << "<X>";
		cout << ", ";
		Traversal = Traversal->getNext();
	}
	cout << Traversal->getItem()->GetId();
	cout << "]" << endl;
}

int Game::GetTimeStep()
{
	return TimeStep;
}

void Game::StartGame()
{
	int x = 0;
	cout << "Which Mode Do you like to simulate with ?" << endl;
	cout << "For Interactive Mode Press 1" << endl;
	cout << "For Silent Mode Press 2" << endl;
	cout << "choice: ";
	cin >> x;

	while (x <= 0 || x > 2)
	{
		cout << "Invalid Mode please choose again!" << endl;
		cout << "choice: ";
		cin >> x;
	}
    cin.ignore();


	Readinput();
	srand((unsigned)time(0));

	while (EndGameCondition == Neutral) 
	{
		if (x == 1) cout << endl << "Current TimeStep " << TimeStep << endl;

		randgen->Generate(this);

		EA->EarthArmyAttack(this);
		AA->AlienArmyAttack(this);

		HealUnit* HU;
		if (!isEmpty_HL())
		{
			PeekHU(HU);
			if (HU)	HU->Attack(this);
		}

		SaverUnit* SU;
		if (!(Allies->isEmpty_SU()))
		{
			Allies->peekSU(SU);
			if (SU)	SU->Attack(this);
		}

		if (PercentageOfInfected == 0)
		{
			SaverUnit* SU;
			while (Allies->removeSU(SU));
		}

		if (EA->getEScount() != 0) SetPercentageOfInfected((InfectedCount / EA->getEScount()) * 100);
		if (x == 1)
		{
			cout << endl << "Percentage Of Infected Earth Soliders: " << GetPercentageOfInfected() << endl << endl;
		}

		if (x == 1)
		{
			cout << "==============  Earth Army Alive Units ================" << endl;
			EA->printES();
			EA->printET();
			EA->printEG();
			printHL();

			cout << endl << "============= Unit Maintenance List ===================" << endl;
			printUML();

			cout << endl << "============= Saver Unit List ===================" << endl;
			Allies->printSU();

			cout << endl << "==============  Alien Army Alive Units ================" << endl;
			AA->printAS();
			AA->printAD();
			AA->printAM();

			cout << endl << "============== Units Fighting At Current Step =========" << endl;
			printAttacking();

			cout << endl << "==============  Killed/Destructed Units ===============" << endl;
			PrintKilledList();

			cout << endl << "Press ENTER to move to next timestep" << endl;
			cin.get();
		}
		if (TimeStep >= 40)
		{
			if (CheckGameEnded())
			{
				if (x == 1) cout << "Game Ended !" << endl;
				break;
			}
		}
		TimeStep++;
	}
	if (x == 2)
	{
		ProduceOutput();
		cout << "Silent Mode" << endl;
		cout << "Simulation Starts..." << endl;
		cout << "Simulation ends, Output file is created" << endl;
	}
	else ProduceOutput();
}

void Game::SetPercentageOfInfected(float Percent)
{
	PercentageOfInfected = Percent;
}

float Game::GetPercentageOfInfected()
{
	return PercentageOfInfected;
}

void Game::IncrementInfectedCount()
{
	InfectedCount++;
}

bool Game::CheckGameEnded()
{
	if (TimeStep == 500)
	{
		EndGameCondition = Draw;
		return true;
	}
	else if (EA->GetEarthCount() == 0)
	{
		EndGameCondition = Lose;
		return true;
	}
	else if (AA->GetAlienCount() == 0)
	{
		EndGameCondition = Win;
		return true;
	}
	else if (AA->GetAlienCount() != 0 && EA->GetEarthCount() != 0)
	{
		EndGameCondition = Neutral;
		return false;
	}
}

void Game::AddInfectedES(EarthSoldier* Unit)
{
	if (Unit)
	{
		ESInfect.enqueue(Unit);
		InfectedCount++;
	}
}

void Game::RemoveInfectedES(EarthSoldier*& esptr)
{
	if (InfectedCount != 0)
	{
		ESInfect.dequeue(esptr);
		InfectedCount--;
	}
}

bool Game::GetGenerating()
{
	return generating;
}

void Game::SetGenerating(bool x)
{
	generating = x;
}