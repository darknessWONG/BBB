#pragma once
#include "Chara.h"
#include "stdafx.h"
class Enemy :
	public Chara
{
public:
	Enemy();
	Enemy(string modelPath);
	virtual ~Enemy();

	/*===========================================
	virtual member
	============================================*/
	virtual void dataUpdate(void);

	/*===========================================
	public geter / seter
	============================================*/
	D3DXVECTOR3* getVecPatrolStart(void);
	void setVecPatrolStart(D3DXVECTOR3* vecPatrolStart);
	D3DXVECTOR3* getVecPatrolEnd(void);
	void setVecPatrolEnd(D3DXVECTOR3* vecPatrolEnd);
	D3DXVECTOR3* getVecPatrolTarget(void);
	void setVecPatrolTarget(D3DXVECTOR3* vecPatrolTarget);
	bool getIsTracking(void);
	void setIsTracking(bool isTracking);
	void setIsPatrol(bool isPatrol);
private:
	bool isPatrol;

	D3DXVECTOR3* vecPatrolStart = NULL;
	D3DXVECTOR3* vecPatrolEnd = NULL;
	D3DXVECTOR3* vecPatrolTarget = NULL;

	bool isTracking;
};

