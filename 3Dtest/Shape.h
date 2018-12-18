#pragma once
#include "stdafx.h"
class Shape
{
public:
	Shape();
	~Shape();

	/*===========================================
	virtual member
	============================================*/
	virtual void draw(LPDIRECT3DDEVICE9 pD3DDevice) = 0;
	void setMtxWorld(D3DXMATRIX mtxWorld) = 0;

};

