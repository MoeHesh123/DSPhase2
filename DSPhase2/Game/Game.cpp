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

void Game::AddToKilled(Unit* unit)
{
	if (unit != nullptr)
	{
		KL.enqueue(unit);
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

void Game::AddToTempList(Unit* unit)
{
	if (unit != nullptr) TL.enqueue(unit);
}

void Game::RemoveFromTempList(Unit* unit)
{
	TL.dequeue(unit);
}