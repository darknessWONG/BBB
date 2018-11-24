#pragma once
#include <vector>
#include "Chara.h"
class Battle
{
public:
	Battle();
	~Battle();

	void calActionList(void);
	
	void addCharas(Chara* chara);

private:
	vector<Chara*> charas;
	vector<Chara*> actionList;
};

