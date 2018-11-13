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
	moveDamping = MOVEDAMPING;

	vecRotateAxis = new D3DXVECTOR3(0, 0, 0);
	rotateSpeed = 0;
	rotateDamping = ROTATEDAMPING;

	canMove = false;
}


GameObject::~GameObject()
{
	safe_delete<D3DXMATRIX>(mtxWorld);

	safe_delete<D3DXVECTOR3>(vecFront);    //the up direct of camera(normalize vector)
	safe_delete<D3DXVECTOR3>(vecRight);    //the front direct of camera(normalize vector)
	safe_delete<D3DXVECTOR3>(vecUp);	     //the right direct of camera(normalize vector)

	safe_delete<D3DXVECTOR3>(vecNowPos);
	safe_delete<D3DXVECTOR3>(vecMoveSpeed);

	safe_delete<D3DXVECTOR3>(vecRotateAxis);

}

void GameObject::calWorldMatrix(void)
{

	D3DXMATRIX mtxTrans;
	D3DXMatrixIdentity(&mtxTrans);
	mtxTrans._41 = vecNowPos->x;
	mtxTrans._42 = vecNowPos->y;
	mtxTrans._43 = vecNowPos->z;

	D3DXMatrixIdentity(mtxWorld);
	D3DXMATRIX mtxRotate;
	D3DXMatrixIdentity(&mtxRotate);
	D3DXMatrixRotationAxis(&mtxRotate, vecRotateAxis, rotateSpeed);

	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxRotate);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxTrans);

}

void GameObject::dataUpdate(void)
{
	if (D3DXVec3Length(vecMoveSpeed) > maxSpeed)
	{
		D3DXVec3Normalize(vecMoveSpeed, vecMoveSpeed);
		*vecMoveSpeed *= maxSpeed;
	}

	rotateSpeed *= rotateDamping;
	D3DXMATRIX mtxRotate;
	D3DXMatrixIdentity(&mtxRotate);
	D3DXMatrixRotationAxis(&mtxRotate, vecRotateAxis, rotateSpeed);
	D3DXVec3TransformNormal(vecFront, vecFront, &mtxRotate);
	D3DXVec3TransformNormal(vecRight, vecRight, &mtxRotate);
	D3DXVec3TransformNormal(vecUp, vecUp, &mtxRotate);

	*vecMoveSpeed *= moveDamping;
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

void GameObject::addSpeed(D3DXVECTOR3 * speedDir, float speed)
{
	D3DXVECTOR3 norSpeed;
	D3DXVec3Normalize(&norSpeed, speedDir);
	*vecMoveSpeed += norSpeed * speed;
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

D3DXVECTOR3* GameObject::geteVecFront(void)
{
	return vecFront;
}

void GameObject::seteVecFront(D3DXVECTOR3* vecFront)
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
