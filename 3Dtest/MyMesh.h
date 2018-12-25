#pragma once
#include "GameObject.h"
#include "Parts.h"
class MyMesh :
	public GameObject
{
public:
	MyMesh();
	~MyMesh();

	/*===========================================
	virtual member
	============================================*/
	virtual void dataUpdate(void);
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
	Parts* getPartsByIndex(int index);
	BOOL partsMove(int index, D3DXVECTOR3* scale, D3DXVECTOR3* rotation, D3DXVECTOR3* transport, D3DXVECTOR3* revolution);

	/*===========================================
	public geter / seter
	============================================*/
	string getModelClass(void);
	void setModelClass(string modelClass);
	Parts* getParts(void);
	void setParts(Parts* part);

private:
	void findBoundingRect(Parts* part, D3DXVECTOR2& lt, D3DXVECTOR2& rb);

	string modelClass;
	Parts* parts;
};

