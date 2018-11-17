#include "stdafx.h"
#include "MovePerform.h"
#include "Physics.h"


MovePerform::MovePerform()
{
}


MovePerform::~MovePerform()
{
}

void MovePerform::play(void)
{
	GameObject *actor = getActor();
	D3DXVECTOR2 boundingCenter = actor->getBoundingCenter();
	D3DXVECTOR3 speedDir = vecTarget - D3DXVECTOR3(boundingCenter.x, 0, boundingCenter.y);
	D3DXVec3Normalize(&speedDir, &speedDir);
	actor->setVecMoveSpeed(&D3DXVECTOR3(0, 0, 0));
	actor->addSpeed(&speedDir, moveSpeed);

	D3DXVECTOR2 newCenter = { vecTarget.x, vecTarget.z };
	D3DXVECTOR2 newFront = boundingCenter - newCenter;
	D3DXVECTOR3 newFront3 = { newFront.x, 0, newFront.y };
	D3DXVec3Normalize(&newFront3, &newFront3);
	actor->setVecTargetFront(&newFront3);
}

bool MovePerform::checkEnd(void)
{
	D3DXVECTOR2 center = getActor()->getBoundingCenter();
	if (Physics::round(center.x, FLOATBITS) == Physics::round(vecTarget.x, FLOATBITS) && Physics::round(center.y, FLOATBITS) == Physics::round(vecTarget.z, FLOATBITS))
	{
		return true;
	}
	return false;
}
