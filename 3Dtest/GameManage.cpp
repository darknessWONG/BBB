#include "stdafx.h"
#include "GameManage.h"
#include "Model.h"
#include "Player.h"

GameManage::GameManage()
{
}

GameManage::GameManage(LPDIRECT3DDEVICE9 pD3DDevice)
{
	setPD3DDevice(pD3DDevice);
	gs = GameState::GameStateTitleInit;
}


GameManage::~GameManage()
{
}

void GameManage::init(void)
{
	map = new MapManage();

	D3DXVECTOR3* cameraPos = new D3DXVECTOR3(0, 20, -20);
	D3DXVECTOR3* cameraWatchAt = new D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3* cameraUp = new D3DXVECTOR3(0, 1, 0);
	camera = new Camera(cameraPos, cameraWatchAt, cameraUp);



	light = new Light();
	light->init(pD3DDevice);
}

void GameManage::beforeUpdate(void)
{
	map->cleanGameObject();
	int gameObjectsNum = gameObjects.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		map->addGameObject(gameObjects[i]);
	}
}

void GameManage::update(void)
{
	beforeUpdate();
	camera->dataUpdate();
	camera->calWatchAt();
	camera->calWorldMatrix();
	camera->draw(pD3DDevice);

	switch (gs)
	{
	case GameState::GameStateTitleInit:
		titleStateInit();
		break;
	case GameState::GameStateTitleRunning:
		titleStateUpdate();
		break;
	case GameState::GameStateTitleClean:
		titleStateClean();
		break;
	case GameState::GameStateGameInit:
		gameStateInit();
		break;
	case GameState::GameStateGameRunning:
		gameStateUpdate();
		break;
	case GameState::GameStateGameClean:
		gameStateClean();
		break;
	case GameState::GameStateEndInit:
		endStateInit();
		break;
	case GameState::GameStateEndRunning:
		endStateUpdate();
		break;
	case GameState::GameStateEndClean:
		endStateClean();
		break;
	}

	map->updateGameObejcts();
}

void GameManage::draw(void)
{
	light->lightSet(pD3DDevice);
	camera->draw(pD3DDevice);

	if (gs == GameState::GameStateGameRunning)
	{
		map->drawGameObjects(pD3DDevice);
	}
}

void GameManage::release(void)
{
}

void GameManage::titleStateInit(void)
{
	gs = GameState::GameStateTitleRunning;
}

void GameManage::titleStateUpdate(void)
{
	gs = GameState::GameStateTitleClean;
}

void GameManage::titleStateClean(void)
{
	gs = GameState::GameStateGameInit;
}

void GameManage::gameStateInit(void)
{
	Player* mesh = new Player("radio.x");
	mesh->loadModel(pD3DDevice);
	//mesh->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	//mesh->setRotateSpeed(20);
	mesh->setWalkSpeed(0.01);
	mesh->setMaxSpeed(0.3);
	mesh->setCanMove(true);
	mesh->setVecNowPos(new D3DXVECTOR3(0, 0, 0));
	gameObjects.push_back(mesh);
	map->addGameObject(mesh);


	Model* mesh1 = new Model("tree.x");
	mesh1->loadModel(pD3DDevice);
	mesh1->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	//mesh1->setRotateSpeed(20);
	mesh1->setCanMove(false);
	mesh1->setVecNowPos(new D3DXVECTOR3(7.5, 0, 0));
	gameObjects.push_back(mesh1);
	map->addGameObject(mesh1);

	gs = GameState::GameStateGameRunning;
}

void GameManage::gameStateUpdate(void)
{
	checkEnd();
}

void GameManage::gameStateClean(void)
{
	gs = GameState::GameStateEndInit;
}

void GameManage::endStateInit(void)
{
	gs = GameState::GameStateEndRunning;
}

void GameManage::endStateUpdate(void)
{
	gs = GameState::GameStateEndClean;
}

void GameManage::endStateClean(void)
{
	gs = GameState::GameStateTitleInit;
}

void GameManage::checkEnd(void)
{
	//gs = GameState::GameStateGameClean;
}

void GameManage::setPD3DDevice(LPDIRECT3DDEVICE9 pD3DDevice)
{
	this->pD3DDevice = pD3DDevice;
}
