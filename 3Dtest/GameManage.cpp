#include "stdafx.h"
#include "GameManage.h"
#include "Model.h"
#include "Player.h"
#include "Vigilance.h"
#include "ItemFactory.h"
#include "Enemy.h"
#include "input.h"
#include "Common.h"
#include "Workbench.h"
#include "Emitter.h"
#include "font.h"
#include "texture.h"
#include "Parts.h"
#include "MyMesh.h"
#include "factoryModel.h"
#include "Animation.h"
#include "AnimationSet.h"


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
	Font_Finalize();
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

	Font_Initialize();
}

void GameManage::beforeUpdate(void)
{
	map->cleanGameObject();
	cleanDead();
	if (player != NULL)
	{
		map->addGameObject(player);
	}

	int gameObjectsNum = items.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		map->addGameObject(items[i]);
	}
	gameObjectsNum = wbs.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		map->addGameObject(wbs[i]);
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
	gameObjectsNum = factorys.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		map->addGameObject(factorys[i]);
	}
	gameObjectsNum = handOutbox.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		map->addGameObject(handOutbox[i]);
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

	if (gs == GameState::GameState_title_state_running)
	{
		pTitle->Draw();
	}

	if (gs == GameState::GameState_tutorial_state_running)
	{
		pTutorial->Draw();
	}

	if (gs == GameState::GameState_game_state_running)
	{
		int gameObjectsNum = others.size();
		for (int i = 0; i < gameObjectsNum; i++)
		{
			map->addGameObject(others[i]);
		}
		map->drawGameObjects(pD3DDevice);
		//pEmitter->Draw();
	}

	if (gs == GameState::GameState_result_state_running)
	{
		pResult->Draw();
	}

}

void GameManage::release(void)
{
}

void GameManage::title_state_init(void)
{
	pTitle = new GameTitle();

	gs = GameState_title_state_running;
}

void GameManage::title_state_update(void)
{
	pTitle->Update();

	if (pTitle->isEnd()) {
		gs = GameState_title_state_clean;
	}
}

void GameManage::title_state_clean(void)
{
	delete pTitle;

	gs = GameState_tutorial_state_init;
}

void GameManage::tutorial_state_init(void)
{
	pTutorial = new GameTutorial();

	gs = GameState_tutorial_state_running;
}

void GameManage::tutorial_state_update(void)
{
	pTutorial->Update();

	if (pTutorial->isEnd()) {
		gs = GameState_tutorial_state_clean;
	}

}

void GameManage::tutorial_state_clean(void)
{
	delete pTutorial;

	gs = GameState_game_state_init;
}

