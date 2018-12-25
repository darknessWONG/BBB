#include "stdafx.h"
#include "Parts.h"


Parts::Parts()
{
	D3DXMatrixIdentity(&mtxWorld);

	baseOffsetS = { 1, 1, 1 };
	baseOffsetR = {0, 0, 0};
	baseOffsetT = {0, 0, 0};
	baseRotation = {0, 0, 0};

	offsetS = { 1, 1, 1 };
	offsetR = {0, 0, 0};
	offsetT = {0, 0, 0};
	rotation = {0, 0, 0};

	model = NULL;

	child = NULL;
	next = NULL;
}


Parts::~Parts()
{
}

void Parts::draw(LPDIRECT3DDEVICE9 pD3DDevice, D3DXMATRIX parentMtx)
{
	mtxWorld *= parentMtx;
	model->setMtxWorld(mtxWorld);
	model->draw(pD3DDevice);

	if (next != NULL)
	{
		next->draw(pD3DDevice, parentMtx);
	}
	if (child != NULL)
	{
		child->draw(pD3DDevice, mtxWorld);
	}

}

void Parts::dataUpdate(void)
{
	D3DXMatrixIdentity(&mtxWorld);

	D3DXMATRIX mtxOffsetS;
	D3DXMatrixIdentity(&mtxOffsetS);
	D3DXMatrixScaling(&mtxOffsetS, offsetS.x, offsetS.y, offsetS.z);

	D3DXMATRIX mtxOffsetR;
	D3DXMatrixIdentity(&mtxOffsetR);
	D3DXMatrixRotationYawPitchRoll(&mtxOffsetR, D3DXToRadian(offsetR.y), D3DXToRadian(offsetR.x), D3DXToRadian(offsetR.z));

	D3DXMATRIX mtxOffsetT;
	D3DXMatrixIdentity(&mtxOffsetT);
	D3DXMatrixTranslation(&mtxOffsetT, offsetT.x, offsetT.y, offsetT.z);

	D3DXMATRIX mtxRotation;
	D3DXMatrixIdentity(&mtxRotation);
	D3DXMatrixRotationYawPitchRoll(&mtxRotation, D3DXToRadian(rotation.y), D3DXToRadian(rotation.x), D3DXToRadian(rotation.z));

	mtxWorld = mtxOffsetS * mtxOffsetR * mtxOffsetT * mtxRotation;

	if (next != NULL)
	{
		next->dataUpdate();
	}
	if (child != NULL)
	{
		child->dataUpdate();
	}
}

D3DXVECTOR3 Parts::getBaseOffsetS(void)
{
	return baseOffsetS;
}

void Parts::setBaseOffsetS(D3DXVECTOR3 offsetS)
{
	this->baseOffsetS = offsetS;
}

D3DXVECTOR3 Parts::getBaseOffsetR(void)
{
	return baseOffsetR;
}

void Parts::setBaseOffsetR(D3DXVECTOR3 offsetR)
{
	this->baseOffsetR = offsetR;
}

D3DXVECTOR3 Parts::getBaseOffsetT(void)
{
	return baseOffsetT;
}

void Parts::setBaseOffsetT(D3DXVECTOR3 offsetT)
{
	this->baseOffsetT = offsetT;
}

D3DXVECTOR3 Parts::getBaseRotation(void)
{
	return baseRotation;
}

void Parts::setBaseRotation(D3DXVECTOR3 rotation)
{
	this->baseRotation = rotation;
}

D3DXVECTOR3 Parts::getOffsetS(void)
{
	return offsetS;
}

void Parts::setOffsetS(D3DXVECTOR3 offsetS)
{
	this->offsetS = offsetS;
}

D3DXVECTOR3 Parts::getOffsetR(void)
{
	return offsetR;
}

void Parts::setOffsetR(D3DXVECTOR3 offsetR)
{
	this->offsetR = offsetR;
}

D3DXVECTOR3 Parts::getOffsetT(void)
{
	return offsetT;
}

void Parts::setOffsetT(D3DXVECTOR3 offsetT)
{
	this->offsetT = offsetT;
}

D3DXVECTOR3 Parts::getRotation(void)
{
	return rotation;
}

void Parts::setRotation(D3DXVECTOR3 rotation)
{
	this->rotation = rotation;
}

Shape * Parts::getModel(void)
{
	return model;
}

void Parts::setModel(Shape * model)
{
	this->model = model;
}

Parts * Parts::getChild(void)
{
	return child;
}

Parts * Parts::getNext(void)
{
	return next;
}

void Parts::addChild(Parts * parts)
{
	if (child == NULL)
	{
		child = parts;
	}
	else
	{
		Parts* tmp = child;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = parts;
	}
}

void Parts::addNext(Parts * parts)
{
	if (next == NULL)
	{
		next = parts;
	}
	else
	{
		Parts* tmp = next;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = parts;
	}
}

void Parts::releaseChain(void)
{
	if (child != NULL)
	{
		child->releaseChain();
	}
	if (next != NULL)
	{
		next->releaseChain();
	}
	releaseNext();
	releaseChild();
}

void Parts::releaseChild(void)
{
	if (child != NULL)
	{
		child = NULL;
	}
}

void Parts::releaseNext(void)
{
	if (next != NULL)
	{
		next = NULL;
	}
}