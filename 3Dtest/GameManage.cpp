#include "stdafx.h"
#include "GameManage.h"
#include "Model.h"
#include "Player.h"
#include "Vigilance.h"
#include "Enemy.h"

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

	map->addGameObject(player);

	int gameObjectsNum = enemys.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		map->addGameObject(enemys[i]);
	}
	gameObjectsNum = others.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		map->addGameObject(others[i]);
	}
	gameObjectsNum = vigliances.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		map->addGameObject(vigliances[i]);
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
	player = mesh;
	map->addGameObject(mesh);


	Model* mesh1 = new Model("tree.x");
	mesh1->loadModel(pD3DDevice);
	mesh1->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	//mesh1->setRotateSpeed(20);
	mesh1->setCanMove(false);
	mesh1->setVecNowPos(new D3DXVECTOR3(7.5, 0, 0));
	others.push_back(mesh1);
	map->addGameObject(mesh1);


	Enemy* mesh3 = new Enemy("radio.x");
	mesh3->loadModel(pD3DDevice);
	mesh3->setWalkSpeed(0.01);
	mesh3->setMaxSpeed(0.3);
	mesh3->setCanMove(true);
	mesh3->setVecNowPos(new D3DXVECTOR3(1, 0, 1));
	mesh3->setVecPatrolStart(new D3DXVECTOR3(1, 0, 1));
	mesh3->setVecPatrolEnd(new D3DXVECTOR3(1, 0, 5));
	enemys.push_back(mesh3);
	map->addGameObject(mesh3);

	Vigilance* mesh4 = new Vigilance();
	mesh4->setMaxSpeed(0.3);
	mesh4->setCanMove(true);
	mesh4->setVecNowPos(new D3DXVECTOR3(1, 0, 1));
	mesh4->setBelong(mesh3);
	mesh4->setRadius(7);
	vigliances.push_back(mesh4);
	map->addGameObject(mesh4);

	gs = GameState::GameStateGameRunning;
}

void GameManage::gameStateUpdate(void)
{
	enemyUpdate();
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

void GameManage::enemyUpdate(void)
{
	int viNum = vigliances.size();
	for (int i = 0; i < viNum; i++)
	{
		bool isPor = false;
		if (typeid(Enemy) != typeid(*vigliances[i]->getBelong()))
		{
			continue;
		}
		vector<GameObject*> list = map->calObjectInCycle(vigliances[i]);
		if (list.size() > 0)
		{
			int num = list.size();
			for (int j = 0; j < num; j++)
			{
				if (typeid(Player) == typeid(*list[j]))
				{
					D3DXVECTOR2 listObjCenter = list[j]->getBoundingCenter();
					D3DXVECTOR3 targe = D3DXVECTOR3(listObjCenter.x, 0, listObjCenter.y);
					
					vector<GameObject*> sightList = map->calObjectOnSight(((Enemy*)(vigliances[i]->getBelong())), (Player*)list[j]);
					if (sightList.size() == 0)
					{
						((Enemy*)(vigliances[i]->getBelong()))->setVecPatrolTarget(&targe);
						isPor = true;;
					}
					
				}
			}
		}
		((Enemy*)(vigliances[i]->getBelong()))->setIsTracking(isPor);
	}
}

void GameManage::setPD3DDevice(LPDIRECT3DDEVICE9 pD3DDevice)
{
	this->pD3DDevice = pD3DDevice;
}
