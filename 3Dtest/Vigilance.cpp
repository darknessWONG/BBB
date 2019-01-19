#include "stdafx.h"
#include "Vigilance.h"
#include "Common.h"


Vigilance::Vigilance()
{
}


Vigilance::~Vigilance()
{
}

void Vigilance::calWorldMatrix(void)
{
	D3DXVECTOR3 newPos = *getVecNowPos();
	D3DXMATRIX mtxSphereWorld;
	D3DXMatrixIdentity(&mtxSphereWorld);
	mtxSphereWorld._41 += newPos.x;
	mtxSphereWorld._42 += newPos.y;
	mtxSphereWorld._43 += newPos.z;

	setMtxWorld(&mtxSphereWorld);
}

void Vigilance::dataUpdate(void)
{
	if (belong != NULL)
	{
		D3DXVECTOR2 center = belong->getBoundingCenter();
		D3DXVECTOR3 newPos = D3DXVECTOR3(center.x, 0, center.y);
		setVecNowPos(&newPos);
	}

	SpecialArea::dataUpdate();
}

void Vigilance::draw(LPDIRECT3DDEVICE9 pD3DDevice)
{
	if (getIsDisplay())
	{
#ifdef _DEBUG
		D3DMATERIAL9 blue;
		blue.Diffuse = { 1.0f, 1.0f, 1.0f, 0.5f };
		blue.Ambient = blue.Diffuse;
		//blue.Emissive = blue.Diffuse;
		//blue.Specular = blue.Diffuse;

		pD3DDevice->SetMaterial(&blue);
		pD3DDevice->SetTexture(0, 0); // disable texture

		LPD3DXMESH SphereMesh;
		D3DXCreateSphere(pD3DDevice, getRadius(), 16, 16, &SphereMesh, NULL);
		//D3DXCreateBox(pD3DDevice, boundingBoxMax.x - boundingBoxMin.x, boundingBoxMax.y - boundingBoxMin.y, boundingBoxMax.z - boundingBoxMin.z, &boxMesh, 0);
		//D3DXCreateSphere(pD3DDevice, boundingSphereRadius, 20, 20, &sphereMesh, 0);
		pD3DDevice->SetTransform(D3DTS_WORLD, getMtxWorld());
		SphereMesh->DrawSubset(0);

		SphereMesh->Release();
#endif
	}
}

RECTF Vigilance::getBoundingRect(void)
{
	return RECTF{ 0, 0, 0, 0 };
}

D3DXVECTOR2 Vigilance::getBoundingCenter(void)
{
	D3DXVECTOR3 nowPos = *getVecNowPos();
	return D3DXVECTOR2(nowPos.x, nowPos.z);
}

void Vigilance::setBoundingCenter(D3DXVECTOR2 center)
{
	D3DXVECTOR3 nowPos = *getVecNowPos();
	nowPos.x = center.x;
	nowPos.z = center.y;
	setVecNowPos(&nowPos);
}

Chara * Vigilance::getBelong(void)
{
	return belong;
}

void Vigilance::setBelong(Chara * belong)
{
	this->belong = belong;
}
