#pragma once
#include "stdafx.h"
class SideEffect
{
public:
	SideEffect();
	SideEffect(const SideEffect& sideEffect);
	~SideEffect();

	string getName(void);
	void seetName(string name);
	SideEffectType getType(void);
	void setType(SideEffectType type);
	int getDuration(void);
	void setDuration(int duration);
	EffectTarget getTarget(void);
	void setTarget(EffectTarget target);
	float getValue(void);
	void setValue(float value);
	string getDescribe(void);
	void setDescribe(string describe);

private:
	string name;
	SideEffectType type;
	int duration;
	EffectTarget target;
	float value;
	string describe;
};

