#pragma once
/*==============================================================================

The base of other perform[Perform.h]
Author : darknessWONG
Date   : 2018/11/23
--------------------------------------------------------------------------------

==============================================================================*/
#include "GameObject.h"
class Perform
{
public:
	Perform();
	virtual ~Perform();
	/*===========================================
	virtual member
	============================================*/
	virtual void play(void) = 0;
	virtual bool checkEnd(void) = 0;

	/*===========================================
	public function
	============================================*/

	/*===========================================
	public geter / seter
	============================================*/
	GameObject* getActor(void);
	void setActor(GameObject* actor);
private:
	GameObject* actor;
};

