#pragma once
#include "Perform.h"
#include "GameObject.h"
class MovePerform : public Perform
{
public:
	MovePerform();
	~MovePerform();

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
private:
	D3DXVECTOR3 vecTarget;
	float moveSpeed;
};

