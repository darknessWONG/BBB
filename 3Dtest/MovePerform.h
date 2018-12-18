#pragma once
#include "Perform.h"
#include "GameObject.h"
class MovePerform : public Perform
{
public:
	MovePerform();
	virtual ~MovePerform();

	/*===========================================
	virtual member
	============================================*/
	virtual void play(void);
	virtual bool checkEnd(void);

	/*===========================================
	public function
	============================================*/

	/*===========================================
	public geter / seter
	============================================*/
	D3DXVECTOR3 getVecTarget(void);
	void setVecTarget(D3DXVECTOR3 vecTarget);
	D3DXVECTOR3 getVecStart(void);
	void setVecStart(D3DXVECTOR3 vecStart);
	float getMoveSpeed(void);
	void setMoveSpeed(float moveSpeed);
private:
	D3DXVECTOR3 vecTarget;
	D3DXVECTOR3 vecStart;
	float moveSpeed;
};

