#pragma once
#include "SpecialArea.h"
#include "stdafx.h"
class BattleArea :
	public SpecialArea
{
public:
	BattleArea(Cycle cycle);
	virtual ~BattleArea();

	/*===========================================
	virtual member
	============================================*/
	virtual void calWorldMatrix(void);
	virtual void dataUpdate(void);
	virtual void draw(LPDIRECT3DDEVICE9 pD3DDevice);
	virtual RECTF getBoundingRect(void);
	//the center of the bounding box
	//position may not be the center of the bounding box, so it have to be calculate
	virtual D3DXVECTOR2 getBoundingCenter(void);
	virtual void setBoundingCenter(D3DXVECTOR2 center);

	/*===========================================
	public function
	============================================*/

	/*===========================================
	public geter / seter
	============================================*/
	void setCycle(Cycle cycle);
private:
	Cycle cycle;

	Vertex3D* point;
	WORD* index;

	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
};

