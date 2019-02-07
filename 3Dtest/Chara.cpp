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

void Chara::dataUpdate(void)
{

	float speedSum = D3DXVec3LengthSq(getVecMoveSpeed());
	if (getIsWithAnimation())
	{
		if (Physics::round(speedSum, FLOAT_BITS) != 0)
		{
			setIsPlayAnimation(true);
		}
		else
		{
			setIsPlayAnimation(false);
			resetAnimation();
			updateAnimation(0.001);
		}
	}

	Model::dataUpdate();
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
