#pragma once
#include "stdafx.h"
#include "SideEffect.h"
#include "Common.h"
#include "Model.h"
class BattleSkill
{
public:
	BattleSkill();
	~BattleSkill();

	string getName(void);
	void setName(string name);
	int getCost(void);
	void setCost(int cost);
	EffectTarget getMainTarget(void);
	void setMainTarget(EffectTarget target);
	float getDamage(void);
	void setDamage(float damage);
	EffectTarget getDamageTarget(void);
	void setDamageTarget(EffectTarget target);
	float getHeal(void);
	void setHeal(float heal);
	EffectTarget getHealTarget(void);
	void setHealTarget(EffectTarget target);
	SideEffect *getSideEffect(void);
	void setSideEffect(const SideEffect* sideEffect);
	DamageType getSkillType(void);
	void setSkillType(DamageType skillType);
	float getDistance(void);
	void setDistance(float distance);
	string getDescribe(void);
	void setDescribe(string describe);
	int getTextureIndex(void);
	void setTextureIndex(int textureIndex);

private:
	string name;
	int cost;
	EffectTarget mainTarget;
	float damage;
	EffectTarget damageTarget;
	float heal;
	EffectTarget healTarget;
	SideEffect *sideEffect;
	DamageType skillType;
	float distance;
	string describe;

	int textureIndex;
};

