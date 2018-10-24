#pragma once
#include <d3dx9.h>

class GameObject
{
public:
	GameObject();
	~GameObject();

	/*===========================================
	virtual member
	============================================*/
	virtual void calWorldMatrix(void);
	virtual void dataUpdate(void);
	virtual void draw(void) = 0;

	/*===========================================
	public function
	============================================*/

	/*===========================================
	public geter / seter
	============================================*/
	D3DXMATRIX* getMtxWorld(void);
	void setMtxWorld(D3DXMATRIX* mtxWorld);
	D3DXVECTOR3* geteVecFront(void);
	void seteVecFront(D3DXVECTOR3* vecFront);
	D3DXVECTOR3* getVecRight(void);
	void setVecRight(D3DXVECTOR3* vecRight);
	D3DXVECTOR3* getVecUp(void);
	void setVecUp(D3DXVECTOR3* vecUp);
	D3DXVECTOR3* getVecNowPos(void);
	void setVecNowPos(D3DXVECTOR3* vecNowPos);
	D3DXVECTOR3* getVecMoveDirect(void);
	void setVecMoveDirect(D3DXVECTOR3* vecMoveDirect);
	float getMoveSpeed(void);
	void setMoveSpeed(float moveSpeed);
	float getMoveDamping(void);
	void setMoveDamping(float moveDamping);
	D3DXVECTOR3* getVecRotateAxis(void);
	void setVecRotateAxis(D3DXVECTOR3* vecRotateAxis);
	float getRotateSpeed(void);
	void setRotateSpeed(float rotateSpeed);
	float getRotateDamping(void);
	void setRotateDamping(float rotateDamping);
private:
	D3DXMATRIX *mtxWorld;

	D3DXVECTOR3 *vecFront;    //the up direct of camera(normalize vector)
	D3DXVECTOR3 *vecRight;    //the front direct of camera(normalize vector)
	D3DXVECTOR3 *vecUp;	     //the right direct of camera(normalize vector)

	D3DXVECTOR3 *vecNowPos;
	D3DXVECTOR3 *vecMoveDirect;
	float moveSpeed;
	float moveDamping;

	D3DXVECTOR3 *vecRotateAxis;
	float rotateSpeed;
	float rotateDamping;
};

