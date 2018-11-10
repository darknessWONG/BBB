#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Camera.h"
#include "Light.h"
#include "MapManage.h"

enum GameState
{
	GameStateTitleInit,
	GameStateTitleRunning,
	GameStateTitleClean,
	GameStateGameInit,
	GameStateGameRunning,
	GameStateGameClean,
	GameStateEndInit,
	GameStateEndRunning,
	GameStateEndClean,
	GameStateMax
};

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
	void checkEnd(void);

	void setPD3DDevice(LPDIRECT3DDEVICE9 pD3DDevice);
private:
	LPDIRECT3DDEVICE9 pD3DDevice = NULL;

	Camera* camera = NULL;
	Light* light = NULL;
	vector<GameObject*> gameObjects;

	MapManage* map = NULL;

	GameState gs;
};