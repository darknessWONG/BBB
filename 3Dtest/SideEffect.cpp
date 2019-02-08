#include "stdafx.h"
#include "SideEffect.h"


SideEffect::SideEffect()
{
}

SideEffect::SideEffect(const SideEffect & sideEffect)
{
	this->name = sideEffect.name;
	this->type = sideEffect.type;
	this->duration = sideEffect.duration;
	this->target = sideEffect.target;
	this->value = sideEffect.value;
	this->describe = sideEffect.describe;
}


SideEffect::~SideEffect()
{
}

string SideEffect::getName(void)
{
	return name;
}

void SideEffect::setName(string name)
{
	this->name = name;
}

SideEffectType SideEffect::getType(void)
{
	return type;
}

void SideEffect::setType(SideEffectType type)
{
	this->type = type;
}

int SideEffect::getDuration(void)
{
	return duration;
}

void SideEffect::setDuration(int duration)
{
	this->duration = duration;
}

EffectTarget SideEffect::getTarget(void)
{
	return target;
}

void SideEffect::setTarget(EffectTarget target)
{
	this->target = target;
}

float SideEffect::getValue(void)
{
	return value;
}

void SideEffect::setValue(float value)
{
	this->value = value;
}

string SideEffect::getDescribe(void)
{
	return describe;
}

void SideEffect::setDescribe(string describe)
{
	this->describe = describe;
}

int SideEffect::turn_pass(void)
{
	return --duration;
}

