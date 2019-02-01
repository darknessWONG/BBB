#include "stdafx.h"
#include "GameObject.h"
#include "Common.h"

D3DXVECTOR3* GameObject::zeroDirect = new D3DXVECTOR3(0.0f, 0.0f, 0.0f);

GameObject::GameObject()
{
	mtxWorld = new D3DXMATRIX();
	D3DXMatrixIdentity(mtxWorld);

	vecFront = new D3DXVECTOR3(0, 0, 1);    //the up direct of camera(normalize vector)
	vecRight = new D3DXVECTOR3(1, 0, 0);    //the front direct of camera(normalize vector)
	vecUp = new D3DXVECTOR3(0, 1, 0);	     //the right direct of camera(normalize vector)

	vecNowPos = new D3DXVECTOR3(0, 0, 0);
	vecMoveSpeed = new D3DXVECTOR3(0, 0, 0);
	moveDamping = MOVE_DAMPING;

	vecScale = new D3DXVECTOR3(1, 1, 1);

	vecRotateAxis = new D3DXVECTOR3(0, 0, 0);
	rotateSpeed = 0;
	rotateDamping = ROTATE_DAMPING;
	vecTargetFront = NULL;

	moveThisTurn = false;
	canMove = false;

	overlapLevel = 0;
	isDisplay = true;
	isDelete = false;
}


GameObject::~GameObject()
{
	safe_delete<D3DXMATRIX>(mtxWorld);

	safe_delete<D3DXVECTOR3>(vecFront);    //the up direct of camera(normalize vector)
	safe_delete<D3DXVECTOR3>(vecRight);    //the front direct of camera(normalize vector)
	safe_delete<D3DXVECTOR3>(vecUp);	     //the right direct of camera(normalize vector)

	safe_delete<D3DXVECTOR3>(vecNowPos);
	safe_delete<D3DXVECTOR3>(vecMoveSpeed);
	//safe_delete<D3DXVECTOR3>(vecTargetFront);

	safe_delete<D3DXVECTOR3>(vecRotateAxis);

}

void GameObject::calWorldMatrix(void)
{

	D3DXMatrixIdentity(mtxWorld);

	D3DXMATRIX mtxScale;
	D3DXMatrixIdentity(&mtxScale);
	mtxScale._11 = vecScale->x;
	mtxScale._22 = vecScale->y;
	mtxScale._33 = vecScale->z;

	D3DXMATRIX mtxTrans;
	D3DXMatrixIdentity(&mtxTrans);
	mtxTrans._41 = vecNowPos->x;
	mtxTrans._42 = vecNowPos->y;
	mtxTrans._43 = vecNowPos->z;

	//D3DXMATRIX mtxRotate;
	//D3DXMatrixIdentity(&mtxRotate);
	//D3DXMatrixRotationAxis(&mtxRotate, vecRotateAxis, rotateSpeed);

	float cosFront = vecFront->z;
	float sinFront = sqrt(1 - cosFront * cosFront);
	if (vecFront->x > 0)
	{
		sinFront = -sinFront;
	}
	D3DXMATRIX mtxRotate;
	D3DXMatrixIdentity(&mtxRotate);
	mtxRotate._11 = cosFront;
	mtxRotate._13 = sinFront;
	mtxRotate._31 = -sinFront;
	mtxRotate._33 = cosFront;

	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxScale);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxRotate);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxTrans);

}

void GameObject::beforeUpdate(void)
{
	setVecMoveSpeed(&D3DXVECTOR3(0, 0, 0));
}

void GameObject::dataUpdate(void)
{
	calSpeed();
	calFront();

}

void GameObject::positionUpdateX(void)
{
	D3DXVECTOR3 newPos(*vecNowPos);
	newPos.x += vecMoveSpeed->x;
	setVecNowPos(&newPos);
}

void GameObject::positionUpdateY(void)
{
	D3DXVECTOR3 newPos(*vecNowPos);
	newPos.y += vecMoveSpeed->y;
	setVecNowPos(&newPos);
}

void GameObject::positionUpdateZ(void)
{
	D3DXVECTOR3 newPos(*vecNowPos);
	newPos.z += vecMoveSpeed->z;
	setVecNowPos(&newPos);
}

void GameObject::positionUpdate(void)
{
	D3DXVECTOR3 newPos(*vecNowPos + *vecMoveSpeed);
	setVecNowPos(&newPos);
}

void GameObject::calBounding(void)
{
}

void GameObject::addSpeed(D3DXVECTOR3 * speedDir, float speed)
{
	D3DXVECTOR3 norSpeed;
	D3DXVec3Normalize(&norSpeed, speedDir);
	*vecMoveSpeed += norSpeed * speed;
}

void GameObject::calSpeed(void)
{
	//if (D3DXVec3Length(vecMoveSpeed) > maxSpeed)
	//{
	//	D3DXVec3Normalize(vecMoveSpeed, vecMoveSpeed);
	//	*vecMoveSpeed *= maxSpeed;
	//}
	//*vecMoveSpeed *= moveDamping;
}

void GameObject::calFront(void)
{
	rotateSpeed *= rotateDamping;
	D3DXMATRIX mtxRotate;
	D3DXMatrixIdentity(&mtxRotate);
	D3DXMatrixRotationAxis(&mtxRotate, vecRotateAxis, rotateSpeed);
	D3DXVec3TransformNormal(vecFront, vecFront, &mtxRotate);
	D3DXVec3TransformNormal(vecRight, vecRight, &mtxRotate);
	D3DXVec3TransformNormal(vecUp, vecUp, &mtxRotate);

	if (vecTargetFront != NULL && *vecFront != *vecTargetFront)
	{
		vecFront = vecTargetFront;
		D3DXVec3Cross(vecRight, vecUp, vecFront);
	}
}

