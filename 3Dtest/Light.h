#pragma once
#include "stdafx.h"
class Light
{
public:
	Light();
	~Light();

	void init(LPDIRECT3DDEVICE9 pD3DDevice);
	void lightSet(LPDIRECT3DDEVICE9 pD3DDevice);
private:
	D3DLIGHT9 light;
};

