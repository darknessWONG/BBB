#pragma once
#include "MovePerform.h"
class ForceMovePerform :
	public MovePerform
{
public:
	ForceMovePerform();
	~ForceMovePerform();

	/*===========================================
	virtual member
	============================================*/
	virtual void play(void);
};

