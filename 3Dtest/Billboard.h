#pragma once

/*==============================================================================

[Billboard.h]
Author : darknessWONG
Date   : 2019/01/15
--------------------------------------------------------------------------------

==============================================================================*/
#include "stdafx.h"
#include "GameObject.h"
#include "Camera.h"
class Billboard :
	public GameObject
{
public:
	Billboard();
	~Billboard();
	/*===========================================
	virtual member
	============================================*/
	virtual void calWorldMatrix(void);
	virtual void draw(LPDIRECT3DDEVICE9 pD3DDevice);
	virtual RECTF getBoundingRect(void);
	//the center of the bounding box
	//position may not be the center of the bounding box, so it have to be calculate
	virtual D3DXVECTOR2 getBoundingCenter(void);
	//calculate vecNowPos through center, set vecNowPos to let the bounding center get on the position where center at.
	virtual void setBoundingCenter(D3DXVECTOR2 center);

	/*===========================================
	public geter/seter
	============================================*/
	void setCamera(Camera const* camera);
	void setTextureIndex(int index);

	/*===========================================
	static public function
	============================================*/
	//This function should be called once before this call first time be instanced
	static void initStaticMember(LPDIRECT3DDEVICE9 pD3DDevice);

	static LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
	static LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
private:
	Camera const* camera;
	int textureIndex;

	static Vertex3D point[4];
	static WORD index[6];

};

