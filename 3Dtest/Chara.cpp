#include "stdafx.h"
#include "Common.h"
#include "Chara.h"


Chara::Chara()
{
}

Chara::Chara(string modelPath)
	:Model(modelPath)
{
}


Chara::~Chara()
{
}

BattleChara * Chara::getBattleChara(void)
{
	return bc;
}

void Chara::setBattleChara(BattleChara * bc)
{
	safe_delete<BattleChara>(this->bc);
	this->bc = bc;
}

float Chara::getWalkSpeed(void)
{
	return walkSpeed;
}

void Chara::setWalkSpeed(float walkSpeed)
{
	this->walkSpeed = walkSpeed;
}
