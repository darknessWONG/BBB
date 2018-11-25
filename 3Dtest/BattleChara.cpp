#include "stdafx.h"
#include "BattleChara.h"


BattleChara::BattleChara()
{
}


BattleChara::~BattleChara()
{
}

void BattleChara::addSkill(BattleSkill * skill)
{
	this->skill.push_back(skill);
}

void BattleChara::addEffect(SideEffect * effect)
{
	this->effect.push_back(effect);
}

void BattleChara::removeEffect(int index)
{
	if (index >= 0 && index < effect.size())
	{
		vector<SideEffect*>::iterator it = effect.begin() + index;
		effect.erase(it);
	}

}

void BattleChara::removeEffect(SideEffect* effect)
{
	for (vector<SideEffect*>::iterator it = this->effect.begin(); it != this->effect.end(); it++)
	{
		if (*it == effect)
		{
			this->effect.erase(it);
			it = this->effect.begin();
			if (this->effect.size() <= 0)
			{
				break;
			}
		}
	}

}

void BattleChara::removeEffect(SideEffectType type)
{
	int max = effect.size();
	for (int i = 0; i < max; i++)
	{
		if (effect[i]->getType() == type)
		{
			vector<SideEffect*>::iterator it = this->effect.begin() + i;
			this->effect.erase(it);
			
			max = effect.size();
			i = 0;
			if (max <= 0)
			{
				break;
			}
		}
	}
}

void BattleChara::removeOverdueStauts(void)
{
	vector<int> list;
	int effectNum = effect.size();
	for (int i = 0; i < effectNum; i++)
	{
		if (effect[i]->getDuration <= 0)
		{
			list.push_back(i);
		}
	}
	
	int listNum = list.size();
	for (int i = listNum - 1; i >= 0; i--)
	{
		removeEffect(list[i]);
	}
}

void BattleChara::calStatus(void)
{
	int effectNum = effect.size();
	for (int i = 0; i < effectNum; i++)
	{
		effect[i]->turn_pass();
		switch (effect[i]->getType())
		{
		case SideEffectType::SideEffectTypePoison:
			takeDamage(effect[i]->getValue());
		}
	}
}

int BattleChara::getHpMax(void)
{
	return hpMax;
}

void BattleChara::setHpMax(int hp)
{
	this->hpMax;
}

int BattleChara::getHpNow(void)
{
	return hpNow;
}

void BattleChara::setHpNow(int hp)
{
	this->hpNow;
}

int BattleChara::getMpMax(void)
{
	return mpMax;
}

void BattleChara::setMpMax(int mp)
{
	this->mpMax;
}

int BattleChara::getMpNow(void)
{
	return mpNow;
}

void BattleChara::setMpNow(int mp)
{
	this->mpNow;
}

void BattleChara::takeDamage(int damage)
{
	hpNow -= damage;
}

int BattleChara::getAtk(void)
{
	return atk;
}

void BattleChara::setAtk(int atk)
{
	this->atk = atk;
}

int BattleChara::getSpeed(void)
{
	return speed;
}

void BattleChara::setSpeed(int speed)
{
	this->speed = speed;
}

int BattleChara::getMovePoint(void)
{
	return movePoint;
}

void BattleChara::setMovePoint(int movePoint)
{
	this->movePoint = movePoint;
}
