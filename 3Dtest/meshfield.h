//=============================================================================
//
// フィールドメッシュ
//
//=============================================================================
#pragma once

#ifndef MESHFIELD_H_
#define MESHFIELD_H_

#include "stdafx.h"
#include <d3dx9.h>

class Meshfield {
public:
	Meshfield();
	~Meshfield();

	void Initialize(float width, int sx, int sy, int texture, LPDIRECT3DDEVICE9 pDevice);
	void Draw(LPDIRECT3DDEVICE9 pDevice);

private:
	typedef struct
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DCOLOR color;
		D3DXVECTOR2 texcoord;
	}Mesh3D;

	LPDIRECT3DINDEXBUFFER9 index_buffer;
	LPDIRECT3DVERTEXBUFFER9 vertex_buffer;

	int numVertice;
	int numIndex;
	int numGrid;

	int idx;
	int cur;
	int g_texture;

	Mesh3D* vertices;
	WORD* indexs;
};

#endif