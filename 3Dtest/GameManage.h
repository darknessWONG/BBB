#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Camera.h"
#include "Light.h"

class GameManage
{
public:
	GameManage();
	GameManage(LPDIRECT3DDEVICE9 pD3DDevice);
	~GameManage();
	
	void init(void);
	void update(void);
	void draw(void);
	void release(void);


	void setPD3DDevice(LPDIRECT3DDEVICE9 pD3DDevice);
private:
	LPDIRECT3DDEVICE9 pD3DDevice = NULL;

	Camera* camera = NULL;
	Light* light = NULL;
	vector<GameObject*> gameObjects;
};

