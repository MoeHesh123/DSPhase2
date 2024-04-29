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
			earthArmy.addESFromTemp(esptr);
		}
		else if (X > 10 && X <= 20)
		{
			EarthTank* etptr = nullptr;
			earthArmy.removeET(etptr);
			gameManager.AddETToKilled(etptr);
		}
		else if (X > 20 && X <= 30)
		{
			EarthGunnery* egptr = nullptr;
			int Priority = 0.0;
			earthArmy.removeEG(egptr, Priority);
			if (egptr != nullptr)
			{
				egptr->SetHealth(0.5 * egptr->GetHealth());
				if (egptr->GetHealth() <= 0) gameManager.AddEGToKilled(egptr);
				else earthArmy.addEGFromTemp(egptr);
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
					gameManager.AddASToTempList(asptr);
					gameManager.RemoveASFromTempList(asptr);
					if (asptr->GetHealth() <= 0) gameManager.AddASToKilled(asptr);
					else alienArmy.addASFromTemp(asptr);
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
					alienArmy.addAMFromTemp(amptr);
			}
		}
		else if (X > 50 && X <= 60)
		{
			for (int i = 0; i < 3; i++)
			{
				AlienDrone* adptr1, * adptr2;
				alienArmy.removeAD(adptr1, adptr2);
				if (adptr1 && adptr2)
				{
					gameManager.AddADToKilled(adptr1);
					gameManager.AddADToKilled(adptr2);
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