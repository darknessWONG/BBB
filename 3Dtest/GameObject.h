#pragma once
/*==============================================================================

[GameObject.h]
Author : darknessWONG
Date   : 2018/11/23
--------------------------------------------------------------------------------
The base unit in this game,
everything you want to draw of do the collision should be a gameObject
==============================================================================*/
#include <d3dx9.h>
#include "Physics.h"
#include "Model.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	/*===========================================
	virtual member
	============================================*/
	virtual void calWorldMatrix(void);
	virtual void beforeUpdate(void);
	virtual void dataUpdate(void);
	virtual void positionUpdateX(void);
	virtual void positionUpdateY(void);
	virtual void positionUpdateZ(void);
	virtual void positionUpdate(void);
	virtual void draw(LPDIRECT3DDEVICE9 pD3DDevice);
	/*cal the new bounding box 
	so that you should call it every time you set a new position or bounding center*/
	virtual void calBounding(void);
	virtual RECTF getBoundingRect(void);
	virtual BOXF getBoundingBox(void);
	/*the center of the bounding box
	position may not be the center of the bounding box, so it have to be calculate*/
	virtual D3DXVECTOR2 getBoundingCenter(void);
	virtual D3DXVECTOR3 getBoundingCenter3D(void);
	//calculate vecNowPos through center, set vecNowPos to let the bounding center get on the position where center at.
	virtual void setBoundingCenter(D3DXVECTOR2 center);
	virtual void setBoundingCenter3D(D3DXVECTOR3 center);

	/*===========================================
	public function
	============================================*/
	void addSpeed(D3DXVECTOR3* speedDir, float speed);
	void calSpeed(void);
	//not just vecFront, vecUp and vecRight will be updated in this function too
	void calFront(void);
	void lockThisTurn(void);
	void unlockThisTurn(void);
	//if isDisappear is true, will setIsDisplay to false and setOverlapLevel to -100(is unrelated to ovl)
	//if isDisappear is false, will setIsDisplay to true and setOverlapLevel to ovl
	void setDisappear(bool isDisappear, int ovl = 10);
	void resetAnimaCount(void);

	/*===========================================
	public geter / seter
	============================================*/
	Model* getModel(void);
	void setModel(Model* model);
	D3DXMATRIX* getMtxWorld(void);
	void setMtxWorld(D3DXMATRIX* mtxWorld);
	D3DXMATRIX* getMtxRotate(void);
	void setMtxRotate(D3DXMATRIX* mtxRotate);
	D3DXVECTOR3* getVecFront(void);
	void setVecFront(D3DXVECTOR3* vecFront);
	D3DXVECTOR3* getVecRight(void);
	void setVecRight(D3DXVECTOR3* vecRight);
	D3DXVECTOR3* getVecUp(void);
	void setVecUp(D3DXVECTOR3* vecUp);
	bool getCanMove(void);
	void setCanMove(bool canMove);
	D3DXVECTOR3* getVecNowPos(void);
	void setVecNowPos(D3DXVECTOR3* vecNowPos);
	D3DXVECTOR3* getVecMoveSpeed(void);
	void setVecMoveSpeed(D3DXVECTOR3* vecMoveSpeed);
	float getMaxSpeed(void);
	void setMaxSpeed(float maxSpeed);
	float getMoveDamping(void);
	void setMoveDamping(float moveDamping);
	int getOverlapLevel(void);
	void setOverlapLevel(int overlapLevel);
	bool getIsDisplay(void);
	void setIsDisplay(bool isDisplay);
	D3DXVECTOR3 *getVecScale(void);
	void setVecScale(D3DXVECTOR3* vecScale);
	D3DXVECTOR3* getVecRotateAxis(void);
	void setVecRotateAxis(D3DXVECTOR3* vecRotateAxis);
	float getRotateSpeed(void);
	void setRotateSpeed(float rotateSpeed);
	float getRotateDamping(void);
	void setRotateDamping(float rotateDamping);
	bool getIsPlayAnima(void);
	void setIsPlayAnima(bool isPlayAnima);
	D3DXVECTOR3* getVecTargetFront(void);
	void setVecTargetFront(D3DXVECTOR3* vecTargetFront);
	bool getMoveThisTurn(void);
	bool getIsDelete(void);
	void setIsDelete(bool isDelete);
private:
	Model* model;

	D3DXMATRIX *mtxWorld;
	D3DXMATRIX *mtxRotate;

	D3DXVECTOR3 *vecFront;   //the up direct of camera(normalize vector)
	D3DXVECTOR3 *vecRight;   //the front direct of camera(normalize vector)
	D3DXVECTOR3 *vecUp;	     //the right direct of camera(normalize vector)

	bool canMove;
	bool moveThisTurn;
	D3DXVECTOR3 *vecNowPos;
	D3DXVECTOR3 *vecMoveSpeed;
	float maxSpeed;
	float moveDamping;

	//if two object's overlap level's sum is gerther then 0, they will touch each other when near
	//if lower the 0, will not
	int overlapLevel;
	bool isDisplay;

	D3DXVECTOR3 *vecScale;

	D3DXVECTOR3 *vecRotateAxis;
	float rotateSpeed;
	float rotateDamping;

	D3DXVECTOR3 boundingBoxMin;
	D3DXVECTOR3 boundingBoxMax;
	
	float animaCounter;
	bool isPlayAnima;

	D3DXVECTOR3 *vecTargetFront;
	static D3DXVECTOR3* zeroDirect;

	bool isDelete;
};

