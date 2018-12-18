#pragma once
#include "GameObject.h"
#include "Parts.h"
class Human :
	public GameObject
{
public:
	Human();
	~Human();

	/*===========================================
	virtual member
	============================================*/
	virtual void calWorldMatrix(void);
	virtual void dataUpdate(void);
	virtual void positionUpdateX(void);
	virtual void positionUpdateY(void);
	virtual void positionUpdateZ(void);
	virtual void positionUpdate(void);
	virtual void draw(LPDIRECT3DDEVICE9 pD3DDevice);
	virtual RECTF getBoundingRect(void);
	//the center of the bounding box
	//position may not be the center of the bounding box, so it have to be calculate
	virtual D3DXVECTOR2 getBoundingCenter(void);
	//calculate vecNowPos through center, set vecNowPos to let the bounding center get on the position where center at.
	virtual void setBoundingCenter(D3DXVECTOR2 center);

	/*===========================================
	public function
	============================================*/

	/*===========================================
	public geter / seter
	============================================*/


private:
	void findBoundingRect(Parts* part, D3DXVECTOR2& lt, D3DXVECTOR2& rb);

	Parts* parts;
};

