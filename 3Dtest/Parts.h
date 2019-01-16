#pragma once
#include "Shape.h"
#include "Cube.h"
class Parts
{
public:
	Parts();
	~Parts();

	/*===========================================
	virtual member
	============================================*/

	/*===========================================
	public function
	============================================*/
	void draw(LPDIRECT3DDEVICE9 pD3DDevice, D3DXMATRIX parentMtx);
	/*it update in the following order:
	scale->rotation->transport->revolution*/
	void dataUpdate(void);
	void addChild(Parts* part);
	void addNext(Parts* part);
	void releaseChain(void);
	/*===========================================
	public geter / seter
	============================================*/
	//scale of axis x, y, z
	D3DXVECTOR3 getBaseOffsetS(void);
	//scale of axis x, y, z
	void setBaseOffsetS(D3DXVECTOR3 offsetS);
	//angle of rotation on axis x, y, z
	D3DXVECTOR3 getBaseOffsetR(void);
	//angle of rotation on axis x, y, z
	void setBaseOffsetR(D3DXVECTOR3 offsetR);
	//transport distans
	D3DXVECTOR3 getBaseOffsetT(void);
	//transport distans
	void setBaseOffsetT(D3DXVECTOR3 offsetT);
	//angle ofo revolution on axis x, y, z
	D3DXVECTOR3 getBaseRotation(void);
	//angle ofo revolution on axis x, y, z
	void setBaseRotation(D3DXVECTOR3 rotation);

	//scale of axis x, y, z
	D3DXVECTOR3 getOffsetS(void);
	//scale of axis x, y, z
	void setOffsetS(D3DXVECTOR3 offsetS);
	//angle of rotation on axis x, y, z
	D3DXVECTOR3 getOffsetR(void);
	//angle of rotation on axis x, y, z
	void setOffsetR(D3DXVECTOR3 offsetR);
	//transport distans
	D3DXVECTOR3 getOffsetT(void);
	//transport distans
	void setOffsetT(D3DXVECTOR3 offsetT);
	//angle ofo revolution on axis x, y, z
	D3DXVECTOR3 getRotation(void);
	//angle ofo revolution on axis x, y, z
	void setRotation(D3DXVECTOR3 rotation);

	Shape* getModel(void);
	void setModel(Shape* model);

	Parts* getChild(void);
	Parts* getNext(void);
private:
	void releaseChild(void);
	void releaseNext(void);

	D3DXMATRIX mtxWorld;

	/*This part's base relative position wiht it's parent
	It is a reference to let the system know how much part moved
	It will be referenced when part want to return to the start posture*/
	//scale of axis x, y, z
	D3DXVECTOR3 baseOffsetS;
	//angle of rotation on axis x, y, z
	D3DXVECTOR3 baseOffsetR;
	//transport distans
	D3DXVECTOR3 baseOffsetT;
	//angle ofo revolution on axis x, y, z
	D3DXVECTOR3 baseRotation;

	/*this part's relative position wiht it's parent now
	It is the real offset use for drawing and calculating
	modify these variable when just want to move the part*/
	D3DXVECTOR3 offsetS;
	D3DXVECTOR3 offsetR;
	D3DXVECTOR3 offsetT;
	D3DXVECTOR3 rotation;

	Shape* model = NULL;

	Parts* child = NULL;
	Parts* next = NULL;
};

