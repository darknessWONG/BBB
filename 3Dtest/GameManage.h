#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Camera.h"
#include "Light.h"
#include "Vigilance.h"
#include "MapManage.h"
#include "Player.h"
#include "Enemy.h"
#include "MeumUI.h"
#include "PerformManage.h"
#include "UI.h"
#include "Animation.h"
#include "AnimationSet.h"
#include "AnimationManage.h"
#include "Battle.h"

class GameManage
{
public:
	GameManage();
	GameManage(LPDIRECT3DDEVICE9 pD3DDevice);
	~GameManage();
	
	void init(void);
	void beforeUpdate(void);
	void update(void);
	void draw(void);
	void release(void);

	void titleStateInit(void);
	void titleStateUpdate(void);
	void titleStateClean(void);
	void gameStateInit(void);
	void gameStateUpdate(void);
	void gameStateClean(void);
	void endStateInit(void);
	void endStateUpdate(void);
	void endStateClean(void);
	BOOL checkEnd(void);

	void cameraUpdate(void);
	void enemyUpdate(void);
	void enemyUpdate(Enemy* enemy);
	void animationUpdate(void);
	void othersUpdate(void);

	void battleInit(void);
	//return 1 if is in battle
	//return 0 if is not in battle
	bool checkIsInBattle(void);
	void battleUpdate(void);
	void addCharaToBattle(Battle* battle, Chara* chara);


	void cleanDeletedObject(void);

	void lockUnmoveObject(void);

	void setPD3DDevice(LPDIRECT3DDEVICE9 pD3DDevice);

	void setIsFade(BOOL isFade);
	void fade(void);
private:
	LPDIRECT3DDEVICE9 pD3DDevice = NULL;

	Camera* camera = NULL;
	Light* light = NULL;

	Player *player = NULL;
	vector<Enemy*> enemys;
	Enemy* boss = NULL;
	vector<Vigilance*> vigliances;
	vector<GameObject*> others;
	vector<MeumUI*> uis;
	vector<Model*> models;
	//vector<AnimationSet*> animates;

	Battle* battle = NULL;
	BattleResultType battleResult;

	MapManage* map = NULL;

	PerformManage pm;
	AnimationManage am;

	GameState gs;

	BOOL winStatus;


	MeumUI* fadeFrame;
	BOOL isFade;
	int fadeAlpha;
	bool fadeinFlage;
	bool fadeoutFlage;
};