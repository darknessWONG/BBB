#pragma once

/*==============================================================================

Chara infomation use in battle[BattleChara.h]
Author : darknessWONG
Date   : 2019/01/15
--------------------------------------------------------------------------------

==============================================================================*/

#include "BattleSkill.h"
#include "SideEffect.h"
class BattleChara
{
public:
	BattleChara();
	~BattleChara();

	/*===========================================
	virtual member
	============================================*/

	/*===========================================
	public function
	============================================*/
	void addSkill(BattleSkill* skill);

	void addEffect(SideEffect* effect);
	bool checkEffect(SideEffectType type);
	void removeEffect(int index);
	void removeEffect(SideEffect* effect);
	void removeEffect(SideEffectType type);

	//damage can be negative when getting healed
	void takeDamage(int damage);
	void removeOverdueStauts(void);
	void calStatus(void);

	/*===========================================
	public geter / seter
	============================================*/
	string getName(void);
	void setName(string name);
	int getHpMax(void);
	void setHpMax(int hp);
	int getHpNow(void);
	void setHpNow(int hp);
	int getMpMax(void);
	void setMpMax(int mp);
	int getMpNow(void);
	void setMpNow(int mp);
	int getAtk(void);
	void setAtk(int atk);
	int getSpeed(void);
	void setSpeed(int speed);
	int getMovePoint(void);
	void setMovePoint(int movePoint);
	CampType getCamp(void);
	void setCamp(CampType camp);
	vector<BattleSkill*> getSkillList(void);

private:
	string name;

	int hpMax;
	int hpNow;
	int mpMax;
	int mpNow;
	int atk;
	int speed;
	int movePoint;

	CampType camp;

	vector<BattleSkill*> skill;
	vector<SideEffect*> effect;
};
