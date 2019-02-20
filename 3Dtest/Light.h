#pragma once
/*==============================================================================

[Light.h]
Author : darknessWONG
Date   : 2018/10/20
--------------------------------------------------------------------------------

==============================================================================*/
#include "stdafx.h"
class Light
{
public:
	Light();
	~Light();

	/*===========================================
	public function
	============================================*/
	void init(LPDIRECT3DDEVICE9 pD3DDevice);
	void lightSet(LPDIRECT3DDEVICE9 pD3DDevice);

	/*===========================================
	public geter / seter
	============================================*/
	void setDirection(D3DXVECTOR3* direction);
private:
	D3DLIGHT9 light;
	
	D3DXVECTOR3* direction = NULL;
};

