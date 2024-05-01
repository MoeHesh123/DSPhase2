#include "Game.h"
#include"../RandGen/RandGen.h"

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
		myfile.close();
	}
}

void Game::ProduceOutput(EarthArmy* earmy, AlienArmy* aarmy)
{

	cout << "Please Enter The Output File Name: ";
	string file;
	cin >> file;
	ofstream OutputFile(file + ".txt");

	OutputFile << "File Name: " << file << endl << endl;

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
	//float ESumDd = 0, ESumDb = 0;
	//float ASumDd = 0, ASumDb = 0;
	while (Current) 
	{
		//if ((Current->getItem()->GetType() == "ES") || (Current->getItem()->GetType() == "ET") || (Current->getItem()->GetType() == "EG")) 
		//{
		//	ESumDd += Current->getItem()->GetDd();
		//	ESumDb += Current->getItem()->GetDb();
		//}
		//else
		//{
		//	ASumDd += Current->getItem()->GetDd();
		//	ASumDb += Current->getItem()->GetDb();
		//}
		OutputFile 
		<< setw(6) << left << ""
		<< setw(6) << left << Current->getItem()->GetId()
		<< setw(6) << left << Current->getItem()->GetJoinTime()
		<< setw(6) << left << ""
		<< setw(6) << left << ""
		<< setw(6) << left << "" << endl;
		Current = Current->getNext();
	}

	//OutputFile << "============================================================================" << endl;

	//Output File win/loss/draw

	OutputFile << "============================================================================" << endl;

	OutputFile 
	<< "Total Earth Army Units Alive: " << endl
	<< setw(6) << left << "ES"
	<< setw(6) << left << "ET"
	<< setw(6) << left << "EG" << endl;
	OutputFile 
	<< setw(6) << left << earmy->getEScount()
	<< setw(6) << left << earmy->getETcount()
	<< setw(6) << left << earmy->getEGcount() << endl <<endl;
	OutputFile
	<< "Percentage Of Destructed Earth Units Relative To Their Total: " << endl
	<< setw(6) << left << round((ESKilledcount / (earmy->getEScount() + ESKilledcount)) * 100)
	<< setw(6) << left << round((ETKilledcount / (earmy->getETcount() + ETKilledcount)) * 100)
	<< setw(6) << left << round((EGKilledcount / (earmy->getEGcount() + EGKilledcount)) * 100) << endl << endl;
	OutputFile << "Percentage Of Total Destructed Earth units Relative To Total Earth Units: " 
	<< round((ESKilledcount + ETKilledcount + EGKilledcount) / ((earmy->getEScount() + ESKilledcount) + (earmy->getETcount() + ETKilledcount) + (earmy->getEGcount() + EGKilledcount)) * 100) << endl;
	//OutputFile << "Average of Df,Dd & Db for Earth Units:"
	//<< setw(6) << left << "DfAVG"
	//<< setw(6) << left << "DdAVG"
	//<< setw(6) << left << "DbAVG" << endl;
	//OutputFile
	//<< setw(6) << left << round(ESumDf)
	//<< setw(6) << left << round(ESumDd/KilledCount)
	//<< setw(6) << left << round(ESumDb/KilledCount) << endl;
	//OutputFile << "Earth Df/Db%: " << round((ESumDf / ESumDb) * 100) << endl;
	//OutputFile << "Earth Dd/Db%: " << round((ESumDd / ESumDb) * 100) << endl;

	OutputFile << "============================================================================" << endl;

	OutputFile
	<< "Total Alien Army Units Alive: " << endl
	<< setw(6) << left << "AS"
	<< setw(6) << left << "AM"
	<< setw(6) << left << "AD" << endl;
	OutputFile
	<< setw(6) << left << aarmy->getAScount()
	<< setw(6) << left << aarmy->getAMcount()
	<< setw(6) << left << aarmy->getADcount() << endl<<endl;
	OutputFile
	<< "Percentage Of Destructed Alien Units Relative To Their Total: " << endl
	<< setw(6) << left << round((ASKilledcount / (aarmy->getAScount() + ASKilledcount)) * 100)
	<< setw(6) << left << round((AMKilledcount / (aarmy->getAMcount() + AMKilledcount)) * 100)
	<< setw(6) << left << round((ADKilledcount / (aarmy->getADcount() + ADKilledcount)) * 100) << endl<<endl;
	OutputFile << "Percentage Of Total Destructed Alien units Relative To Total Alien Units: "
	<< round((ASKilledcount + AMKilledcount + ADKilledcount) / ((aarmy->getAScount() + ASKilledcount) + (aarmy->getAMcount() + AMKilledcount) + (aarmy->getADcount() + ADKilledcount)) * 100) << endl;
	//OutputFile << "Average of Df,Dd & Db for Alien Units:"
	//<< setw(6) << left << "DfAVG"
	//<< setw(6) << left << "DdAVG"
	//<< setw(6) << left << "DbAVG" << endl;
	//OutputFile
	//<< setw(6) << left << round(ASumDf)
	//<< setw(6) << left << round(ASumDd / KilledCount)
	//<< setw(6) << left << round(ASumDb / KilledCount) << endl;
	//OutputFile << "Alien Df/Db%: " << round((ESumDf / ESumDb) * 100) << endl;
	//OutputFile << "Alien Dd/Db%: " << round((ESumDd / ESumDb) * 100) << endl;

	OutputFile << "============================================================================" << endl;

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


bool Game::addHU(int jt, double h, int p, int AttC, EarthArmy*& earmy)
{
	if (earmy->getEarthID() < 999)
	{
		HealUnit* hu = new HealUnit(earmy->IncrementEarthID(), jt, h, p, AttC);
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
		else
		{
			KL.enqueue(unit);
			KilledCount++;
			ADKilledcount++;
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
int Game::GetTimeStep()
{
	return TimeStep;
}

void Game::SetTimeStep(int TS)
{
	TimeStep = TS;
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

	Game gameManager;
	RandGen generator;
	EarthArmy earthArmy;
	AlienArmy alienArmy;

	gameManager.Readinput();

	srand((unsigned)time(0));
	int X = 0;
	int Timestep = gameManager.GetTimeStep();

	for (Timestep = 1; Timestep <= 50; Timestep++)
	{
		gameManager.SetTimeStep(Timestep);
		if (x == 1) cout << endl << "Current TimeStep " << Timestep << endl;
		X = 1 + (rand() % 100);
		generator.Generate(&gameManager,&earthArmy, &alienArmy, Timestep);
		if (X > 0 && X <= 10)
		{
			EarthSoldier* esptr = nullptr;
			earthArmy.removeES(esptr);
			gameManager.AddToKilled(esptr);
		}
		else if (X > 10 && X <= 20)
		{
			EarthTank* etptr = nullptr;
			earthArmy.removeET(etptr);
			gameManager.AddToKilled(etptr);
		}
		else if (X > 20 && X <= 30)
		{
			EarthGunnery* egptr = nullptr;
			int Priority = 0;
			earthArmy.removeEG(egptr, Priority);
			gameManager.AddToKilled(egptr);
		}
		else if (X > 30 && X <= 40)
		{
			AlienSoldier* asptr = nullptr;
			alienArmy.removeAS(asptr);
			gameManager.AddToKilled(asptr);
		}
		else if (X > 40 && X <= 50)
		{
			AlienMonster* amptr = nullptr;
			alienArmy.removeAM(amptr);
			gameManager.AddToKilled(amptr);
		}
		else if (X > 50 && X <= 60)
		{
			AlienDrone* adptr1, * adptr2;
			alienArmy.removeAD(adptr1, adptr2);
			if (adptr1 || adptr2)
			{
				gameManager.AddToKilled(adptr1);
				gameManager.AddToKilled(adptr2);
			}
		}
		if (x == 1)
		{
			cout << "==============  Earth Army Alive Units ========" << endl;
			earthArmy.printES();
			earthArmy.printET();
			earthArmy.printEG();
			gameManager.printHL();

			cout << endl << "============= Unit Maintenance List ===========" << endl;
			gameManager.printUML();

			cout << endl << "==============  Alien Army Alive Units ========" << endl;
			alienArmy.printAS();
			alienArmy.printAD();
			alienArmy.printAM();

			cout << endl << "==============  Killed/Destructed Units =======" << endl;
			gameManager.PrintKilledList();

			cout << "Press any key to move to next timestep" << endl;
			cin.get();
		}
	}
	if(x == 2)
	{
		cout << "Silent Mode" << endl;
		cout << "Simulation Starts..." << endl;
		cout << "Simulation ends, Output file is created" << endl;
	}
	gameManager.ProduceOutput(&earthArmy, &alienArmy);
}