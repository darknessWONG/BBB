#include "stdafx.h"
#include "MovePerform.h"
#include "Physics.h"


MovePerform::MovePerform()
{
}


MovePerform::~MovePerform()
{
}

//void MovePerform::play(void)
//{
//	GameObject *actor = getActor();
//	D3DXVECTOR3 speedDir = vecTarget - vecStart;
//	D3DXVec3Normalize(&speedDir, &speedDir);
//	actor->setVecMoveSpeed(&D3DXVECTOR3(0, 0, 0));
//	actor->addSpeed(&speedDir, moveSpeed);
//
//	D3DXVECTOR2 boundingCenter = actor->getBoundingCenter();
//	D3DXVECTOR2 newCenter = { vecTarget.x, vecTarget.z };
//	D3DXVECTOR2 newFront = boundingCenter - newCenter;
//	D3DXVECTOR3 newFront3 = { newFront.x, 0, newFront.y };
//	D3DXVec3Normalize(&newFront3, &newFront3);
//	actor->setVecTargetFront(&newFront3);
//}
void MovePerform::play(void)
{
	GameObject *actor = getActor();
	vecStart = { actor->getBoundingCenter().x, actor->getVecNowPos()->y, actor->getBoundingCenter().y };
	D3DXVECTOR3 speedDir = vecTarget - vecStart;
	D3DXVec3Normalize(&speedDir, &speedDir);
	actor->setVecMoveSpeed(&D3DXVECTOR3(0, 0, 0));
	actor->addSpeed(&speedDir, moveSpeed);

	D3DXVECTOR2 boundingCenter = actor->getBoundingCenter();
	D3DXVECTOR2 newCenter = { vecTarget.x, vecTarget.z };
	D3DXVECTOR2 newFront = newCenter - boundingCenter;
	D3DXVECTOR3 newFront3 = { newFront.x, 0, newFront.y };
	D3DXVec3Normalize(&newFront3, &newFront3);
	actor->setVecTargetFront(&newFront3);

}

bool MovePerform::checkEnd(void)
{
	D3DXVECTOR2 boundingCenter = getActor()->getBoundingCenter();
	D3DXVECTOR3 patrolLine = vecTarget - vecStart;
	D3DXVECTOR3 nowLine = vecTarget - D3DXVECTOR3(boundingCenter.x, 0, boundingCenter.y);

	//float dot = D3DXVec3Dot(&patrolLine, &nowLine);
	//float length = D3DXVec3Length(&patrolLine) * D3DXVec3Length(&nowLine);
	//if (Physics::round(dot, FLOATBITS) == -Physics::round(length, FLOATBITS))
	//{
	//	getActor()->setVecMoveSpeed(&D3DXVECTOR3(0, 0, 0));
	//	return true;
	//}
	//return false;

	if(boundingCenter.x > vecTarget.x - 0.1 && boundingCenter.x < vecTarget.x + 0.1 
		&& boundingCenter.y > vecTarget.z - 0.1 && boundingCenter.y < vecTarget.z + 0.1 )
	{
		getActor()->setVecMoveSpeed(&D3DXVECTOR3(0, 0, 0));
		return true;
	}
	return false;
}

D3DXVECTOR3 MovePerform::getVecTarget(void)
{
	return vecTarget;
}

void MovePerform::setVecTarget(D3DXVECTOR3 vecTarget)
{
	this->vecTarget = vecTarget;
}

D3DXVECTOR3 MovePerform::getVecStart(void)
{
	return vecStart;
}

void MovePerform::setVecStart(D3DXVECTOR3 vecStart)
{
	this->vecStart = vecStart;
}

float MovePerform::getMoveSpeed(void)
{
	return moveSpeed;
}

void MovePerform::setMoveSpeed(float moveSpeed)
{
	this->moveSpeed = moveSpeed;
}
