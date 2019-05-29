#include "stdafx.h"
#include "TextureHandler2D.h"
#include "Common.h"
#include "RoundShadowHandler.h"


vector<D3DXVECTOR2> RoundShadowHandler::pos;
int RoundShadowHandler::textureIndex;
Vertex3D RoundShadowHandler::point[4] = {
	{ { -0.5, 0, 0.5 }, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(0.0f, 0.0f) },
	{ { 0.5, 0, 0.5 }, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(1.0f, 0.0f) },
	{ { -0.5, 0, -0.5 }, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(0.0f, 1.0f) },
	{ { 0.5, 0, -0.5 }, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0xFFFFFFFF, D3DXVECTOR2(1.0f, 1.0f) }
};

WORD RoundShadowHandler::index[6] = {
	0, 1, 2, 2, 1, 3
};

LPDIRECT3DVERTEXBUFFER9 RoundShadowHandler::pVertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 RoundShadowHandler::pIndexBuffer = NULL;

RoundShadowHandler::RoundShadowHandler()
{

}


RoundShadowHandler::~RoundShadowHandler()
{
}

void RoundShadowHandler::draw(LPDIRECT3DDEVICE9 pD3DDevice)
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
	//set texture
	pD3DDevice->SetTexture(0, TextureHandler2D::GetTexture(textureIndex).tex_p);

	pD3DDevice->SetStreamSource(0, RoundShadowHandler::pVertexBuffer, 0, sizeof(Vertex3D));
	pD3DDevice->SetIndices(RoundShadowHandler::pIndexBuffer);

	//set alpha
	pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	//set lighting
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int i = 0; i < RoundShadowHandler::pos.size(); i++)
	{
		D3DXMATRIX mtxWorld;
		D3DXMatrixIdentity(&mtxWorld);
		D3DXMatrixTranslation(&mtxWorld, pos[i].x, 0.1, pos[i].y);
		//set world matrix
		pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		//draw
		pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	}

	//restore alpha
	pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//restore lighting
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pos.clear();
}

void RoundShadowHandler::init(LPDIRECT3DDEVICE9 pD3DDevice, int textureIndex)
{
	if (pVertexBuffer == NULL)
	{
		pD3DDevice->CreateVertexBuffer(sizeof(Vertex3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &pVertexBuffer, NULL);
	}
	if (pIndexBuffer == NULL)
	{
		pD3DDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, NULL);
	}
	RoundShadowHandler::setTextureIndex(textureIndex);
}

void RoundShadowHandler::setTextureIndex(int textureIndex)
{
	RoundShadowHandler::textureIndex = textureIndex;
}

void RoundShadowHandler::addPos(D3DXVECTOR2 pos)
{
	RoundShadowHandler::pos.push_back(pos);
}
