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
		myfile >> in.ES >> in.ET >> in.EG;
		myfile >> in.AS >> in.AM >> in.AD;
		myfile >> in.Prob;
		myfile >> in.minPowerEarth >> in.maxPowerEarth >> in.minHealthEarth >> in.maxHealthEarth >> in.minCapacityEarth >> in.maxCapacityEarth;
		myfile >> in.minPowerAlien >> in.maxPowerAlien >> in.minHealthAlien >> in.maxHealthAlien >> in.minCapacityAlien >> in.maxCapacityAlien;
		myfile.close();
	}
}

void Game::AddESToKilled(EarthSoldier* es)
{
	if (es != nullptr)
	{
		KL.enqueue(es);
		KilledCount++;
	}
}

void Game::AddETToKilled(EarthTank* et)
{
	if (et != nullptr)
	{
		KL.enqueue(et);
		KilledCount++;
	}
}

void Game::AddEGToKilled(EarthGunnery* eg)
{
	if (eg != nullptr)
	{
		KL.enqueue(eg);
		KilledCount++;
	}
}

void Game::AddASToKilled(AlienSoldier* as)
{
	if (as != nullptr)
	{
		KL.enqueue(as);
		KilledCount++;
	}
}

void Game::AddADToKilled(AlienDrone* ad)
{
	if (ad != nullptr)
	{
		KL.enqueue(ad);
		KilledCount++;
	}
}

void Game::AddAMToKilled(AlienMonster* am)
{
	if (am != nullptr)
	{
		KL.enqueue(am);
		KilledCount++;
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

void Game::AddESToTempList(EarthSoldier* es)
{
	TLES.enqueue(es);
}

void Game::AddETToTempList(EarthTank* et)
{
	TLET.enqueue(et);
}

void Game::AddEGToTempList(EarthGunnery* eg)
{
	TLEG.enqueue(eg);
}

void Game::AddASToTempList(AlienSoldier* as)
{
	TLAS.enqueue(as);
}

void Game::AddADToTempList(AlienDrone* ad)
{
	TLAD.enqueue(ad);
}

void Game::AddAMToTempList(AlienMonster* am)
{
	TLAM.enqueue(am);
}

void Game::RemoveESFromTempList(EarthSoldier* es)
{
	TLES.dequeue(es);
}

void Game::RemoveETFromTempList(EarthTank* et)
{
	TLET.dequeue(et);
}

void Game::RemoveEGFromTempList(EarthGunnery* eg)
{
	TLEG.dequeue(eg);
}

void Game::RemoveASFromTempList(AlienSoldier* as)
{
	TLAS.dequeue(as);
}

void Game::RemoveADFromTempList(AlienDrone* ad)
{
	TLAD.dequeue(ad);
}

void Game::RemoveAMFromTempList(AlienMonster* am)
{
	TLAM.dequeue(am);
}