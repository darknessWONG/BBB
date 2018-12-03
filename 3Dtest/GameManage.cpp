#include "stdafx.h"
#include "GameManage.h"
#include "Model.h"
#include "Player.h"
#include "Vigilance.h"
#include "ItemFactory.h"
#include "Enemy.h"
#include "input.h"
#include "Common.h"


GameManage::GameManage()
{
	gs = GameState::GameState_title_state_init;
}

GameManage::GameManage(LPDIRECT3DDEVICE9 pD3DDevice)
{
	setPD3DDevice(pD3DDevice);
	gs = GameState::GameState_title_state_init;
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
	int gameObjectsNum = others.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		map->addGameObject(others[i]);
	}
	gameObjectsNum = items.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		map->addGameObject(items[i]);
	}
	gameObjectsNum = enemys.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		map->addGameObject(enemys[i]);
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
	case GameState::GameState_title_state_init:
		title_state_init();
		break;
	case GameState::GameState_title_state_running:
		title_state_update();
		break;
	case GameState::GameState_title_state_clean:
		title_state_clean();
		break;
	case GameState::GameState_tutorial_state_init:
		tutorial_state_init();
		break;
	case GameState::GameState_tutorial_state_running:
		tutorial_state_update();
		break;
	case GameState::GameState_tutorial_state_clean:
		tutorial_state_clean();
		break;
	case GameState::GameState_game_state_init:
		game_state_init();
		break;
	case GameState::GameState_game_state_running:
		game_state_update();
		break;
	case GameState::GameState_game_state_clean:
		game_state_clean();
		break;
	case GameState::GameState_result_state_init:
		result_state_init();
		break;
	case GameState::GameState_result_state_running:
		result_state_update();
		break;
	case GameState::GameState_result_state_clean:
		result_state_clean();
		break;
	case GameState::GameState_naming_state_init:
		naming_state_init();
		break;
	case GameState::GameState_naming_state_running:
		naming_state_update();
		break;
	case GameState::GameState_naming_state_clean:
		naming_state_clean();
		break;
	case GameState::GameState_ranking_state_init:
		ranking_state_init();
		break;
	case GameState::GameState_ranking_state_running:
		ranking_state_update();
		break;
	case GameState::GameState_ranking_state_clean:
		ranking_state_clean();
	}

	map->updateGameObejcts();
}

void GameManage::draw(void)
{
	light->lightSet(pD3DDevice);
	camera->draw(pD3DDevice);

	if (gs == GameState::GameState_game_state_running)
	{
		map->drawGameObjects(pD3DDevice);
	}
}

void GameManage::release(void)
{
}

void GameManage::title_state_init(void)
{
	gs = GameState_title_state_running;
}

void GameManage::title_state_update(void)
{
	gs = GameState_title_state_clean;
}

void GameManage::title_state_clean(void)
{
	gs = GameState_tutorial_state_init;
}

void GameManage::tutorial_state_init(void)
{
	gs = GameState_tutorial_state_running;
}

void GameManage::tutorial_state_update(void)
{
	gs = GameState_tutorial_state_clean;
}

void GameManage::tutorial_state_clean(void)
{
	gs = GameState_game_state_init;
}

void GameManage::game_state_init(void)
{
	ItemFactory::setDevice(pD3DDevice);

	Player* mesh = new Player("radio.x");
	mesh->loadModel(pD3DDevice);
	//mesh->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	//mesh->setRotateSpeed(20);
	mesh->setWalkSpeed(0.01);
	mesh->setMaxSpeed(0.3);
	mesh->setCanMove(true);
	mesh->setVecNowPos(new D3DXVECTOR3(0, 0, 0));
	//gameObjects.push_back(mesh);
	player = mesh;
	map->addGameObject(mesh);


	Model* mesh1 = new Model("tree.x");
	mesh1->loadModel(pD3DDevice);
	mesh1->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	//mesh1->setRotateSpeed(20);
	mesh1->setCanMove(false);
	mesh1->setVecNowPos(new D3DXVECTOR3(7.5, 0, 0));
	//gameObjects.push_back(mesh1);
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
	//gameObjects.push_back(mesh3);
	enemys.push_back(mesh3);
	map->addGameObject(mesh3);

	Vigilance* mesh4 = new Vigilance();
	mesh4->setMaxSpeed(0.3);
	mesh4->setCanMove(true);
	mesh4->setVecNowPos(new D3DXVECTOR3(1, 0, 1));
	mesh4->setBelong(mesh3);
	mesh4->setRadius(2);
	mesh4->setRadius(7);
	vigliances.push_back(mesh4);
	//gameObjects.push_back(mesh4);
	map->addGameObject(mesh4);

	Item *abc = ItemFactory::create_item(-7, 7, 1);
	map->addGameObject(abc);
	items.push_back(abc);


	gs = GameState::GameState_game_state_running;
}

void GameManage::game_state_update(void)
{
	//state_read_input(GameState_game_state_clean);
	//state = GameState_game_state_clean;
	ItemUpdate();
}

void GameManage::game_state_clean(void)
{
	//int idx = gameObjects.size();
	//for (int i = 0; i < idx; i++)
	//{
	//	delete gameObjects[i];
	//}
	//gameObjects.clear();
	//map->cleanGameObject();

	map->cleanGameObject();
	int gameObjectsNum = others.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		delete others[i];
	}
	gameObjectsNum = vigliances.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		delete vigliances[i];
	}
	gameObjectsNum = enemys.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		delete enemys[i];
	}
	gameObjectsNum = items.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		delete items[i];
	}
	safe_delete<Player>(player);
	
	enemys.clear();
	others.clear();
	vigliances.clear();
	gs = GameState_result_state_init;
}

void GameManage::result_state_init(void)
{
	gs = GameState_result_state_running;
}

void GameManage::result_state_update(void)
{
	gs = GameState_result_state_clean;
}

void GameManage::result_state_clean(void)
{
	gs = GameState_naming_state_init;
}

void GameManage::naming_state_init(void)
{
	gs = GameState_naming_state_running;
}

void GameManage::naming_state_update(void)
{
	gs = GameState_naming_state_clean;
}

void GameManage::naming_state_clean(void)
{
	gs = GameState_ranking_state_init;
}

void GameManage::ranking_state_init(void)
{
	gs = GameState_ranking_state_running;
}

void GameManage::ranking_state_update(void)
{
	gs = GameState_ranking_state_clean;
}

void GameManage::ranking_state_clean(void)
{
	gs = GameState_title_state_init;
}

void GameManage::checkEnd(void)
{
	//gs = GameState::GameStateGameClean;
}

void GameManage::ItemUpdate(void)
{
	if (player->getFindHoldings())
	{
		int itemsNum = items.size();
		for (int i = 0; i < itemsNum; i++)
		{
			TouchType tt = map->collisionDetection(items[i], player);
			
			if (tt != TouchType::noTouch)
			{
				items[i]->setBelong(player);
				player->setHoldings(items[i]);
				player->setFindHoldings(false);
				break;
			}
			if (player->getFindHoldings())
			{
				break;
			}
		}
	}
}

void GameManage::setPD3DDevice(LPDIRECT3DDEVICE9 pD3DDevice)
{
	this->pD3DDevice = pD3DDevice;
}

void GameManage::state_read_input(GameState name)
{
	if (Keyboard_IsPress(DIK_SPACE))
	{
		gs = name;
	}
}
