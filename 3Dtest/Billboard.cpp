#include "stdafx.h"
#include "Billboard.h"
#include "TextureHandler2D.h"


Vertex3D Billboard::point[4] = {
	{ { -0.5, 1, 0 }, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0xFFFFFFFF, D3DXVECTOR2(0.0f, 0.0f) },
	{ { 0.5, 1, 0 }, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0xFFFFFFFF, D3DXVECTOR2(1.0f, 0.0f) },
	{ { -0.5, 0, 0 }, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0xFFFFFFFF, D3DXVECTOR2(0.0f, 1.0f) },
	{ { 0.5, 0, 0 }, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0xFFFFFFFF, D3DXVECTOR2(1.0f, 1.0f) }
};

WORD Billboard::index[6] = {
	0, 1, 2, 2, 1, 3
};


LPDIRECT3DVERTEXBUFFER9 Billboard::pVertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 Billboard::pIndexBuffer = NULL;

Billboard::Billboard()
{
}


Billboard::~Billboard()
{
}

void Billboard::calWorldMatrix(void)
{
	D3DXMATRIX mtxWorld;
	D3DXMatrixIdentity(&mtxWorld);

	D3DXMATRIX mtxScale;
	D3DXMatrixIdentity(&mtxScale);
	mtxScale._11 = getVecScale()->x;
	mtxScale._22 = getVecScale()->y;
	mtxScale._33 = getVecScale()->z;

	D3DXMATRIX mtxTrans;
	D3DXMatrixIdentity(&mtxTrans);
	mtxTrans._41 = getVecNowPos()->x;
	mtxTrans._42 = getVecNowPos()->y;
	mtxTrans._43 = getVecNowPos()->z;

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &camera->getInvMatrix());
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	setMtxWorld(&mtxWorld);
}

void Billboard::draw(LPDIRECT3DDEVICE9 pD3DDevice)
{
	Vertex3D *pv;
	pVertexBuffer->Lock(0, 0, (void**)&pv, 0);
	memcpy(pv, point, sizeof(point));
	pVertexBuffer->Unlock();

	WORD* pIndex;
	pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);
	memcpy(pIndex, index, sizeof(index));
	pIndexBuffer->Unlock();

	//set FVF
	pD3DDevice->SetFVF(FVF_VERTEX3D);
	pD3DDevice->SetTexture(0, TextureHandler2D::GetTexture(textureIndex).tex_p);

	pD3DDevice->SetStreamSource(0, Billboard::pVertexBuffer, 0, sizeof(Vertex3D));
	pD3DDevice->SetIndices(Billboard::pIndexBuffer);
	//set world matrix
	pD3DDevice->SetTransform(D3DTS_WORLD, getMtxWorld());
	//draw
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

RECTF Billboard::getBoundingRect(void)
{
	return RECTF{ 0.0f, 0.0f, 0.0f, 0.0f };
}

D3DXVECTOR2 Billboard::getBoundingCenter(void)
{
	return D3DXVECTOR2(0.0f, 0.0f);
}

void Billboard::setBoundingCenter(D3DXVECTOR2 center)
{
}

void Billboard::setCamera(Camera const* camera)
{
	this->camera = camera;
}

void Billboard::setTextureIndex(int index)
{
	this->textureIndex = index;
}

void Billboard::initStaticMember(LPDIRECT3DDEVICE9 pD3DDevice)
{
	if (pVertexBuffer == NULL)
	{
		pD3DDevice->CreateVertexBuffer(sizeof(Vertex3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &pVertexBuffer, NULL);
	}
	if (pIndexBuffer == NULL)
	{
		pD3DDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, NULL);
	}
}
