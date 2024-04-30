#include "RandGen.h"

void RandGen::Generate(Game* game, EarthArmy* EA, AlienArmy* ALA,int tj)
{
	game->in;
	game->Readinput();
	int A = 1 + rand() % 100;
	if (A <= game->in.Prob)
	{
		for (int i = 0; i < game->in.numOfUnits; i++)
		{
			int B = 1 + rand() % 100;
			int H = game->in.minHealthEarth + (rand() % (game->in.maxHealthEarth - game->in.minHealthEarth));
			int P = game->in.minPowerEarth + (rand() % (game->in.maxPowerEarth - game->in.minPowerEarth));
			int C = game->in.minCapacityEarth + (rand() % (game->in.maxCapacityEarth - game->in.minCapacityEarth));
			if (B <= game->in.ES)
			{
				EA->addES(tj, H, P, C);
			}
			else if (B <= game->in.ES + game->in.ET)
			{
				EA->addET(tj, H, P, C);
			}
			else
			{
				EA->addEG(tj, H, P, C);
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
				ALA->addAS(tj, H, P, C);
			}
			else if (Z <= game->in.AS + game->in.AM)
			{
				ALA->addAM(tj, H, P, C);
			}
			else
			{
				ALA->addAD(tj, H, P, C);
			}
		}
	}
}