void GameManage::game_state_init(void)
{
	ItemFactory::setDevice(pD3DDevice);
	Workbench::initRecipe();


	Player* mesh = new Player("hew_char.blend.x");
	//Player* mesh = new Player("player.blend.x");
	mesh->loadModel(pD3DDevice);
	mesh->setWalkSpeed(0.01);
	mesh->setMaxSpeed(0.3);
	mesh->setCanMove(true);
	mesh->setVecNowPos(new D3DXVECTOR3(0, 0, 0));
	player = mesh;
	map->addGameObject(mesh);

	factoryModel* fm = new factoryModel("radio.x");
	fm->loadModel(pD3DDevice);
	fm->setItemType(ResourceM::RESOURCEM_WOOD);
	fm->setCanMove(false);
	fm->setVecNowPos(new D3DXVECTOR3(3, 0, 3));
	factorys.push_back(fm);
	map->addGameObject(fm);

	factoryModel* fm1 = new factoryModel("radio.x");
	fm1->loadModel(pD3DDevice);
	fm1->setItemType(ResourceM::RESOURCEM_IRON);
	fm1->setCanMove(false);
	fm1->setVecNowPos(new D3DXVECTOR3(3, 0, 0));
	factorys.push_back(fm1);
	map->addGameObject(fm1);


	factoryModel* fm2 = new factoryModel("radio.x");
	fm2->loadModel(pD3DDevice);
	fm2->setItemType(ResourceM::RESOURCEM_BRICK);
	fm2->setCanMove(false);
	fm2->setVecNowPos(new D3DXVECTOR3(3, 0, 0));
	factorys.push_back(fm2);
	map->addGameObject(fm2);

	Model* box = new Model("face.x");
	box->loadModel(pD3DDevice);
	box->setCanMove(false);
	box->setOverlapLevel(-10);
	box->setVecNowPos(new D3DXVECTOR3(5, 0, 5));
	handOutbox.push_back(box);
	map->addGameObject(box);

	Model* wall = new Model("asset\\hew_models\\hew_wall.x");
	wall->loadModel(pD3DDevice);
	wall->setCanMove(false);
	wall->setOverlapLevel(-10);
	wall->setVecNowPos(new D3DXVECTOR3(-10, 0, 10));
	wall->setVecScale(new D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall);
	map->addGameObject(wall);


	Model* wall1 = new Model("asset\\hew_models\\hew_wall.x");
	wall1->loadModel(pD3DDevice);
	wall1->setCanMove(false);
	wall1->setOverlapLevel(-10);
	wall1->setVecNowPos(new D3DXVECTOR3(-3, 0, 10));
	wall1->setVecScale(new D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall1);
	map->addGameObject(wall1);

	Model* wall2 = new Model("asset\\hew_models\\hew_wall.x");
	wall2->loadModel(pD3DDevice);
	wall2->setCanMove(false);
	wall2->setOverlapLevel(-10);
	wall2->setVecNowPos(new D3DXVECTOR3(4, 0, 10));
	wall2->setVecScale(new D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall2);
	map->addGameObject(wall2);

	Model* wall3 = new Model("asset\\hew_models\\hew_wall.x");
	wall3->loadModel(pD3DDevice);
	wall3->setCanMove(false);
	wall3->setOverlapLevel(-10);
	wall3->setVecNowPos(new D3DXVECTOR3(11, 0, 10));
	wall3->setVecScale(new D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall3);
	map->addGameObject(wall3);

	Model* wall4 = new Model("asset\\hew_models\\hew_wall.x");
	wall4->loadModel(pD3DDevice);
	wall4->setCanMove(false);
	wall4->setOverlapLevel(-10);
	wall4->setVecNowPos(new D3DXVECTOR3(-17, 0, 10));
	wall4->setVecScale(new D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall4);
	map->addGameObject(wall4);

	Model* wall5 = new Model("asset\\hew_models\\hew_wall.x");
	wall5->loadModel(pD3DDevice);
	wall5->setCanMove(false);
	wall5->setOverlapLevel(-10);
	wall5->setVecNowPos(new D3DXVECTOR3(-17, 0, 7));
	wall5->setVecScale(new D3DXVECTOR3(1, 0.5, 0.5));
	wall5->setVecRotation(new D3DXVECTOR3(0, 90, 0));
	others.push_back(wall5);
	map->addGameObject(wall5);

	Model* wall6 = new Model("asset\\hew_models\\hew_wall.x");
	wall6->loadModel(pD3DDevice);
	wall6->setCanMove(false);
	wall6->setOverlapLevel(-10);
	wall6->setVecNowPos(new D3DXVECTOR3(-17, 0, 0));
	wall6->setVecScale(new D3DXVECTOR3(1, 0.5, 0.5));
	wall6->setVecRotation(new D3DXVECTOR3(0, 90, 0));
	others.push_back(wall6);
	map->addGameObject(wall6);

	Model* wall7 = new Model("asset\\hew_models\\hew_wall.x");
	wall7->loadModel(pD3DDevice);
	wall7->setCanMove(false);
	wall7->setOverlapLevel(-10);
	wall7->setVecNowPos(new D3DXVECTOR3(-17, 0, -7));
	wall7->setVecScale(new D3DXVECTOR3(1, 0.5, 0.5));
	wall7->setVecRotation(new D3DXVECTOR3(0, 90, 0));
	others.push_back(wall7);
	map->addGameObject(wall7);

	Model* wall10 = new Model("asset\\hew_models\\hew_wall.x");
	wall10->loadModel(pD3DDevice);
	wall10->setCanMove(false);
	wall10->setOverlapLevel(-10);
	wall10->setVecNowPos(new D3DXVECTOR3(-10, 0, -10));
	wall10->setVecScale(new D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall10);
	map->addGameObject(wall10);

	Model* wall11 = new Model("asset\\hew_models\\hew_wall.x");
	wall11->loadModel(pD3DDevice);
	wall11->setCanMove(false);
	wall11->setOverlapLevel(-10);
	wall11->setVecNowPos(new D3DXVECTOR3(-3, 0, -10));
	wall11->setVecScale(new D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall11);
	map->addGameObject(wall11);

	Model* wall12 = new Model("asset\\hew_models\\hew_wall.x");
	wall12->loadModel(pD3DDevice);
	wall12->setCanMove(false);
	wall12->setOverlapLevel(-10);
	wall12->setVecNowPos(new D3DXVECTOR3(4, 0, -10));
	wall12->setVecScale(new D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall12);
	map->addGameObject(wall12);

	Model* wall13 = new Model("asset\\hew_models\\hew_wall.x");
	wall13->loadModel(pD3DDevice);
	wall13->setCanMove(false);
	wall13->setOverlapLevel(-10);
	wall13->setVecNowPos(new D3DXVECTOR3(11, 0, -10));
	wall13->setVecScale(new D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall13);
	map->addGameObject(wall13);

	Model* wall14 = new Model("asset\\hew_models\\hew_wall.x");
	wall14->loadModel(pD3DDevice);
	wall14->setCanMove(false);
	wall14->setOverlapLevel(-10);
	wall14->setVecNowPos(new D3DXVECTOR3(-17, 0, -10));
	wall14->setVecScale(new D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall14);
	map->addGameObject(wall14);

	Workbench *wb = new Workbench(3, 3, 6, 6);
	wb->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	wb->setCanMove(false);
	wb->setVecNowPos(new D3DXVECTOR3(-7.5, 0, 0));
	wb->setOverlapLevel(-10);
	wbs.push_back(wb);
	map->addGameObject(wb);



	//pEmitter = new Emitter();

	gs = GameState::GameState_game_state_running;
}

