#pragma once
#include "BattleChara.h"
#include "GameObject.h"

class Chara :
	public GameObject
{
public:
	Chara();
	virtual ~Chara();

	virtual void dataUpdate(void);

	BattleChara* getBattleChara(void);
	void setBattleChara(BattleChara* bc);
	float getWalkSpeed(void);
	void setWalkSpeed(float walkSpeed);

private:
	BattleChara* bc = NULL;

	float walkSpeed;
};

