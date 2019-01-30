#pragma once
#include "Billboard.h"
#include "Chara.h"
class NameTap :
	public Billboard
{
public:
	NameTap();
	~NameTap();

	/*===========================================
	virtual member
	============================================*/
	virtual void dataUpdate(void);
	virtual void positionUpdateX(void);
	virtual void positionUpdateY(void);
	virtual void positionUpdateZ(void);
	virtual void positionUpdate(void);
	virtual void draw(LPDIRECT3DDEVICE9 pD3DDevice);

	/*===========================================
	public function
	============================================*/
	void initName(LPDIRECT3DDEVICE9 pD3DDevice);

	/*===========================================
	public geter / seter
	============================================*/
	void setBelong(Chara* belong);

private:
	Chara* belong;
	ID3DXMesh* Text = NULL;
};

