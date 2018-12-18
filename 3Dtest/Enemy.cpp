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
}

void Enemy::dataUpdate(void)
{
	if (vecPatrolTarget == NULL)
	{
		vecPatrolTarget = vecPatrolEnd;
	}
	if (!isTracking)
	{
		D3DXVECTOR3 patrolLine = *vecPatrolEnd - *vecPatrolStart;
		if (vecPatrolTarget == vecPatrolStart)
		{
			patrolLine = -patrolLine;
		}
		D3DXVECTOR2 boundingCenter = getBoundingCenter();
		D3DXVECTOR3 nowLine = *vecPatrolTarget - D3DXVECTOR3(boundingCenter.x, 0, boundingCenter.y);

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
	}
	D3DXVECTOR2 boundingCenter = getBoundingCenter();
	D3DXVECTOR3 speedDir = *vecPatrolTarget - D3DXVECTOR3(boundingCenter.x, 0, boundingCenter.y);
	D3DXVec3Normalize(&speedDir, &speedDir);
	setVecMoveSpeed(&D3DXVECTOR3(0, 0, 0));
	addSpeed(&speedDir, getWalkSpeed());

	D3DXVECTOR2 newCenter = { vecPatrolTarget->x, vecPatrolTarget->z };
	D3DXVECTOR2 newFront = boundingCenter - newCenter;
	D3DXVECTOR3 newFront3 = { newFront.x, 0, newFront.y };
	D3DXVec3Normalize(&newFront3, &newFront3);
	setVecTargetFront(&newFront3);

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
	//safe_delete<D3DXVECTOR3>(this->vecPatrolTarget);
	this->vecPatrolTarget = new D3DXVECTOR3(*vecPatrolTarget);
}

bool Enemy::getIsTracking(void)
{
	return isTracking;
}

void Enemy::setIsTracking(bool isTracking)
{

	if (this->isTracking && !isTracking)
	{
		vecPatrolTarget = vecPatrolEnd;
	}
	this->isTracking = isTracking;
}
