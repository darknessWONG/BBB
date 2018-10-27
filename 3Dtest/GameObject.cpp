#include "stdafx.h"
#include "GameObject.h"
#include "Common.h"


GameObject::GameObject()
{
	mtxWorld = new D3DXMATRIX();
	D3DXMatrixIdentity(mtxWorld);

	vecFront = new D3DXVECTOR3(0, 0, 1);    //the up direct of camera(normalize vector)
	vecRight = new D3DXVECTOR3(1, 0, 0);    //the front direct of camera(normalize vector)
	vecUp = new D3DXVECTOR3(0, 1, 0);	     //the right direct of camera(normalize vector)

	vecNowPos = new D3DXVECTOR3(0, 0, 0);
	vecMoveDirect = new D3DXVECTOR3(0, 0, 0);
	moveSpeed = 0;
	moveDamping = MOVEDAMPING;

	vecRotateAxis = new D3DXVECTOR3(0, 0, 0);
	rotateSpeed = 0;
	rotateDamping = ROTATEDAMPING;
}


GameObject::~GameObject()
{
	safe_delete<D3DXMATRIX>(mtxWorld);

	safe_delete<D3DXVECTOR3>(vecFront);    //the up direct of camera(normalize vector)
	safe_delete<D3DXVECTOR3>(vecRight);    //the front direct of camera(normalize vector)
	safe_delete<D3DXVECTOR3>(vecUp);	     //the right direct of camera(normalize vector)

	safe_delete<D3DXVECTOR3>(vecNowPos);
	safe_delete<D3DXVECTOR3>(vecMoveDirect);

	safe_delete<D3DXVECTOR3>(vecRotateAxis);

}

void GameObject::calWorldMatrix(void)
{
	D3DXVECTOR3 y(0, 1, 0), z(0, 0, 1);
	D3DXVec3Normalize(vecFront, vecFront);
	D3DXVec3Normalize(&y, &y);
	D3DXVec3Normalize(&z, &z);

	//float r = D3DXVec3Length(vec);
	//D3DXMATRIX rotZ, rotY;
	//D3DXMatrixIdentity(&rotZ);
	//D3DXMatrixIdentity(&rotY);
	//float ry = sqrt(vec->z*vec->z + vec->x*vec->x);

	//rotZ._11 = vec->y / r;
	//rotZ._21 = ry / r;
	//rotZ._12 = -rotZ._21;
	//rotZ._22 = rotZ._11;

	//rotY._11 = vec->x / ry;
	//rotY._13 = vec->z / ry;
	//rotY._31 = -rotY._13;
	//rotY._33 = rotY._11;

	//*outMat = rotZ*rotY;

	float cosy = D3DXVec3Dot(&y, vecFront);
	float siny = sqrt(1 - cosy * cosy);
	siny = vecFront->z < 0 ? -siny : siny;
	float cosxz = cosy * cos(D3DX_PI / 2) + siny * sin(D3DX_PI / 2);
	float sinxz = sqrt(1 - cosxz * cosxz);
	sinxz = vecFront->z < 0 ? -sinxz : sinxz;

	float cosz = D3DXVec3Dot(&z, vecUp);
	float sinz = sqrt(1 - cosz * cosz);
	sinz = vecUp->x < 0 ? -sinz : sinz;
	float cosyz = cosz * cos(D3DX_PI / 2) + sinz * sin(D3DX_PI / 2);
	float sinyz = sqrt(1 - cosyz * cosyz);
	sinyz = vecUp->y < 0 ? -sinyz : sinyz;

	D3DXMATRIX mtxRotateX;
	D3DXMatrixIdentity(&mtxRotateX);
	mtxRotateX._22 = cosxz;
	mtxRotateX._23 = -sinxz;
	mtxRotateX._32 = sinxz;
	mtxRotateX._33 = cosxz;

	D3DXMATRIX mtxRotateY;
	D3DXMatrixIdentity(&mtxRotateY);
	mtxRotateY._11 = cosyz;
	mtxRotateY._13 = sinyz;
	mtxRotateY._31 = -sinyz;
	mtxRotateY._33 = cosyz;

	D3DXVECTOR3 mtxPreFront(0, 0, 1);



	D3DXMATRIX mtxTrans;
	D3DXMatrixIdentity(&mtxTrans);
	mtxTrans._41 = vecNowPos->x;
	mtxTrans._42 = vecNowPos->y;
	mtxTrans._43 = vecNowPos->z;

	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxRotateX);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxRotateY);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxTrans);
}

void GameObject::dataUpdate(void)
{
	moveSpeed *= moveDamping;
	D3DXVECTOR3 newPos(*vecNowPos + (*vecMoveDirect * moveSpeed));
	setVecNowPos(&newPos);

	rotateSpeed *= rotateDamping;
	D3DXMATRIX mtxRotate;
	D3DXMatrixIdentity(&mtxRotate);
	D3DXVec3TransformNormal(vecFront, vecFront, &mtxRotate);
	D3DXVec3TransformNormal(vecRight, vecRight, &mtxRotate);
	D3DXVec3TransformNormal(vecUp, vecUp, &mtxRotate);
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

D3DXVECTOR3* GameObject::getVecNowPos(void)
{
	return vecNowPos;
}

void GameObject::setVecNowPos(D3DXVECTOR3* vecNowPos)
{
	safe_delete<D3DXVECTOR3>(this->vecNowPos);
	this->vecNowPos = new D3DXVECTOR3(*vecNowPos);
}

D3DXVECTOR3* GameObject::getVecMoveDirect(void)
{
	return vecMoveDirect;
}

void GameObject::setVecMoveDirect(D3DXVECTOR3* vecMoveDirect)
{
	safe_delete<D3DXVECTOR3>(this->vecMoveDirect);
	this->vecMoveDirect = new D3DXVECTOR3(*vecMoveDirect);
}

float GameObject::getMoveSpeed(void)
{
	return moveSpeed;
}

void GameObject::setMoveSpeed(float moveSpeed)
{
	this->moveSpeed = moveSpeed;
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
