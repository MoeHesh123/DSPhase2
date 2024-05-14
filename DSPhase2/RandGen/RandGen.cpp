#include "RandGen.h"

void RandGen::Generate(Game* game)
{
	game->in;
	int A = 1 + rand() % 100;
	if (A <= game->in.Prob)
	{
		for (int i = 0; i < game->in.numOfUnits; i++)
		{
			int B = 1 + rand() % 100;
			int H = game->in.minHealthEarth + (rand() % (game->in.maxHealthEarth - game->in.minHealthEarth));
			int P = game->in.minPowerEarth + (rand() % (game->in.maxPowerEarth - game->in.minPowerEarth));
			int C = game->in.minCapacityEarth + (rand() % (game->in.maxCapacityEarth - game->in.minCapacityEarth));
			if (B <= (game->in.ES))
			{
				game->GetEA()->addES(game->GetTimeStep(), H, P, C);
			}
			else if (B <= (game->in.ES + game->in.ET))
			{
				game->GetEA()->addET(game->GetTimeStep(), H, P, C);
			}
			else if (B <= (game->in.ES + game->in.ET + game->in.EG))
			{
				game->GetEA()->addEG(game->GetTimeStep(), H, P, C);
			}
			else
			{
				game->addHU(game->GetTimeStep(), H, P, C);
			}
		}
		for (int i = 0; i < game->in.numOfUnits; i++)
		{
			int Z = 1 + rand() % 100;
			int H = game->in.minHealthAlien + (rand() % (game->in.maxHealthAlien - game->in.minHealthAlien));
			int P = game->in.minPowerAlien + (rand() % (game->in.maxPowerAlien - game->in.minPowerAlien));
			int C = game->in.minCapacityAlien + (rand() % (game->in.maxCapacityAlien - game->in.minCapacityAlien));
			if (Z <= game->in.AS)
			{
				game->GetAA()->addAS(game->GetTimeStep(), H, P, C);
			}
			else if (Z <= game->in.AS + game->in.AM)
			{
				game->GetAA()->addAM(game->GetTimeStep(), H, P, C);
			}
			else
			{
				game->GetAA()->addAD(game->GetTimeStep(), H, P, C);
			}
		}
		if (!game->GetGenerating()) {
			if (game->GetPercentageOfInfected() >= game->in.InfectionThreshold)
			{
				game->SetGenerating(1);
				for (int i = 0; i < game->in.numOfUnits; i++)
				{
					int H = game->in.minHealthAlly + (rand() % (game->in.maxHealthAlly - game->in.minHealthAlly));
					int P = game->in.minPowerAlly + (rand() % (game->in.maxPowerAlly - game->in.minPowerAlly));
					int C = game->in.minCapacityAlly + (rand() % (game->in.maxCapacityAlly - game->in.minCapacityAlly));
					game->GetAllies()->addSU(game->GetTimeStep(), H, P, C);
				}
			}
		}
		else
		{
			for (int i = 0; i < game->in.numOfUnits; i++)
			{
				int H = game->in.minHealthAlly + (rand() % (game->in.maxHealthAlly - game->in.minHealthAlly));
				int P = game->in.minPowerAlly + (rand() % (game->in.maxPowerAlly - game->in.minPowerAlly));
				int C = game->in.minCapacityAlly + (rand() % (game->in.maxCapacityAlly - game->in.minCapacityAlly));
				game->GetAllies()->addSU(game->GetTimeStep(), H, P, C);
			}
			if (game->GetPercentageOfInfected() == 0)
			{
				game->SetGenerating(0);
				SaverUnit* SU = nullptr;
				while (game->GetAllies()->removeSU(SU))
				{
					SU = nullptr;
					delete SU;
				}
			}
		}
	}
}