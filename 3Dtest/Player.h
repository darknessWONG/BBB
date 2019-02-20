#pragma once
/*==============================================================================

[Player.h]
Author : darknessWONG
Date   : 2018/11/23
--------------------------------------------------------------------------------

==============================================================================*/
#include "Chara.h"
class Player :
	public Chara
{
public:
	Player();
	virtual ~Player();

	/*===========================================
	virtual member
	============================================*/
	virtual void dataUpdate(void);

	/*===========================================
	public geter / seter
	============================================*/
	void setIsReadInput(bool isi);
	D3DXVECTOR3* getVecSpeedFront(void);
	void setVecSpeedFront(D3DXVECTOR3* vecspeedFront);
private:
	bool isReadInput;

	float walkAccele;

	D3DXVECTOR3* vecSpeedFront;
};

