#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Camera.h"
#include "Item.h"
#include "Light.h"
#include "static.h"
#include "MapManage.h"
#include "Workbench.h"
#include "Emitter.h"
#include "GameTitle.h"
#include "GameTutorial.h"
#include "GameResult.h"

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

	// each stage function
	void title_state_init(void);				// title screen
	void title_state_update(void);
	void title_state_clean(void);
	void tutorial_state_init(void);				// tutorial phase
	void tutorial_state_update(void);
	void tutorial_state_clean(void);
	void game_state_init(void);					// game phase
	void game_state_update(void);
	void game_state_clean(void);
	void result_state_init(void);				// show result screen
	void result_state_update(void);
	void result_state_clean(void);
	void naming_state_init(void);				// input name if change ranking
	void naming_state_update(void);
	void naming_state_clean(void);
	void ranking_state_init(void);				// show ranking
	void ranking_state_update(void);
	void ranking_state_clean(void);

	void checkEnd(void);
	void ItemUpdate(void);
	void workbenchUpdate(void);

	void cleanDead(void);

	void setPD3DDevice(LPDIRECT3DDEVICE9 pD3DDevice);
private:
	void state_read_input(GameState name);

	LPDIRECT3DDEVICE9 pD3DDevice = NULL;

	Camera* camera = NULL;
	Light* light = NULL;

	Player *player = NULL;
	vector<Enemy*> enemys;
	vector<Vigilance*> vigliances;
	vector<Item*> items;
	vector<Workbench*> wbs;
	
	vector<GameObject*> others;

	Emitter *pEmitter;
	
	GameTitle *pTitle;
	GameTutorial *pTutorial;
	GameResult *pResult;

	MapManage* map = NULL;

	GameState gs;
};