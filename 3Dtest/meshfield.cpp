#include "stdafx.h"
#include "meshfield.h"
#include "texture.h"
#include "common.h"

#define PI (3.14159265358979323846)

#define FVF_VERTEX3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

static const D3DXVECTOR3 normalin[] = {
	D3DXVECTOR3(0.0f, 0.0f,-1.0f),			// front
	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),			// left
	D3DXVECTOR3(1.0f, 0.0f, 0.0f),			// right
	D3DXVECTOR3(0.0f, 0.0f, 1.0f),			// back
	D3DXVECTOR3(0.0f, 1.0f, 0.0f),			// top
	D3DXVECTOR3(0.0f,-1.0f, 0.0f),			// bot
};

Meshfield::Meshfield()
{
}

Meshfield::~Meshfield()
{
	delete[] vertices;
	vertices = NULL;

	delete[] indexs;
	indexs = NULL;
}

void Meshfield::Initialize(float width, int sx, int sy, int texture, LPDIRECT3DDEVICE9 pDevice)
{
	g_texture = texture;

	numVertice = (sx + 1) * (sy + 1);
	numIndex = (sy + 1) * 2 * sx + 2 * (sx - 1);
	numGrid = sx * sy * 2 + 3 * (sx - 1);

	vertices = new Mesh3D[numVertice];
	// create vertices position
	idx = 0;
	for (int i = 0; i <= sx; i++) {
		for (int j = 0; j <= sy; j++) {
			vertices[idx] = { D3DXVECTOR3(width * i - width * sx / 2, 0.0f, width * sy / 2 - width * j), 
				normalin[4], 
				0xffffffff, 
				D3DXVECTOR2(1.0f * i , 1.0f * j) 
			};
			idx++;
		}
	}


	indexs = new WORD[numIndex];
	// create vertices index
	cur = 0;
	for (int i = 0; i < sx; i++) {
		if (i > 0) {
			// double next row start point in case of not start point
			indexs[cur] = i * (sy + 1);
			cur++;
		}
		for (int j = 0; j <= sy; j++) {
			// left vertice
			indexs[cur] = i * (sy + 1) + j;
			cur++;

			// right vertice
			indexs[cur] = (i + 1) * (sy + 1) + j;
			cur++;
		}
		// double end point
		if (i + 1 < sx) {
			indexs[cur] = indexs[cur - 1];
			cur++;
		}
	}

	// create buffer
	VOID* pVoid;
	pDevice->CreateVertexBuffer(numVertice * sizeof(Mesh3D), 0, FVF_VERTEX3D, D3DPOOL_MANAGED, &vertex_buffer, NULL);

	vertex_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, vertices, sizeof(*vertices) * numVertice);
	vertex_buffer->Unlock();

	// Setting Index Buffer
	pDevice->CreateIndexBuffer(numIndex * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &index_buffer, NULL);

	index_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, indexs, sizeof(*indexs) * numIndex);
	index_buffer->Unlock();
}

void Meshfield::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	// Setting Primitive Draw by index
	pDevice->SetStreamSource(0, vertex_buffer, 0, sizeof(Mesh3D));
	pDevice->SetIndices(index_buffer);

	D3DXMATRIX mtxWorld;
	D3DXMatrixIdentity(&mtxWorld);
	
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	
	IDirect3DStateBlock9* pStateBlock = NULL;
	pDevice->CreateStateBlock(D3DSBT_ALL, &pStateBlock);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		// light off
	pDevice->SetTexture(0, Texture_GetTexture(g_texture));
	
	pDevice->SetFVF(FVF_VERTEX3D);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, numVertice, 0, numIndex-2);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pStateBlock->Apply();
	pStateBlock->Release();
}

