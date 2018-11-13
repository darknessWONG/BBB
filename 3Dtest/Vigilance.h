#pragma once
#include "SpecialArea.h"
#include "Chara.h"
class Vigilance :
	public SpecialArea
{
public:
	Vigilance();
	~Vigilance();
	
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

	/*===========================================
	public geter / seter
	============================================*/
	Chara* getBelong(void);
	void setBelong(Chara* belong);
private:
	Chara* belong;
};

