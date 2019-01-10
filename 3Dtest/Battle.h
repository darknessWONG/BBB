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

	//should only change bs by this function, 
	//it will initialize other value it they should be initialize when new bs begin
	void changeBattleState(BattleState newbs);

	void standbyPhase(void);
	void commandPhase(void);
	void taragetSelectPhase(void);
	void movePhase(void);
	void placeSelectPhase(void);
	void damagePhase(void);
	void mapMovePhase(void);
	void endPhase(void);

	void calActionList(void);

	void selectAction(void);
	void readActionCommand(void);
	void selectTarget(void);
	void readTargetCommand(void);
	void seleteSkill(void);
	void readSkillCommand(void);

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
	ActionPhaseStatus lastAs;

	vector<Chara*> charas;
	vector<Chara*> actionList;

	int nowActionChara;

	int lastSelect;
	int nowSelect;

	Action* action;

	MeumUI* commandMeum;
};

