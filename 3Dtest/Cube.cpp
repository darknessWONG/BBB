#include "stdafx.h"
#include "Cube.h"

Vertex3D Cube::cubeVertex[CUBE_VERTEX_NUM] = {
	//back
	{ { 0.5, 1, 0.5 }, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0xFFFFFFFF, D3DXVECTOR2(1.0f, 0.0f) },
	{ { -0.5, 1, 0.5 }, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0xFFFFFFFF, D3DXVECTOR2(0.0f, 0.0f) },
	{ { 0.5, 0, 0.5 }, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0xFFFFFFFF, D3DXVECTOR2(1.0f, 1.0f) },
	{ { -0.5, 0, 0.5 }, D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0xFFFFFFFF, D3DXVECTOR2(0.0f, 1.0f) },
	//front
	{ { -0.5, 1, -0.5 }, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0xFFFFFFFF, D3DXVECTOR2(1.0f, 0.0f) },
	{ { 0.5, 1, -0.5 }, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0xFFFFFFFF, D3DXVECTOR2(0.0f, 0.0f) },
	{ { -0.5, 0, -0.5 }, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0xFFFFFFFF, D3DXVECTOR2(1.0f, 1.0f) },
	{ { 0.5, 0, -0.5 }, D3DXVECTOR3(0.0f, 0.0f, -1.0f), 0xFFFFFFFF, D3DXVECTOR2(0.0f, 1.0f) },
	//top
	{ { -0.5, 1, 0.5 }, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(1.0f, 0.0f) },
	{ { 0.5, 1, 0.5 }, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(0.0f, 0.0f) },
	{ { -0.5, 1, -0.5 }, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(1.0f, 1.0f) },
	{ { 0.5, 1, -0.5 }, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(0.0f, 1.0f) },
	//bottom
	{ { -0.5, 0, -0.5 }, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(1.0f, 0.0f) },
	{ { 0.5, 0, -0.5 }, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(0.0f, 0.0f) },
	{ { -0.5, 0, 0.5 }, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(1.0f, 1.0f) },
	{ { 0.5, 0, 0.5 }, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(0.0f, 1.0f) },
	//left
	{ { -0.5, 1, 0.5 }, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(1.0f, 0.0f) },
	{ { -0.5, 1, -0.5 }, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(0.0f, 0.0f) },
	{ { -0.5, 0, 0.5 }, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(1.0f, 1.0f) },
	{ { -0.5, 0, -0.5 }, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(0.0f, 1.0f) },
	//right
	{ { 0.5, 1, -0.5 }, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(1.0f, 0.0f) },
	{ { 0.5, 1, 0.5 }, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(0.0f, 0.0f) },
	{ { 0.5, 0, -0.5 }, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(1.0f, 1.0f) },
	{ { 0.5, 0, 0.5 }, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(0.0f, 1.0f) }
};

WORD Cube::cubeIndex[CUBE_INDEX_NUM] = {
	0, 1, 2, 2, 1, 3,
	4, 5, 6, 6, 5, 7,
	8, 9, 10, 10, 9, 11,
	12, 13, 14, 14, 13, 15,
	16, 17, 18, 18, 17, 19,
	20, 21, 22, 22, 21, 23
};

LPDIRECT3DVERTEXBUFFER9 Cube::pVertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 Cube::pIndexBuffer = NULL;

Cube::Cube()
{
	D3DXMatrixIdentity(&mtxWorld);
}


Cube::~Cube()
{
}

void Cube::draw(LPDIRECT3DDEVICE9 pD3DDevice)
{
	//set FVF
	pD3DDevice->SetFVF(FVF_VERTEX3D);
	pD3DDevice->SetTexture(0, NULL);

	pD3DDevice->SetStreamSource(0, Cube::pVertexBuffer, 0, sizeof(Vertex3D));
	pD3DDevice->SetIndices(Cube::pIndexBuffer);	
	//make the polygon hollow
	pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//set world matrix
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	//draw
	pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
	//restore
	pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void Cube::setMtxWorld(D3DXMATRIX mtxWorld)
{
	D3DXMatrixIdentity(&this->mtxWorld);
	this->mtxWorld *= mtxWorld;
}

void Cube::initStaticMember(LPDIRECT3DDEVICE9 pD3DDevice)
{
	if (pVertexBuffer == NULL)
	{
		pD3DDevice->CreateVertexBuffer(sizeof(Vertex3D) * CUBE_VERTEX_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &pVertexBuffer, NULL);
	}
	if (pIndexBuffer == NULL)
	{
		pD3DDevice->CreateIndexBuffer(sizeof(WORD) * CUBE_INDEX_NUM, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, NULL);
	}

	Vertex3D *pv;
	pVertexBuffer->Lock(0, 0, (void**)&pv, 0);
	memcpy(pv, cubeVertex, sizeof(cubeVertex));
	pVertexBuffer->Unlock();

	WORD* pIndex;
	pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);
	memcpy(pIndex, cubeIndex, sizeof(cubeIndex));
	pIndexBuffer->Unlock();
}
