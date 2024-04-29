#include"../DSPhase2/RandGen/RandGen.h"

int main()
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
		cout << endl << "Current TimeStep " << TimeStep << endl;
		X = 1 + (rand() % 100);
		generator.Generate(&gameManager, &earthArmy, &alienArmy);
		if (X > 0 && X <= 10)
		{
			EarthSoldier* esptr = nullptr;
			earthArmy.removeES(esptr);
			earthArmy.ReAddEarthUnit(esptr);
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
			int Priority = 0.0;
			earthArmy.removeEG(egptr, Priority);
			if (egptr != nullptr)
			{
				egptr->SetHealth(0.5 * egptr->GetHealth());
				if (egptr->GetHealth() <= 0) gameManager.AddToKilled(egptr);
				else earthArmy.ReAddEarthUnit(egptr);
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
					asptr->SetHealth(asptr->GetHealth() - 1.5);
					gameManager.AddToTempList(asptr);
					gameManager.RemoveFromTempList(asptr);
					if (asptr->GetHealth() <= 0) gameManager.AddToKilled(asptr);
					else alienArmy.ReAddAlienUnit(asptr);
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
					alienArmy.ReAddAlienUnit(amptr);
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
		cout << "==============  Earth Army Alive Units ========" << endl;

		earthArmy.printES();
		earthArmy.printET();
		earthArmy.printEG();

		cout << endl << "==============  Alien Army Alive Units ========" << endl;

		alienArmy.printAS();
		alienArmy.printAD();
		alienArmy.printAM();

		cout << endl << "==============  Killed/Destructed Units =======" << endl;

		gameManager.PrintKilledList();
	}
}