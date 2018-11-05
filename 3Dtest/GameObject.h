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
	virtual void positionUpdateX(void);
	virtual void positionUpdateY(void);
	virtual void positionUpdateZ(void);
	virtual void positionUpdate(void);
	virtual void draw(LPDIRECT3DDEVICE9 pD3DDevice) = 0;
	virtual RECT getBoundingRect(void) = 0;

	/*===========================================
	public function
	============================================*/
	void addSpeed(D3DXVECTOR3* speedDir, float speed);

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

	bool canMove;
	D3DXVECTOR3 *vecNowPos;
	D3DXVECTOR3 *vecMoveSpeed;
	float maxSpeed;
	float moveDamping;

	D3DXVECTOR3 *vecRotateAxis;
	float rotateSpeed;
	float rotateDamping;

	static D3DXVECTOR3* zeroDirect;
};

