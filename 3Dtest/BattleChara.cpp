#include "stdafx.h"
#include "BattleChara.h"


BattleChara::BattleChara()
{
}


BattleChara::~BattleChara()
{
}

int BattleChara::getHp(void)
{
	return hp;
}

void BattleChara::setHp(int hp)
{
	this->hp;
}

void BattleChara::takeDamage(int damage)
{
	hp -= damage;
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
