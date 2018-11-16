#pragma once
#include <vector>
#include "Chara.h"
class Battle
{
public:
	Battle();
	~Battle();

	void addCharas(Chara* chara);

private:
	vector<Chara*> charas;
};

