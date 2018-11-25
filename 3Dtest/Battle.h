#pragma once
#include <vector>
#include "Chara.h"
class Battle
{
public:
	Battle();
	~Battle();

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


	void addCharas(Chara* chara);

private:
	vector<Chara*> charas;
	vector<Chara*> actionList;

	BattleState bs;
	int nowActionPlayer;
};

