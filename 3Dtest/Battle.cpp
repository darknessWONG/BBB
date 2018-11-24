#include "stdafx.h"
#include "Battle.h"


Battle::Battle()
{
}


Battle::~Battle()
{
}

void Battle::calActionList(void)
{
	int charaNum = charas.size();
	actionList.clear();
	if (actionList.size() <= 0)
	{
		for (int i = 0; i < charaNum; i++)
		{
			if (charas[i]->getBattleChara()->getHp() >= 0)
			{
				actionList.push_back(charas[i]);
			}
		}
	}

	int actionNum = charas.size();
	for (int i = 0; i < actionNum; i++)
	{
		for (int j = i + 1; j < actionNum; j++)
		{
			if (actionList[i]->getBattleChara()->getSpeed() < actionList[j]->getBattleChara()->getSpeed())
			{
				Chara *tmp = actionList[i];
				actionList[i] = actionList[j];
				actionList[j] = tmp;
			}
		}
	}
}

void Battle::addCharas(Chara * chara)
{
	charas.push_back(chara);
}
