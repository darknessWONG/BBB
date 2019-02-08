#include "stdafx.h"
#include "ForceMovePerform.h"


ForceMovePerform::ForceMovePerform()
{
}


ForceMovePerform::~ForceMovePerform()
{
}

void ForceMovePerform::play(void)
{
	GameObject *actor = getActor();
	setVecStart({ actor->getBoundingCenter().x, actor->getVecNowPos()->y, actor->getBoundingCenter().y });
	D3DXVECTOR3 speedDir = getVecTarget() - getVecStart();
	D3DXVECTOR2 speedDir2D = { speedDir.x, speedDir.z };
	D3DXVec3Normalize(&speedDir, &speedDir);
	actor->setBoundingCenter(actor->getBoundingCenter() + speedDir2D * getMoveSpeed());
}
