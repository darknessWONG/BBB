#include "stdafx.h"
#include "BattleArea.h"
#include "TextureHandler2D.h"
#include "Common.h"
#include "Billboard.h"


BattleArea::BattleArea(Cycle cycle)
	:cycle(cycle)
{
	point = new Vertex3D[CYCLE_SEGMENTATION + 1];
	index = new WORD[CYCLE_SEGMENTATION * 3];

	ZeroMemory(point, (CYCLE_SEGMENTATION + 1) * sizeof(Vertex3D));
	ZeroMemory(index, CYCLE_SEGMENTATION * 3 * sizeof(WORD));

	for (int i = 0, j = 1; i < CYCLE_SEGMENTATION * 3; i += 3, j++)
	{
		index[i] = 0;
		index[i + 1] = j;
		index[i + 2] = j + 1 > CYCLE_SEGMENTATION ? 1 : j + 1;
	}

	// 頂点バッファの確保（頂点４つ分）
	Common::g_pD3DDevice->CreateVertexBuffer(sizeof(Vertex3D) * (CYCLE_SEGMENTATION + 1), D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &pVertexBuffer, NULL);

	// インデックスバッファの確保（インデックス６個分）
	Common::g_pD3DDevice->CreateIndexBuffer(sizeof(WORD) * CYCLE_SEGMENTATION * 3, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, NULL);
}


BattleArea::~BattleArea()
{
	safe_delete<Vertex3D>(point);
	safe_delete<WORD>(index);
	SAFE_RELEASE(pVertexBuffer);
	SAFE_RELEASE(pIndexBuffer);

}

void BattleArea::calWorldMatrix(void)
{
	D3DXMATRIX mtxWorld;
	D3DXMatrixIdentity(&mtxWorld);

	D3DXMATRIX mtxScale;
	D3DXMatrixIdentity(&mtxScale);
	mtxScale._11 = getVecScale()->x;
	mtxScale._22 = getVecScale()->y;
	mtxScale._33 = getVecScale()->z;

	D3DXVECTOR3 newPos = *getVecNowPos();
	D3DXMATRIX mtxSphereWorld;
	D3DXMatrixIdentity(&mtxSphereWorld);
	mtxSphereWorld._41 += newPos.x;
	mtxSphereWorld._42 += newPos.y;
	mtxSphereWorld._43 += newPos.z;

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxSphereWorld);

	setMtxWorld(&mtxWorld);
}

void BattleArea::dataUpdate(void)
{
	D3DXVECTOR3 pos = { cycle.center_x, 0, cycle.center_y };
	setVecNowPos(&pos);

	ZeroMemory(point, (CYCLE_SEGMENTATION + 1) * sizeof(Vertex3D));
	point[0] = { {0.0f, 0.01f, 0.0f}, {0, 1, 0}, 0x88FF0000, {0, 0} };


	float preDegree = 360 / CYCLE_SEGMENTATION;
	for (int i = 1; i < CYCLE_SEGMENTATION + 1; i++)
	{
		int dergree = i * preDegree;
		double radian = D3DXToRadian(dergree);
		double sin1;
		if ((dergree % 90) == 0 && (dergree % 90) % 2 == 0)
		{
			sin1 = 0;
		}
		else
		{
			sin1 = sin(radian);
		}
		point[i].pos.x = cycle.r * sin1;
		point[i].pos.y = 0.01f;
		double cos1;
		if((dergree % 90) == 0 && (dergree % 90) % 2 == 1)
		{
			cos1 = 0;
		}
		else
		{
			cos1 = cos(radian);
		}

		point[i].pos.z = cycle.r * cos1;
		point[i].normal = { 0, 1, 0 };
		point[i].color = 0x88FF0000;
		point[i].uv = { 0.0f, 0.0f };
	}

	SpecialArea::dataUpdate();
}

void BattleArea::draw(LPDIRECT3DDEVICE9 pD3DDevice)
{
	if (getIsDisplay())
	{
		WORD* pIndex; // 仮想アドレス
		pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);
		memcpy(pIndex, index, CYCLE_SEGMENTATION * 3 * sizeof(WORD));
		pIndexBuffer->Unlock();

		Vertex3D* pV;
		pVertexBuffer->Lock(0, 0, (void**)&pV, 0);
		memcpy(pV, point, (CYCLE_SEGMENTATION + 1) * sizeof(Vertex3D));
		pVertexBuffer->Unlock();

		//set special attribute
		pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		//pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		pD3DDevice->SetFVF(FVF_VERTEX3D);
		pD3DDevice->SetTexture(0, NULL);
		pD3DDevice->SetTransform(D3DTS_WORLD, getMtxWorld());
		pD3DDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(Vertex3D));
		pD3DDevice->SetIndices(pIndexBuffer);
		//draw
		pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, CYCLE_SEGMENTATION + 1, 0, CYCLE_SEGMENTATION);

		//restore special attribute
		pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		//pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

RECTF BattleArea::getBoundingRect(void)
{
	return RECTF{ 0, 0, 0, 0 };
}

D3DXVECTOR2 BattleArea::getBoundingCenter(void)
{
	return { cycle.center_x, cycle.center_y };
}

void BattleArea::setBoundingCenter(D3DXVECTOR2 center)
{
}

Cycle BattleArea::getCycle(void)
{
	return cycle;
}

void BattleArea::setCycle(Cycle cycle)
{
	this->cycle = cycle;
}

