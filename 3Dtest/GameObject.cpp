#include "stdafx.h"
#include "GameObject.h"
#include "RoundShadowHandler.h"
#include "Common.h"

D3DXVECTOR3* GameObject::zeroDirect = new D3DXVECTOR3(0.0f, 0.0f, 0.0f);

GameObject::GameObject()
{
	mtxWorld = new D3DXMATRIX();
	D3DXMatrixIdentity(mtxWorld);

	model = NULL;

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

	animaCounter = 0;
	isPlayAnima = true;
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

	/*
	normal of angle is {0, 0, 1}.
	The dot of front and normal is 0 * x + 0 * y + 1 * z = 1 * 1 * cos
	So cos = z
	*/
	float cosFront = vecFront->z;
	float sinFront = sqrt(1 - cosFront * cosFront);
	if (vecFront->x > 0)
	{
		sinFront = -sinFront;
	}
	safe_delete<D3DXMATRIX>(mtxRotate);
	mtxRotate = new D3DXMATRIX;
	D3DXMatrixIdentity(mtxRotate);
	mtxRotate->_11 = cosFront;
	mtxRotate->_13 = sinFront;
	mtxRotate->_31 = -sinFront;
	mtxRotate->_33 = cosFront;

	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxScale);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, mtxRotate);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxTrans);

}

void GameObject::beforeUpdate(void)
{
	setVecMoveSpeed(&D3DXVECTOR3(0, 0, 0));
}

