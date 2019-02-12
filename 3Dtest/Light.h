#pragma once
#include "stdafx.h"
class Light
{
public:
	Light();
	~Light();

	void init(LPDIRECT3DDEVICE9 pD3DDevice);
	void lightSet(LPDIRECT3DDEVICE9 pD3DDevice);
	
	void setDirection(D3DXVECTOR3* direction);
private:
	D3DLIGHT9 light;
	
	D3DXVECTOR3* direction = NULL;
};

