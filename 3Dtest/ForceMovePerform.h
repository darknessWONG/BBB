#pragma once
/*==============================================================================

[ForceMovePerform.h]
Author : darknessWONG
Date   : 2019/02/01
--------------------------------------------------------------------------------
 Different between the ForceMovePerform and the MovePerform is that
 the ForceMovePerform is alter the position of the acvite directly.
 It will not trigger the animation
==============================================================================*/
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

