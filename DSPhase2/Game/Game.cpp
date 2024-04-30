#include "Game.h"
#include"../RandGen/RandGen.h"

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

void Game::ProduceOutput(EarthArmy* earmy, AlienArmy* aarmy)
{
	cout << "Please Enter The Output File Name: ";
	string file;
	cin >> file;
	ofstream OutputFile(file + ".txt");

	Node<Unit*>* Current = KL.getfrontPtr();
	OutputFile 
	<< setw(6) << left << "Td"
	<< setw(6) << left << "ID"
	<< setw(6) << left << "Tj"
	<< setw(6) << left << "Df"
	<< setw(6) << left << "Dd"
	<< setw(6) << left << "Db" << endl;
	while (Current) 
	{
		OutputFile 
		<< setw(6) << left << ""
		<< setw(6) << left << Current->getItem()->GetId()
		<< setw(6) << left << Current->getItem()->GetJoinTime()
		<< setw(6) << left << ""
		<< setw(6) << left << ""
		<< setw(6) << left << "" << endl;
		Current = Current->getNext();
	}

	//Output File win/loss/draw
	
	OutputFile 
	<< "Earth Army: " << endl
	<< setw(6) << left << "ES"
	<< setw(6) << left << "ET"
	<< setw(6) << left << "EG" << endl;
	OutputFile 
	<< setw(6) << left << earmy->getEScount()
	<< setw(6) << left << earmy->getETcount()
	<< setw(6) << left << earmy->getEGcount() << endl;
	OutputFile
	<< setw(6) << left << int((ESKilledcount / (earmy->getEScount()+ ESKilledcount)) * 100)
	<< setw(6) << left << int((ETKilledcount / (earmy->getETcount()+ ETKilledcount)) * 100)
	<< setw(6) << left << int((EGKilledcount / (earmy->getEGcount()+ EGKilledcount)) * 100) << endl;

	//OutputFile << ((ESKilledcount + ETKilledcount + EGKilledcount) / (Earmy.getEScount() + Earmy.getETcount() + Earmy.getEGcount())) * 100;

	OutputFile
	<< "Alien Army: " << endl
	<< setw(6) << left << "AS"
	<< setw(6) << left << "AM"
	<< setw(6) << left << "AD" << endl;
	OutputFile
	<< setw(6) << left << aarmy->getAScount()
	<< setw(6) << left << aarmy->getAMcount()
	<< setw(6) << left << aarmy->getADcount() << endl;
	OutputFile
	<< setw(6) << left << int((ASKilledcount / (aarmy->getAScount()+ ASKilledcount)) * 100)
	<< setw(6) << left << int((AMKilledcount / (aarmy->getAMcount()+ AMKilledcount)) * 100)
	<< setw(6) << left << int((ADKilledcount / (aarmy->getADcount()+ ADKilledcount)) * 100) << endl;

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

void Game::StartGame()
{

	int x = 0;
	std::cout << "Which Mode Do you like to simulate with ?" << endl;
	std::cout << "For Interactive Mode Press 1" << endl;
	std::cout << "For Silent Mode Press 2" << endl;
	std::cout << "choice: ";
	std::cin >> x;

	while (x <= 0 || x > 2)
	{
		std::cout << "Invalid Mode please choose again!" << endl;
		std::cout << "choice: ";
		std::cin >> x;
	}

	std::cin.ignore();

	if (x == 1)
	{
		EarthArmy earthArmy;

		AlienArmy alienArmy;

		Game gameManager;

		gameManager.Readinput();

		RandGen generator;

		srand((unsigned)time(0));
		int X = 0;

		for (int TimeStep = 1; TimeStep <= 50; TimeStep++)
		{
			std::cout << endl << "Current TimeStep " << TimeStep << endl;
			X = 1 + (rand() % 100);
			generator.Generate(&gameManager, &earthArmy, &alienArmy, TimeStep);
			if (X > 0 && X <= 10)
			{
				EarthSoldier* esptr = nullptr;
				earthArmy.removeES(esptr);
				gameManager.AddToKilled(esptr);
				/*gameManager.addESToUML(esptr);*/
				/*earthArmy.ReAddEarthUnit(esptr);*/
			}
			else if (X > 10 && X <= 20)
			{
				EarthTank* etptr = nullptr;
				earthArmy.removeET(etptr);
				/*gameManager.addETToUML(etptr);*/
				gameManager.AddToKilled(etptr);
			}
			else if (X > 20 && X <= 30)
			{
				EarthGunnery* egptr = nullptr;
				int Priority = 0;
				earthArmy.removeEG(egptr, Priority);
				if (egptr != nullptr)
				{
					/*egptr->SetHealth(0.5 * egptr->GetHealth());
					if (egptr->GetHealth() <= 0) gameManager.AddToKilled(egptr);
					else earthArmy.ReAddEarthUnit(egptr);*/
					gameManager.AddToKilled(egptr);
				}
			}
			else if (X > 30 && X <= 40)
			{
				for (int i = 0; i < 5; i++)
				{
					AlienSoldier* asptr;
					alienArmy.removeAS(asptr);
					if (asptr != nullptr)
					{
						/*asptr->SetHealth(asptr->GetHealth() - 1.5);
						gameManager.AddToTempList(asptr);
						gameManager.RemoveFromTempList(asptr);
						if (asptr->GetHealth() <= 0) gameManager.AddToKilled(asptr);
						else alienArmy.ReAddAlienUnit(asptr);*/
						gameManager.AddToKilled(asptr);
					}
				}
			}
			else if (X > 40 && X <= 50)
			{
				for (int i = 0; i < 5; i++)
				{
					AlienMonster* amptr = nullptr;
					alienArmy.removeAM(amptr);
					if (amptr)
					{
						gameManager.AddToKilled(amptr);
						/*alienArmy.ReAddAlienUnit(amptr);*/
					}
				}
			}
			else if (X > 50 && X <= 60)
			{
				for (int i = 0; i < 3; i++)
				{
					AlienDrone* adptr1, * adptr2;
					alienArmy.removeAD(adptr1, adptr2);
					if (adptr1 || adptr2)
					{
						gameManager.AddToKilled(adptr1);
						gameManager.AddToKilled(adptr2);
					}
				}
			}
			std::cout << "==============  Earth Army Alive Units ========" << endl;

			earthArmy.printES();
			earthArmy.printET();
			earthArmy.printEG();
			gameManager.printHL();

			std::cout << endl << "============= Unit Maintenance List ===========" << endl;

			gameManager.printUML();

			std::cout << endl << "==============  Alien Army Alive Units ========" << endl;

			alienArmy.printAS();
			alienArmy.printAD();
			alienArmy.printAM();

			std::cout << endl << "==============  Killed/Destructed Units =======" << endl;

			gameManager.PrintKilledList();

			std::cout << "Press any key to move to next timestep" << endl;
			std::cin.get();
		}
		gameManager.ProduceOutput(&earthArmy, &alienArmy);
	}
	else
	{
		EarthArmy earthArmy;

		AlienArmy alienArmy;

		Game gameManager;

		gameManager.Readinput();

		RandGen generator;

		srand((unsigned)time(0));
		int X = 0;

		for (int TimeStep = 1; TimeStep <= 50; TimeStep++)
		{
			X = 1 + (rand() % 100);
			generator.Generate(&gameManager, &earthArmy, &alienArmy, TimeStep);
			if (X > 0 && X <= 10)
			{
				EarthSoldier* esptr = nullptr;
				earthArmy.removeES(esptr);
				//gameManager.addESToUML(esptr);
				//earthArmy.ReAddEarthUnit(esptr);
				gameManager.AddToKilled(esptr);
			}
			else if (X > 10 && X <= 20)
			{
				EarthTank* etptr = nullptr;
				earthArmy.removeET(etptr);
				//gameManager.addETToUML(etptr);
				gameManager.AddToKilled(etptr);
			}
			else if (X > 20 && X <= 30)
			{
				EarthGunnery* egptr = nullptr;
				int Priority = 0;
				earthArmy.removeEG(egptr, Priority);
				if (egptr != nullptr)
				{
					//egptr->SetHealth(0.5 * egptr->GetHealth());
					//if (egptr->GetHealth() <= 0) gameManager.AddToKilled(egptr);
					//else earthArmy.ReAddEarthUnit(egptr);
					gameManager.AddToKilled(egptr);
				}
			}
			else if (X > 30 && X <= 40)
			{
				for (int i = 0; i < 5; i++)
				{
					AlienSoldier* asptr;
					alienArmy.removeAS(asptr);
					if (asptr != nullptr)
					{
						//asptr->SetHealth(asptr->GetHealth() - 1.5);
						//gameManager.AddToTempList(asptr);
						//gameManager.RemoveFromTempList(asptr);
						//if (asptr->GetHealth() <= 0) gameManager.AddToKilled(asptr);
						//else alienArmy.ReAddAlienUnit(asptr);
						gameManager.AddToKilled(asptr);
					}
				}
			}
			else if (X > 40 && X <= 50)
			{
				for (int i = 0; i < 5; i++)
				{
					AlienMonster* amptr = nullptr;
					alienArmy.removeAM(amptr);

					//if (amptr) alienArmy.ReAddAlienUnit(amptr);
					gameManager.AddToKilled(amptr);
				}
			}
			else if (X > 50 && X <= 60)
			{
				for (int i = 0; i < 3; i++)
				{
					AlienDrone* adptr1, * adptr2;
					alienArmy.removeAD(adptr1, adptr2);
					if (adptr1 || adptr2)
					{
						gameManager.AddToKilled(adptr1);
						gameManager.AddToKilled(adptr2);
					}
				}
			}
		}
		gameManager.ProduceOutput(&earthArmy, &alienArmy);
		std::cout << "Silent Mode" << endl;
		std::cout << "Simulation Starts..." << endl;
		std::cout << "Simulation ends, Output file is created" << endl;
	}
}