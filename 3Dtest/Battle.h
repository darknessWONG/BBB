#pragma once
#include <vector>
#include "Chara.h"
#include "meumUI.h"
#include "Player.h"
#include "PerformManage.h"
#include "MapManage.h"

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
	Battle(MapManage *map, PerformManage *pm, MeumUI* commandMeum, Player* movePointer);
	~Battle();

	/*===========================================
	public function
	============================================*/
	void start(void);
	void addCharas(Chara* chara);
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
	void setPerformManager(PerformManage* pm);
	void setMap(MapManage* map);
private:
	//should only change bs by this function, 
	//it will initialize other value it they should be initialize when new bs begin
	void changeBattleState(BattleState newbs);

	/*===========================================
	phase function
	============================================*/
	void standbyPhase(void);
	void commandPhase(void);
	void taragetSelectPhase(void);
	void movePhase(void);
	void placeSelectPhase(void);
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
	void move(void);

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
	void addMovePerform(Chara* act, Chara* target);



	BattleState bs;
	ActionPhaseStatus as;
	ActionPhaseStatus lastAs;
	MovePhaseStatus ms;
	MovePhaseStatus lastMs;

	vector<Chara*> charas;
	vector<Chara*> actionList;
	Player* movePointer = NULL;

	int nowActionChara;

	int lastSelect;
	int nowSelect;

	Action* action;
	D3DXVECTOR2 movePlace;

	PerformManage *pm = NULL;
	MeumUI* commandMeum = NULL;

	float skillEfficiency;
	float defEfficiency;

	MapManage* map;
};

