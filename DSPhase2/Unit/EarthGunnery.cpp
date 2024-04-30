#include "EarthGunnery.h"

EarthGunnery::EarthGunnery(int ID, int JT, double H, int P, int AC) : Unit(ID, JT, H, P, AC) {}

string EarthGunnery::GetType()
{
    return type;
}

void EarthGunnery::Attack()
{
}
