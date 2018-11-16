#pragma once
#include "Model.h"
#include "BattleChara.h"
class Chara :
	public Model
{
public:
	Chara();
	Chara(string modelPath);
	virtual ~Chara();

	BattleChara* geBattleChara(void);
	void seBattleChara(BattleChara* bc);
	float getWalkSpeed(void);
	void setWalkSpeed(float walkSpeed);

private:
	BattleChara* bc = NULL;

	float walkSpeed;
};

