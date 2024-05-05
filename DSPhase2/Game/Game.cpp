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

void Game::ProduceOutput(Game* game, EarthArmy* earmy, AlienArmy* aarmy)
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
	<< setw(6) << left << "Ta"
	<< setw(6) << left << "Db" << endl; 

	float ESumDd = 0, ESumDb = 0, ESumDf = 0, ASumDd = 0, ASumDb = 0, ASumDf = 0, EarthKilled = 0, AlienKilled = 0;

	while (Current) 
	{
		if ((Current->getItem()->GetType() == "ES") || (Current->getItem()->GetType() == "ET") || (Current->getItem()->GetType() == "EG") || (Current->getItem()->GetType() == "HU"))
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
		<< setw(6) << left << Current->getItem()->GetTa()
		<< setw(6) << left << Current->getItem()->GetDb() <<endl;
		Current = Current->getNext();
	}

	OutputFile << "============================================================================" << endl;

	OutputFile << "Battle result: ";
	if (game->GetEndGameCondition() == 2) OutputFile << "Earth Army Won!";
	else if (game->GetEndGameCondition() == 1) OutputFile << "Alien Army Won!";
	else OutputFile << "Draw!";

	OutputFile << endl << "============================================================================" << endl;

	OutputFile
	<< "Total Earth Army Units Alive: " << endl
	<< setw(6) << left << "ES"
	<< setw(6) << left << "ET"
	<< setw(6) << left << "EG" 
	<< setw(6) << left << "HU"
	<< setw(6) << left << "ESUML"
	<< setw(6) << left << "ETUML" << endl;
	OutputFile 
	<< setw(6) << left << earmy->getEScount()
	<< setw(6) << left << earmy->getETcount()
	<< setw(6) << left << earmy->getEGcount()
	<< setw(6) << left << HUcount 
	<< setw(6) << left << ESUMLcount
	<< setw(6) << left << ETUMLcount << endl;
	OutputFile
	<< setw(6) << left << ESKilledcount
	<< setw(6) << left << ETKilledcount
	<< setw(6) << left << EGKilledcount
	<< setw(6) << left << HUKilledcount;

	OutputFile << endl << endl << "Percentage Of Destructed Earth Units Relative To Their Total: " << endl
	<< setw(6) << left << "ES"
	<< setw(6) << left << "ET"
	<< setw(6) << left << "EG"
	<< setw(6) << left << "HU" << endl;

	if ((earmy->getEScount() + ESKilledcount + ESUMLcount) == 0) OutputFile << setw(6) << left << "0";
	else OutputFile << setw(6) << left << round((ESKilledcount / (earmy->getEScount() + ESKilledcount + ESUMLcount)) * 100);

	if ((earmy->getETcount() + ETKilledcount + ETUMLcount) == 0) OutputFile << setw(6) << left << "0";
	else OutputFile << setw(6) << left << round((ETKilledcount / (earmy->getETcount() + ETKilledcount + ETUMLcount)) * 100);

	if ((earmy->getEGcount() + EGKilledcount) == 0) OutputFile << setw(6) << left << "0";
	else OutputFile << setw(6) << left << round((EGKilledcount / (earmy->getEGcount() + EGKilledcount)) * 100);

	if ((HUcount + HUKilledcount) == 0) OutputFile << setw(6) << left << "0";
	else OutputFile << setw(6) << left << round((HUKilledcount / (HUcount + HUKilledcount)) * 100);

	OutputFile << endl << endl << "Percentage Of Total Destructed Earth units Relative To Total Earth Units: ";
	if((earmy->getEScount() + earmy->getETcount() + earmy->getEGcount() + EarthKilled + HUcount + ESUMLcount + ETUMLcount) == 0) OutputFile <<"0";
	else OutputFile << round(EarthKilled / (earmy->getEScount() + earmy->getETcount() + earmy->getEGcount() + EarthKilled + HUcount + ESUMLcount + ETUMLcount) * 100);

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
	<< setw(6) << left << aarmy->getAScount()
	<< setw(6) << left << aarmy->getAMcount()
	<< setw(6) << left << aarmy->getADcount() << endl;
	OutputFile
	<< setw(6) << left << ASKilledcount
	<< setw(6) << left << AMKilledcount
	<< setw(6) << left << ADKilledcount;
	OutputFile << endl << endl << "Percentage Of Destructed Alien Units Relative To Their Total: " << endl
	<< setw(6) << left << "AS"
	<< setw(6) << left << "AM"
	<< setw(6) << left << "AD" << endl;

	if ((aarmy->getAScount() + ASKilledcount) == 0) OutputFile << setw(6) << left << "0";
	else OutputFile << setw(6) << left << round((ASKilledcount / (aarmy->getAScount() + ASKilledcount)) * 100);

	if ((aarmy->getAMcount() + AMKilledcount) == 0) OutputFile << setw(6) << left << "0";
	else OutputFile << setw(6) << left << round((AMKilledcount / (aarmy->getAMcount() + AMKilledcount)) * 100);

	if ((aarmy->getADcount() + ADKilledcount) == 0) OutputFile << setw(6) << left << "0";
	else OutputFile << setw(6) << left << round((ADKilledcount / (aarmy->getADcount() + ADKilledcount)) * 100);

	OutputFile << endl << endl << "Percentage Of Total Destructed Alien units Relative To Total Alien Units: ";
	if (((aarmy->getAScount() + ASKilledcount) + (aarmy->getAMcount() + AMKilledcount) + (aarmy->getADcount() + ADKilledcount)) == 0) OutputFile << "0";
    else OutputFile << round((ASKilledcount + AMKilledcount + ADKilledcount) / ((aarmy->getAScount() + ASKilledcount) + (aarmy->getAMcount() + AMKilledcount) + (aarmy->getADcount() + ADKilledcount)) * 100);

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
	else OutputFile << round((ASumDf / ASumDb) * 100) << endl;
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