void GameObject::dataUpdate(void)
{
	if (model != NULL)
	{
		if (isPlayAnima)
		{
			animaCounter += 1/ 1200.0f;
		}
		model->dataUpdate(animaCounter);
	}
	calBounding();
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

void GameObject::draw(LPDIRECT3DDEVICE9 pD3DDevice)
{
	if (isDisplay)
	{
		if (model != NULL)
		{
			model->draw(pD3DDevice, mtxWorld, animaCounter);

#ifdef _DEBUG
			//D3DMATERIAL9 blue;
			//blue.Diffuse = { 1.0f, 1.0f, 1.0f, 0.5f };
			//blue.Ambient = blue.Diffuse;
			//pD3DDevice->SetMaterial(&blue);
			//pD3DDevice->SetTexture(0, 0); // disable texture

			//LPD3DXMESH boxMesh;

			//D3DXMATRIX mtxBoxWorld = *getMtxWorld();
			//mtxBoxWorld._42 += (boundingBoxMax.y - boundingBoxMin.y) / 2;

			//D3DXCreateBox(pD3DDevice, boundingBoxMax.x - boundingBoxMin.x, boundingBoxMax.y - boundingBoxMin.y, boundingBoxMax.z - boundingBoxMin.z, &boxMesh, 0);
			//pD3DDevice->SetTransform(D3DTS_WORLD, &mtxBoxWorld);
			//boxMesh->DrawSubset(0);

			//boxMesh->Release();
#endif

#ifdef ROUNDSHADOWHANDLER
			D3DXVECTOR3 *pos = getVecNowPos();
			D3DXVECTOR2 pos2D(pos->x, pos->z);
			RoundShadowHandler::addPos(pos2D);
#endif

		}
	}
}

void GameObject::calBounding(void)
{
	if (model != NULL)
	{
		D3DXMATRIX matrix;
		D3DXMatrixIdentity(&matrix);

		D3DXMATRIX scale;
		D3DXMatrixIdentity(&scale);
		D3DXMatrixScaling(&scale, vecScale->x, vecScale->y, vecScale->z);
		D3DXMatrixMultiply(&matrix, &matrix, &scale);

		BOXF boundingBox = model->getBoundingBox();
		boundingBoxMin = { boundingBox.left, boundingBox.bottom, boundingBox.front };
		D3DXVec3TransformCoord(&boundingBoxMin, &boundingBoxMin, &matrix);
		boundingBoxMax = { boundingBox.right, boundingBox.top, boundingBox.back };
		D3DXVec3TransformCoord(&boundingBoxMax, &boundingBoxMax, &matrix);
	}
}

RECTF GameObject::getBoundingRect(void)
{
	if (model != NULL)
	{
		RECTF rect;
		float maxX = Physics::round(boundingBoxMax.x, FLOAT_BITS);
		float minX = Physics::round(boundingBoxMin.x, FLOAT_BITS);
		float maxZ = Physics::round(boundingBoxMax.z, FLOAT_BITS);
		float minZ = Physics::round(boundingBoxMin.z, FLOAT_BITS);
		float posX = Physics::round(vecNowPos->x, FLOAT_BITS);
		float posZ = Physics::round(vecNowPos->z, FLOAT_BITS);

		rect.left = minX + posX;
		rect.right = maxX + posX;
		rect.top = maxZ + posZ;
		rect.bottom = minZ + posZ;
		return rect;
	}
	else
	{
		return RECTF{ 0.0f, 0.0f, 0.0f, 0.0f };
	}
}

BOXF GameObject::getBoundingBox(void)
{
	if (model != NULL)
	{
		float maxX = Physics::round(boundingBoxMax.x, FLOAT_BITS);
		float minX = Physics::round(boundingBoxMin.x, FLOAT_BITS);
		float maxY = Physics::round(boundingBoxMax.y, FLOAT_BITS);
		float minY = Physics::round(boundingBoxMin.y, FLOAT_BITS);
		float maxZ = Physics::round(boundingBoxMax.z, FLOAT_BITS);
		float minZ = Physics::round(boundingBoxMin.z, FLOAT_BITS);
		float posX = Physics::round(vecNowPos->x, FLOAT_BITS);
		float posY = Physics::round(vecNowPos->y, FLOAT_BITS);
		float posZ = Physics::round(vecNowPos->z, FLOAT_BITS);

		return BOXF{ minX + posX, maxX + posX, minY + posY, maxY + posY, minZ + posZ, maxZ + posZ };
	}
	else
	{
		return BOXF{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	}
}

D3DXVECTOR2 GameObject::getBoundingCenter(void)
{
	if (model != NULL)
	{
		RECTF rect = getBoundingRect();
		D3DXVECTOR2 center = { 0, 0 };
		center.x = Physics::round((rect.left + rect.right) / 2, FLOAT_BITS);
		center.y = Physics::round((rect.bottom + rect.top) / 2, FLOAT_BITS);
		return center;
	}
	else
	{
		D3DXVECTOR2 pos = { vecNowPos->x, vecNowPos->z };
		return pos;
	}

}

D3DXVECTOR3 GameObject::getBoundingCenter3D(void)
{
	if (model != NULL)
	{
		BOXF rect = getBoundingBox();
		D3DXVECTOR3 center = { 0, 0, 0 };
		center.x = Physics::round((rect.left + rect.right) / 2, FLOAT_BITS);
		center.y = Physics::round((rect.bottom + rect.top) / 2, FLOAT_BITS);
		center.z = Physics::round((rect.front + rect.back) / 2, FLOAT_BITS);

		return center;
	}
	else
	{
		return *vecNowPos;
	}
}

void GameObject::setBoundingCenter(D3DXVECTOR2 center)
{
	D3DXVECTOR2 boundingCenter = getBoundingCenter();
	D3DXVECTOR2 offset = { vecNowPos->x - boundingCenter.x, vecNowPos->z - boundingCenter.y };

	*vecNowPos = { center.x + offset.x, vecNowPos->y, center.y + offset.y };
}

void GameObject::setBoundingCenter3D(D3DXVECTOR3 center)
{
	D3DXVECTOR3 boundingCenter3D = getBoundingCenter3D();
	D3DXVECTOR3 offset = { vecNowPos->x - boundingCenter3D.x, vecNowPos->y - boundingCenter3D.y, vecNowPos->z - boundingCenter3D.z };

	*vecNowPos = { center.x + offset.x, center.y + offset.y, center.y + offset.y };
}

void GameObject::addSpeed(D3DXVECTOR3 * speedDir, float speed)
{
	D3DXVECTOR3 norSpeed;
	D3DXVec3Normalize(&norSpeed, speedDir);
	*vecMoveSpeed += norSpeed * speed;
}

void GameObject::calSpeed(void)
{
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
		setIsDisplay(!isDisappear);
		setOverlapLevel(-100);
	}
	else
	{
		setIsDisplay(!isDisappear);
		setOverlapLevel(ovl);
	}
}

void GameObject::resetAnimaCount(void)
{
	animaCounter = 0.001f;
}

Model * GameObject::getModel(void)
{
	return model;
}

void GameObject::setModel(Model * model)
{
	this->model = model;
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

D3DXMATRIX * GameObject::getMtxRotate(void)
{
	return mtxRotate;
}

void GameObject::setMtxRotate(D3DXMATRIX * mtxRotate)
{
	safe_delete<D3DXMATRIX>(this->mtxRotate);
	this->mtxRotate = new D3DXMATRIX(*mtxRotate);
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

bool GameObject::getIsPlayAnima(void)
{
	return isPlayAnima;
}

void GameObject::setIsPlayAnima(bool isPlayAnima)
{
	this->isPlayAnima = isPlayAnima;
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
