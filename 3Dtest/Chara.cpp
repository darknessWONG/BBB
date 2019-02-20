#include "stdafx.h"
#include "Common.h"
#include "Chara.h"


Chara::Chara()
{
}

Chara::~Chara()
{
}

void Chara::dataUpdate(void)
{

	float speedSum = D3DXVec3LengthSq(getVecMoveSpeed());
	if (getModel()->getIsWithAnimation())
	{
		if (Physics::round(speedSum, FLOAT_BITS) != 0)
		{
			setIsPlayAnima(true);
		}
		else
		{
			setIsPlayAnima(false);
			resetAnimaCount();
			getModel()->resetAnimation();
			getModel()->updateAnimation(0.001);
		}
	}

	GameObject::dataUpdate();
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
