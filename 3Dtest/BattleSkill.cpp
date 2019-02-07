#include "stdafx.h"
#include "BattleSkill.h"


BattleSkill::BattleSkill()
{
	name = "";
	cost = 0;
	mainTarget = EffectTarget::EffectTargetNoTarget;
	damage = 0;
	EffectTarget damageTarget = EffectTarget::EffectTargetNoTarget;;
	heal = 0;
	EffectTarget healTarget = EffectTarget::EffectTargetNoTarget;;
	sideEffect = NULL;
	skillType = DamageType::physics;
	distance = 0;
	describe = "";
}


BattleSkill::~BattleSkill()
{
}

string BattleSkill::getName(void)
{
	return name;
}

void BattleSkill::setName(string name)
{
	this->name = name;
}

int BattleSkill::getCost(void)
{
	return cost;
}

void BattleSkill::setCost(int cost)
{
	this->cost = cost;
}

EffectTarget BattleSkill::getMainTarget(void)
{
	return mainTarget;
}

void BattleSkill::setMainTarget(EffectTarget target)
{
	this->mainTarget = target;
}

float BattleSkill::getDamage(void)
{
	return damage;
}

void BattleSkill::setDamage(float damage)
{
	this->damage = damage;
}

EffectTarget BattleSkill::getDamageTarget(void)
{
	return damageTarget;
}

void BattleSkill::setDamageTarget(EffectTarget target)
{
	this->damageTarget = target;
}

float BattleSkill::getHeal(void)
{
	return heal;
}

void BattleSkill::setHeal(float heal)
{
	this->heal = heal;
}

EffectTarget BattleSkill::getHealTarget(void)
{
	return healTarget;
}

void BattleSkill::setHealTarget(EffectTarget target)
{
	this->healTarget = target;
}

SideEffect * BattleSkill::getSideEffect(void)
{
	return sideEffect;
}

void BattleSkill::setSideEffect(const SideEffect * sideEffect)
{
	if (sideEffect != NULL)
	{
		safe_delete<SideEffect>(this->sideEffect);
		this->sideEffect = new SideEffect(*sideEffect);
	}
}

DamageType BattleSkill::getSkillType(void)
{
	return skillType;
}

void BattleSkill::setSkillType(DamageType skillType)
{
	this->skillType = skillType;
}

float BattleSkill::getDistance(void)
{
	return distance;
}

void BattleSkill::setDistance(float distance)
{
	this->distance = distance;
}

string BattleSkill::getDescribe(void)
{
	return describe;
}

void BattleSkill::setDescribe(string describe)
{
	this->describe;
}

int BattleSkill::getTextureIndex(void)
{
	return textureIndex;
}

void BattleSkill::setTextureIndex(int textureIndex)
{
	this->textureIndex = textureIndex;
}