bool Game::CheckESUMLKilled()
{
	if (ESUML.isEmpty()) return false;
	priNode<EarthSoldier*>* TraverseSoldier1 = ESUML.getfrontPtr();
	priNode<EarthSoldier*>* TraverseSoldier2 = TraverseSoldier1;
	while (TraverseSoldier1)
	{
		int pri;
		if ((TimeStep - (TraverseSoldier1->getItem(pri)->GetJTUML())) >= 10)
		{
			EarthSoldier* ESoldier = TraverseSoldier1->getItem(pri);
			AddToKilled(ESoldier);
			ESUMLcount--;
			TraverseSoldier2->setNext(TraverseSoldier1->getNext());
			TraverseSoldier1->setNext(nullptr);
			delete TraverseSoldier1;
			TraverseSoldier1 = nullptr;
			return  true;
		}
		TraverseSoldier2 = TraverseSoldier1;
		TraverseSoldier1 = TraverseSoldier1->getNext();
	}
	return false;
}

bool Game::CheckETUMLKilled()
{
	if (ETUML.isEmpty()) return false;
	Node<EarthTank*>* TraverseTank1 = ETUML.getfrontPtr();
	Node<EarthTank*>* TraverseTank2 = TraverseTank1;
	while (TraverseTank1)
	{
			if ((TimeStep - (TraverseTank1->getItem()->GetJTUML())) >= 10)
			{
				EarthTank* ETank = TraverseTank1->getItem();
				AddToKilled(ETank);
				ETUMLcount--;
				TraverseTank2->setNext(TraverseTank1->getNext());
				TraverseTank1->setNext(nullptr);
				delete TraverseTank1;
				TraverseTank1 = nullptr;
				return  true;
			}
			TraverseTank2 = TraverseTank1;
			TraverseTank1 = TraverseTank1->getNext();
	}
	return false;
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
		cout << Traversal->getItem()->GetId() << ", ";
		Traversal = Traversal->getNext();
	}
	cout << Traversal->getItem()->GetId();
	cout << "]" << endl;
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

	for (int Timestep = 1; Timestep <= 200; Timestep++)
	{
		gameManager.SetTimeStep(Timestep);

		if (x == 1)
		{
			cout << endl << "Current TimeStep " << Timestep << endl;
		}

		generator.Generate(&gameManager,&earthArmy, &alienArmy, Timestep);

		EarthSoldier* ES;
		if (!(earthArmy.isEmpty_ES()))
		{
			earthArmy.peekES(ES);
			if (ES)
			{
				ES->Attack(&gameManager, &earthArmy, &alienArmy);
			}
		}
		EarthTank* ET;
		if (!(earthArmy.isEmpty_ET()))
		{
			earthArmy.peekET(ET);
			if (ET)
			{
				ET->Attack(&gameManager, &earthArmy, &alienArmy);
			}
		}
		EarthGunnery* EG;
		int p = 0;
		if (!earthArmy.isEmpty_EG())
		{
			earthArmy.peekEG(EG, p);
			if (EG)
			{
				EG->Attack(&gameManager, &earthArmy, &alienArmy);
			}
		}
		AlienSoldier* AS;
		if (!(alienArmy.isEmpty_AS()))
		{
			alienArmy.peekAS(AS);
			if (AS)
			{
				AS->Attack(&gameManager, &earthArmy, &alienArmy);
			}
		}
		AlienDrone* AD;
		if (!alienArmy.isEmpty_AD())
		{
			alienArmy.peekADfront(AD);
			if (AD)
			{
				AD->Attack(&gameManager, &earthArmy, &alienArmy);
			}

		}
		AlienMonster* AM;
		if (!alienArmy.isEmpty_AM()) 
		{
			alienArmy.peekAM(AM); 
			if (AM) 
			{
				AM->Attack(&gameManager, &earthArmy, &alienArmy); 
			}
		}

		HealUnit* HU;
		if (!gameManager.isEmpty_HL())
		{
			gameManager.PeekHU(HU);
			if (HU) 
			{
				HU->Attack(&gameManager, &earthArmy, &alienArmy);
			}
				
		}

		//EarthSoldier* es1 = nullptr;
		//earthArmy.removeES(es1);
		//gameManager.addESToUML(es1);
		//EarthTank* et1 = nullptr;
		//earthArmy.removeET(et1);
		//gameManager.addETToUML(et1);
		//while (gameManager.CheckESUMLKilled());
		//while (gameManager.CheckETUMLKilled());

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
			gameManager.ContinueGame(&gameManager, &earthArmy, &alienArmy);
			cin.get();
		}
	}
	if (x == 2)
	{
		gameManager.ProduceOutput(&gameManager, &earthArmy, &alienArmy);
		cout << "Silent Mode" << endl;
		cout << "Simulation Starts..." << endl;
		cout << "Simulation ends, Output file is created" << endl;
	}
	else gameManager.ProduceOutput(&gameManager, &earthArmy, &alienArmy);
}

bool Game::ContinueGame(Game* game,EarthArmy* earmy, AlienArmy* aarmy)
{
	if (aarmy->GetAlienCount() == 0)
	{
		game->SetEndGameCondition(2);
		return false;
	}
	else if (earmy->GetEarthCount() == 0)
	{
		game->SetEndGameCondition(1);
		return false;
	}
	else
	{
		game->SetEndGameCondition(0);
		return false;
	}
	return true;
}

void Game::SetEndGameCondition(int flag)
{
	EndGame = flag;
}

int Game::GetEndGameCondition()
{
	return EndGame;
}