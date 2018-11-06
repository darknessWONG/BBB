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
	mesh1->setCanMove(true);
	mesh1->setVecNowPos(new D3DXVECTOR3(8, 0, 0));
	gameObjects.push_back(mesh1);
	map->addGameObject(mesh1);

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

	/*for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->dataUpdate();
		gameObjects[i]->calWorldMatrix();
	}*/
	map->updateGameObejcts();
}

void GameManage::draw(void)
{
	light->lightSet(pD3DDevice);
	camera->draw(pD3DDevice);
	
	//for (int i = 0; i < gameObjects.size(); i++)
	//{
	//	gameObjects[i]->draw(pD3DDevice);
	//}
	map->drawGameObjects(pD3DDevice);
}

void GameManage::release(void)
{
}

void GameManage::setPD3DDevice(LPDIRECT3DDEVICE9 pD3DDevice)
{
	this->pD3DDevice = pD3DDevice;
}
