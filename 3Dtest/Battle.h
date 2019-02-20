#pragma once

/*==============================================================================

Battle manager [Battle.h]
Author : darknessWONG
Date   : 2019/01/15
--------------------------------------------------------------------------------

==============================================================================*/

#include "stdafx.h"
#include "Chara.h"
#include "meumUI.h"
#include "Player.h"
#include "PerformManage.h"
#include "MapManage.h"
#include "NameTap.h"
#include "Billboard.h"

//struct to save what the chara wants to do in this turn
typedef struct action_st
{
	Chara* active = NULL;
	vector<Chara*> passive;
	bool isUseSkill;
	BattleSkill* skill = NULL;
	vector<int> damage;
	vector<int> heal;
}Action;



class Battle
{
public:
	Battle();
	Battle(MapManage *map, PerformManage *pm, MeumUI* commandMeum, MeumUI* textBox, MeumUI* statusBox, Player* movePointer);
	~Battle();

	/*===========================================
	public function
	============================================*/
	void start(void);
	void addCharas(Chara* chara);
	bool checkCharaIsInBattle(Chara* chara);
	/*-------------------
	return value:
	0 if not end
	1 if player win
	-1 if enemy win
	-------------------*/
	BOOL checkEnd(void);

	/*===========================================
	public geter / seter
	============================================*/
	void setMovePointer(Player* pointer);
	void setSkillEfficiency(float se);
	void setDefEfficiency(float de);
	void setCommandMeum(MeumUI* commandMeum);
	void setTextBox(MeumUI* textBox);
	void setStatusBox(MeumUI* statusBox);
	void setPerformManager(PerformManage* pm);
	void setSkillBillboard(Billboard* billboard);
	void setMap(MapManage* map);
	BattleState getBattleState(void);
private:
	/*===========================================
	phase function
	============================================*/
	void beginPhase(void);
	void standbyPhase(void);
	void commandPhase(void);
	void movePhase(void);
	void damagePhase(void);
	void mapMovePhase(void);
	void endPhase(void);

	/*===========================================
	command phase
	============================================*/
	void selectAction(void);
	void readActionCommand(void);
	void selectTarget(void);
	void readTargetCommand(void);
	void seleteSkill(void);
	void readSkillCommand(void);

	/*===========================================
	move phase
	============================================*/
	void plaseSelect(void);
	void resetMovePointer(D3DXVECTOR2 center);
	void readMovePlace(void);

	/*===========================================
	end phase
	============================================*/
	void calActionList(void);
	//if is dead return true or return false
	bool checkDead(Chara* chara);

	/*===========================================
	UI
	============================================*/
	void createActionMeum(void);
	void createSkillMeum(vector<BattleSkill*> list);
	void createTagatMeum(vector<Chara*> list);
	vector<Chara*> calTargetList(Chara* acvite, BattleSkill* skill);

	/*===========================================
	damage phase
	============================================*/
	/*-------------------------
	calDamageVal
	Describe: calculate the damage of attack
	Return value: list of damage
	Parameter:
	active: active of this attack
	passive: list of passive
	isUseSkill: ture if use skill, false if normal attack
	skill: pointer of the skill which is using, NULL if isUseSkill is false
	--------------------------*/
	vector<int> calDamageList(Chara* active, vector<Chara*>passive, bool isUseSkill, BattleSkill* skill);
	int calDamageSingle(BattleChara* active, BattleChara* passive, bool isUseSkill, BattleSkill* skill);
	int calDamageVal(int atk, int def, int skillDamage);
	//vector<int> calHealVal(void);
	void takeDamage(void);

	/*===========================================
	tool function
	============================================*/
	//should only change bs by this function, 
	//it will initialize other value it they should be initialize when new bs begin
	void changeBattleState(BattleState newbs);
	void createTextBox(void);
	void createStatusBox(void);
	/*if flag is 0, it will add a normal move perform
	if flag is 1, it will add a force move perform*/
	void addMovePerform(Chara* act, Chara* target, int flag);
	void addSkillPerform(GameObject* act, D3DXVECTOR3 start, D3DXVECTOR3 target);
	void displayMessage(string str);
	void tabDeadEnemy(void);
	void calStatusMessage(void);
	void createSkillModel(int textureIndex, D3DXVECTOR3 position);

	/*===========================================
	private values
	============================================*/
	BattleState bs;
	BattleState lastBs;
	ActionPhaseStatus as;
	ActionPhaseStatus lastAs;

	vector<Chara*> charas;
	vector<Chara*> actionList;
	Player* movePointer = NULL;
	D3DXVECTOR2 primitivePosition;

	int nowActionChara;

	int lastSelect;
	int nowSelect;

	int mapMoveStartFrame;
	Action* action;
	D3DXVECTOR2 movePlace;

	PerformManage *pm = NULL;
	MeumUI* commandMeum = NULL;
	MeumUI* textBox = NULL;
	MeumUI* statusBox = NULL;

	float skillEfficiency;
	float defEfficiency;

	Billboard* skillBillboard;

	MapManage* map;
};

