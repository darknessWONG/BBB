#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Camera.h"
#include "Light.h"
#include "static.h"
#include "MapManage.h"
#include "Emitter.h"

//enum GameState
//{
//	GameStateTitleInit,
//	GameStateTitleRunning,
//	GameStateTitleClean,
//	GameStateGameInit,
//	GameStateGameRunning,
//	GameStateGameClean,
//	GameStateEndInit,
//	GameStateEndRunning,
//	GameStateEndClean,
//	GameStateMax
//};

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

	void setPD3DDevice(LPDIRECT3DDEVICE9 pD3DDevice);
private:
	void state_read_input(GameState name);

	LPDIRECT3DDEVICE9 pD3DDevice = NULL;

	Camera* camera = NULL;
	Light* light = NULL;
	vector<GameObject*> gameObjects;
	Emitter *pEmitter;

	MapManage* map = NULL;

	GameState gs;
};