void GameManage::game_state_update(void)
{
	//pEmitter->Update();

	ItemUpdate();
	workbenchUpdate();
	animationUpdate();
	handOutBoxUpdate();
	factoryUpdate();

	state_read_input(GameState::GameState_game_state_clean);
}

void GameManage::game_state_clean(void)
{
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
	gameObjectsNum = wbs.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		delete wbs[i];
	}
	gameObjectsNum = factorys.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		delete factorys[i];
	}
	gameObjectsNum = handOutbox.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		delete handOutbox[i];
	}
	//safe_delete<Player>(player);
	delete player;
	player = NULL;

	enemys.clear();
	others.clear();
	items.clear();
	vigliances.clear();
	wbs.clear();
	factorys.clear();
	handOutbox.clear();
	gs = GameState_result_state_init;
}

void GameManage::result_state_init(void)
{
	pResult = new GameResult();

	gs = GameState_result_state_running;
}

void GameManage::result_state_update(void)
{

	pResult->Update();

	if (pResult->isEnd()) {
		gs = GameState_result_state_clean;
	}
}

void GameManage::result_state_clean(void)
{
	delete pResult;
	delete pEmitter;

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
			if (!player->getFindHoldings())
			{
				break;
			}
		}
	}
}

void GameManage::workbenchUpdate(void)
{
	int wbNum = wbs.size();
	int itemNum = items.size();
	for (int i = 0; i < wbNum; i++)
	{
		wbs[i]->releaseItems();
		//D3DXVECTOR2 wbCenter = wbs[i]->getBoundingCenter();
		//float width = wbs[i]->getWidth();
		//float length = wbs[i]->getLength();
		RECTF wbRect = wbs[i]->getBoundingRect();
		for (int j = 0; j < itemNum; j++)
		{
			if (items[j]->getIsDestory() || items[j]->getBelong() != NULL)
			{
				continue;
			}
			TouchType type = map->collisionDetection(wbs[i], items[j]);
			if (type == TouchType::cover)
			{
				D3DXVECTOR2 itemCenter = items[j]->getBoundingCenter();
				if (Physics::pointInRect(itemCenter, wbRect))
				{
					wbs[i]->addItem(items[j]);
				}
			}
		}
		wbs[i]->setItemsPosition();
	}
}

void GameManage::animationUpdate(void)
{
	am.play();
	am.cleanEndAnimation();
}

void GameManage::factoryUpdate(void)
{
	int factorysNum = factorys.size();
	for (int i = 0; i < factorysNum; i++)
	{
		vector<NearInfo> list = map->calNearObject(factorys[i], 2);

		int listNum = list.size();
		for (int j = 0; j < listNum; j++)
		{
			if (list[j].obj == player && player->getFindHoldings())
			{
				D3DXVECTOR2 pos = player->getBoundingCenter();
				Item* item = factorys[i]->createItem(pos.x, pos.y);
				map->addGameObject(item);
				items.push_back(item);
			}
		}
	}
}
void GameManage::handOutBoxUpdate(void)
{
	int handOutboxNum = handOutbox.size();
	for (int i = 0; i < handOutboxNum; i++)
	{
		vector<TouchStatus> list = map->collisionDetection(handOutbox[i]);
		int listNum = list.size();
		for (int i = 0; i < listNum; i++)
		{
			if (typeid(*list[i].obj) == typeid(Item) && list[i].touchType == TouchType::cover
				&& ((Item*)list[i].obj)->getBelong() == NULL)
			{
				list[i].obj->setIsDisplay(false);
				list[i].obj->setIsDelete(true);
				//pEmitter->Submit(((Item*)list[i].obj)->getStatusNow());
			}
		}
	}
}
void GameManage::cleanDead(void)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i]->getIsDestory())
		{
			Item* tmp = items[i];
			for (vector<Item*>::iterator it = items.begin(); it != items.end(); it++)
			{
				if (*it == items[i])
				{
					items.erase(it);
					i = 0;
					break;
				}
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
	if (Keyboard_IsTrigger(DIK_RETURN))
	{
		gs = name;
	}
}
