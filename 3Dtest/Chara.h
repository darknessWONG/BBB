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

	virtual void dataUpdate(void);

	BattleChara* getBattleChara(void);
	void setBattleChara(BattleChara* bc);
	float getWalkSpeed(void);
	void setWalkSpeed(float walkSpeed);

private:
	BattleChara* bc = NULL;

	float walkSpeed;
};

