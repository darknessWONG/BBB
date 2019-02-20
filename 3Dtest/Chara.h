#pragma once
/*==============================================================================

The base of other chara class like player and enemy[Chara.h]
Author : darknessWONG
Date   : 2019/01/15
--------------------------------------------------------------------------------

==============================================================================*/
#include "BattleChara.h"
#include "GameObject.h"

class Chara :
	public GameObject
{
public:
	Chara();
	virtual ~Chara();

	/*===========================================
	virtual member
	============================================*/
	virtual void dataUpdate(void);

	/*===========================================
	public geter/seter
	============================================*/
	BattleChara* getBattleChara(void);
	void setBattleChara(BattleChara* bc);
	float getWalkSpeed(void);
	void setWalkSpeed(float walkSpeed);

private:
	BattleChara* bc = NULL;

	float walkSpeed;
};