void GameObject::lockThisTurn(void)
{
	moveThisTurn = false;
}

void GameObject::unlockThisTurn(void)
{
	moveThisTurn = true;
}

void GameObject::setDisappear(bool isDisappear, int ovl)
{
	if (isDisappear)
	{
		setIsDisplay(false);
		setOverlapLevel(-100);
	}
	else
	{
		setIsDisplay(true);
		setOverlapLevel(ovl);
	}
}

D3DXMATRIX* GameObject::getMtxWorld(void)
{
	return mtxWorld;
}

void GameObject::setMtxWorld(D3DXMATRIX* mtxWorld)
{
	safe_delete<D3DXMATRIX>(this->mtxWorld);
	this->mtxWorld = new D3DXMATRIX(*mtxWorld);
}

D3DXVECTOR3* GameObject::getVecFront(void)
{
	return vecFront;
}

void GameObject::setVecFront(D3DXVECTOR3* vecFront)
{
	safe_delete<D3DXVECTOR3>(this->vecFront);
	this->vecFront = new D3DXVECTOR3(*vecFront);
}

D3DXVECTOR3* GameObject::getVecRight(void)
{
	return vecRight;
}

void GameObject::setVecRight(D3DXVECTOR3* vecRight)
{
	safe_delete<D3DXVECTOR3>(this->vecRight);
	this->vecRight = new D3DXVECTOR3(*vecRight);
}

D3DXVECTOR3* GameObject::getVecUp(void)
{
	return vecUp;
}

void GameObject::setVecUp(D3DXVECTOR3* vecUp)
{
	safe_delete<D3DXVECTOR3>(this->vecUp);
	this->vecUp = new D3DXVECTOR3(*vecUp);
}

bool GameObject::getCanMove(void)
{
	return canMove;
}

void GameObject::setCanMove(bool canMove)
{
	this->canMove = canMove;
}

D3DXVECTOR3* GameObject::getVecNowPos(void)
{
	return vecNowPos;
}

void GameObject::setVecNowPos(D3DXVECTOR3* vecNowPos)
{
	safe_delete<D3DXVECTOR3>(this->vecNowPos);
	this->vecNowPos = new D3DXVECTOR3(*vecNowPos);
}

D3DXVECTOR3* GameObject::getVecMoveSpeed(void)
{
	return vecMoveSpeed;
}

void GameObject::setVecMoveSpeed(D3DXVECTOR3* vecMoveSpeed)
{
	safe_delete<D3DXVECTOR3>(this->vecMoveSpeed);
	this->vecMoveSpeed = new D3DXVECTOR3(*vecMoveSpeed);
}

float GameObject::getMaxSpeed(void)
{
	return maxSpeed;
}

void GameObject::setMaxSpeed(float maxSpeed)
{
	this->maxSpeed = maxSpeed;
}

float GameObject::getMoveDamping(void)
{
	return moveDamping;
}

void GameObject::setMoveDamping(float moveDamping)
{
	this->moveDamping = moveDamping;
}

int GameObject::getOverlapLevel(void)
{
	return overlapLevel;
}

void GameObject::setOverlapLevel(int overlapLevel)
{
	this->overlapLevel = overlapLevel;
}

bool GameObject::getIsDisplay(void)
{
	return isDisplay;
}

void GameObject::setIsDisplay(bool isDisplay)
{
	this->isDisplay = isDisplay;
}

D3DXVECTOR3 * GameObject::getVecScale(void)
{
	return vecScale;
}

void GameObject::setVecScale(D3DXVECTOR3 * vecScale)
{
	safe_delete<D3DXVECTOR3>(this->vecScale);
	this->vecScale = new D3DXVECTOR3(*vecScale);
}

D3DXVECTOR3* GameObject::getVecRotateAxis(void)
{
	return vecRotateAxis;
}

void GameObject::setVecRotateAxis(D3DXVECTOR3* vecRotateAxis)
{
	safe_delete<D3DXVECTOR3>(this->vecRotateAxis);
	this->vecRotateAxis = new D3DXVECTOR3(*vecRotateAxis);
}

float GameObject::getRotateSpeed(void)
{
	return rotateSpeed;
}

void GameObject::setRotateSpeed(float rotateSpeed)
{
	this->rotateSpeed = rotateSpeed;
}

float GameObject::getRotateDamping(void)
{
	return rotateDamping;
}

void GameObject::setRotateDamping(float rotateDamping)
{
	this->rotateDamping = rotateDamping;
}

D3DXVECTOR3 * GameObject::getVecTargetFront(void)
{
	return vecTargetFront;
}

void GameObject::setVecTargetFront(D3DXVECTOR3 * vecTargetFront)
{
	safe_delete<D3DXVECTOR3>(this->vecTargetFront);
	this->vecTargetFront = new D3DXVECTOR3(*vecTargetFront);
}

bool GameObject::getMoveThisTurn(void)
{
	return moveThisTurn;
}

bool GameObject::getIsDelete(void)
{
	return isDelete;
}

void GameObject::setIsDelete(bool isDelete)
{
	this->isDelete = isDelete;
}
