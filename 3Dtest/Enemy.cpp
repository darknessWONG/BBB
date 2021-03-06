#include "stdafx.h"
#include "Enemy.h"
#include "Common.h"
#include "physics.h"


Enemy::Enemy()
{
	vecPatrolTarget = vecPatrolEnd;
}

Enemy::Enemy(string modelPath)
	:Chara(modelPath)
{
	vecPatrolTarget = vecPatrolEnd;
}


Enemy::~Enemy()
{
	safe_delete<D3DXVECTOR3>(this->vecPatrolStart);
	safe_delete<D3DXVECTOR3>(this->vecPatrolEnd);
	safe_delete<D3DXVECTOR3>(this->vecPatrolTarget);
}

void Enemy::dataUpdate(void)
{
	if (vecPatrolTarget == NULL)
	{
		vecPatrolTarget = vecPatrolEnd;
	}
	D3DXVECTOR3 patrolLine = *vecPatrolEnd - *vecPatrolStart;
	if (vecPatrolTarget == vecPatrolStart)
	{
		patrolLine = -patrolLine;
	}
	D3DXVECTOR3 nowLine = *vecPatrolTarget - *getVecNowPos();

	float dot = D3DXVec3Dot(&patrolLine, &nowLine);
	float length = D3DXVec3Length(&patrolLine) * D3DXVec3Length(&nowLine);
	if (Physics::round(dot, FLOAT_BITS) == -Physics::round(length, FLOAT_BITS))
	{
		if (vecPatrolTarget == vecPatrolEnd)
		{
			vecPatrolTarget = vecPatrolStart;
		}
		else
		{
			vecPatrolTarget = vecPatrolEnd;
		}

	}
	D3DXVECTOR3 speedDir = *vecPatrolTarget - *getVecNowPos();
	D3DXVec3Normalize(&speedDir, &speedDir);
	setVecMoveSpeed(&D3DXVECTOR3(0, 0, 0));
	addSpeed(&speedDir, getWalkSpeed());

	Chara::dataUpdate();
}

D3DXVECTOR3 * Enemy::getVecPatrolStart(void)
{
	return vecPatrolStart;
}

void Enemy::setVecPatrolStart(D3DXVECTOR3 * vecPatrolStart)
{
	safe_delete<D3DXVECTOR3>(this->vecPatrolStart);
	this->vecPatrolStart = new D3DXVECTOR3(*vecPatrolStart);
}

D3DXVECTOR3 * Enemy::getVecPatrolEnd(void)
{
	return vecPatrolEnd;
}

void Enemy::setVecPatrolEnd(D3DXVECTOR3 * vecPatrolEnd)
{
	safe_delete<D3DXVECTOR3>(this->vecPatrolEnd);
	this->vecPatrolEnd = new D3DXVECTOR3(*vecPatrolEnd);
}

D3DXVECTOR3 * Enemy::getVecPatrolTarget(void)
{
	return vecPatrolTarget;
}

void Enemy::setVecPatrolTarget(D3DXVECTOR3 * vecPatrolTarget)
{
	safe_delete<D3DXVECTOR3>(this->vecPatrolTarget);
	this->vecPatrolTarget = new D3DXVECTOR3(*vecPatrolTarget);
}
