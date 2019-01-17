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
		pEmitter->Draw();
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
	Workbench::initRecipe();

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


	Item *abc = ItemFactory::create_item(-7, -7, 1);
	map->addGameObject(abc);
	items.push_back(abc);

	Item *abc1 = ItemFactory::create_item(-8, 7, 2);
	map->addGameObject(abc1);
	items.push_back(abc1);


	Workbench *wb = new Workbench(3, 3, 6, 6);
	wb->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	wb->setCanMove(false);
	wb->setVecNowPos(new D3DXVECTOR3(-7.5, 0, 0));
	wb->setOverlapLevel(-10);
	wbs.push_back(wb);
	map->addGameObject(wb);

	Model* model10 = new Model("mybody.x");
	model10->loadModel(pD3DDevice);
	Model* head = new Model("face.x");
	head->loadModel(pD3DDevice);
	Parts* par = new Parts();
	par->setModel(model10);

	Parts* par2 = new Parts();
	par2->setModel(model10);
	par2->setOffsetS({ 0.3f, 0.3f, 1.0f });
	par2->setOffsetT({ 2, 1, 0 });
	par2->setOffsetR({ 0, 0, 0 });
	par->addChild(par2);

	Parts* par3 = new Parts();
	par3->setModel(model10);
	par3->setOffsetS({ 0.3f, 0.3f, 1.0f });
	par3->setOffsetT({ -2, 1, 0 });
	par3->setOffsetR({ 0, 0, 0 });
	par->addChild(par3);

	Parts* par5 = new Parts();
	par5->setModel(head);
	par5->setOffsetT({ 0, 5, 0 });
	par5->setOffsetR({ 0, 0, 0 });
	par->addChild(par5);
	
	MyMesh* mm = new MyMesh();
	mm->setParts(par);
	mm->setVecNowPos(new D3DXVECTOR3(10, 0, -10));
	mm->setMaxSpeed(0.3);
	mm->setCanMove(true);
	mm->setOverlapLevel(1);
	others.push_back(mm);
	map->addGameObject(mm);

	AnimationTemplate animateTamp(1, { 0, 0, 0 }, { 90, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 300);
	AnimationTemplate animateTamp1(4, { 0, 0, 0 }, { 0, 90, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 300);
	/*AnimationTemplate animateTamp2(1, { 0, 0, 0 }, { 0, 120, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 300);
	AnimationTemplate animateTamp3(1, { 0, 0, 0 }, { 0, 120, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 300);
	AnimationTemplate animateTamp4(1, { 0, 0, 0 }, { 0, 120, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 300);*/
	vector<AnimationInfoTemplate> list;
	list.push_back({ &animateTamp, 0 });
	list.push_back({ &animateTamp1, 150 });
	AnimationManage::addAnimateTemplate(list);
	am.addAnimation(0, mm);


	pEmitter = new Emitter();

	gs = GameState::GameState_game_state_running;
}

void GameManage::game_state_update(void)
{
	pEmitter->Update();

	//state = GameState_game_state_clean;
	ItemUpdate();
	workbenchUpdate();
	animationUpdate();

	state_read_input(GameState_game_state_clean);
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
	safe_delete<Player>(player);
	
	enemys.clear();
	others.clear();
	items.clear();
	vigliances.clear();
	wbs.clear();
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
	if (Keyboard_IsPress(DIK_RETURN))
	{
		gs = name;
	}
}
