#pragma once
#include <vector>
#include "Chara.h"
#include "meumUI.h"

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
	~Battle();

	/*===========================================
	public function
	============================================*/
	void start(void);

	void standbyPhase(void);
	void commandPhase(void);
	void taragetSelectPhase(void);
	void movePhase(void);
	void placeSelectPhase(void);
	void damagePhase(void);
	void mapMovePhase(void);
	void endPhase(void);

	void calActionList(void);

	void readCommand(void);
	void selectTarget(void);
	void seleteSkill(void);

	//if is dead return true or return false
	bool checkDead(Chara* chara);
	void addCharas(Chara* chara);

	void createActionMeum(void);
	void createSkillMeum(vector<BattleSkill*> list);
	void createTagatMeum(vector<Chara*> list);
	vector<Chara*> calTargetList(Chara* acvite, BattleSkill* skill);
private:
	BattleState bs;
	ActionPhaseStatus as;

	vector<Chara*> charas;
	vector<Chara*> actionList;

	int nowActionChara;

	int lastSelect;
	int nowSelect;

	Action* action;

	MeumUI* commandMeum;
};

