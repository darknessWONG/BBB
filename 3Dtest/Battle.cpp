#include "stdafx.h"
#include "Battle.h"


Battle::Battle()
{
}


Battle::~Battle()
{
}

void Battle::addCharas(Chara * chara)
{
	charas.push_back(chara);
}
