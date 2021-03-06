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
#include "factoryModel.h"
#include "HandoutBox.h"
#include "gamepad.h"
#include "sound.h"


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
	ItemFactory::Uninit();

	int modelNum = models.size();
	for (int i = 0; i < modelNum; i++)
	{
		safe_delete<Model>(models[i]);
	}
	models.clear();
}

void GameManage::init(void)
{
	map = new MapManage();
	bgm = -1;
	ItemFactory::setDevice(pD3DDevice);
	ItemFactory::Init();

	D3DXVECTOR3* cameraPos = new D3DXVECTOR3(0, 20, -20);
	D3DXVECTOR3* cameraWatchAt = new D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3* cameraUp = new D3DXVECTOR3(0, 1, 0);
	camera = new Camera(cameraPos, cameraWatchAt, cameraUp);

	light = new Light();
	light->init(pD3DDevice);

	Model* playerMesh = new Model("hew_char.blend.x");
	playerMesh->setIsWithAnimation(true);
	playerMesh->loadModel(pD3DDevice);
	models.push_back(playerMesh);
	// box
	Model* radioMesh = new Model("radio.x");
	radioMesh->setIsWithAnimation(false);
	radioMesh->loadModel(pD3DDevice);
	models.push_back(radioMesh);
	// bin
	Model* faceMesh = new Model("radio.x");
	faceMesh->setIsWithAnimation(false);
	faceMesh->loadModel(pD3DDevice);
	models.push_back(faceMesh);
	Model* wallMesh = new Model("asset\\hew_models\\hew_wall.x");
	wallMesh->setIsWithAnimation(false);
	wallMesh->loadModel(pD3DDevice);
	models.push_back(wallMesh);
	Model* ironBoxMesh = new Model("asset\\hew_models\\hew_box_iron.x");
	ironBoxMesh->setIsWithAnimation(true);
	ironBoxMesh->loadModel(pD3DDevice);
	models.push_back(ironBoxMesh);
	Model* woodBoxMesh = new Model("asset\\hew_models\\hew_box_wood.x");
	woodBoxMesh->setIsWithAnimation(true);
	woodBoxMesh->loadModel(pD3DDevice);
	models.push_back(woodBoxMesh);
	Model* rockBoxMesh = new Model("asset\\hew_models\\hew_box_rock.x");
	rockBoxMesh->setIsWithAnimation(true);
	rockBoxMesh->loadModel(pD3DDevice);
	models.push_back(rockBoxMesh);
	Model* handoutBoxMesh = new Model("asset\\hew_models\\hew_handout_box.x");
	handoutBoxMesh->setIsWithAnimation(true);
	handoutBoxMesh->loadModel(pD3DDevice);
	models.push_back(handoutBoxMesh);
	Model* longCubeMesh = new Model("asset\\hew_models\\long cube.x");
	longCubeMesh->setIsWithAnimation(false);
	longCubeMesh->loadModel(pD3DDevice);
	models.push_back(longCubeMesh);

	Gamepad_Initialize();

	Font_Initialize();
	totalScore = 0;
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
	gameObjectsNum = others.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		map->addGameObject(others[i]);
	}
}

void GameManage::update(void)
{
	beforeUpdate();
	camera->dataUpdate();
	camera->calWatchAt();
	camera->calWorldMatrix();
	camera->draw(pD3DDevice);
	Gamepad_Update();

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
		map->drawGameObjects(pD3DDevice);
		pMeshfield->Draw(pD3DDevice);
		pEmitter->Draw();
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

	if (bgm == SOUND_LABEL_MUSIC_GAME) {
		StopSound(SOUND_LABEL_MUSIC_GAME);
		bgm = -1;
	}

	if (bgm != SOUND_LABEL_MUSIC_TITLE) {
		PlaySound(SOUND_LABEL_MUSIC_TITLE);
		bgm = SOUND_LABEL_MUSIC_TITLE;
	}

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
	PlaySound(SOUND_LABEL_SE_PASS);

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
	PlaySound(SOUND_LABEL_SE_PASS);

	delete pTutorial;

	gs = GameState_game_state_init;
}

void GameManage::game_state_init(void)
{
	totalScore = 0;
	Workbench::initRecipe();

	if (bgm == SOUND_LABEL_MUSIC_TITLE) {
		StopSound(SOUND_LABEL_MUSIC_TITLE);
		bgm = -1;
	}

	if (bgm != SOUND_LABEL_MUSIC_GAME) {
		PlaySound(SOUND_LABEL_MUSIC_GAME);
		bgm = SOUND_LABEL_MUSIC_GAME;
	}

	Player* mesh = new Player();
	mesh->setModel(models[0]);
	mesh->setWalkSpeed(0.01);
	mesh->setMaxSpeed(0.3);
	mesh->setCanMove(true);
	mesh->setVecNowPos(&D3DXVECTOR3(0, 0, 0));
	player = mesh;
	map->addGameObject(mesh);

	factoryModel* fm = new factoryModel();
	fm->setModel(models[5]);
	fm->setItemType(ResourceM::RESOURCEM_WOOD);
	fm->setCanMove(false);
	fm->setVecNowPos(&D3DXVECTOR3(6, 0, 0));
	factorys.push_back(fm);
	map->addGameObject(fm);

	factoryModel* fm1 = new factoryModel();
	fm1->setModel(models[4]);
	fm1->setItemType(ResourceM::RESOURCEM_IRON);
	fm1->setIsPlayAnima(false);
	fm1->setCanMove(false);
	fm1->setVecNowPos(&D3DXVECTOR3(-9, 0, 6));
	factorys.push_back(fm1);
	map->addGameObject(fm1);

	factoryModel* fm2 = new factoryModel();
	fm2->setModel(models[6]);
	fm2->setItemType(ResourceM::RESOURCEM_BRICK);
	fm2->setCanMove(false);
	fm2->setVecNowPos(&D3DXVECTOR3(0, 0, -6));
	factorys.push_back(fm2);
	map->addGameObject(fm2);

	GameObject* box = new GameObject();
	box->setModel(models[7]);
	box->setIsPlayAnima(false);
	box->setCanMove(false);
	box->setOverlapLevel(-10);
	box->setVecNowPos(&D3DXVECTOR3(3, 0, 0));
	handOutbox.push_back(box);
	map->addGameObject(box);

	GameObject* wall = new GameObject();
	wall->setModel(models[3]);
	wall->setCanMove(false);
	wall->setOverlapLevel(1);
	wall->setVecNowPos(&D3DXVECTOR3(-10, 0, 10));
	wall->setVecScale(&D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall);
	map->addGameObject(wall);


	GameObject* wall1 = new GameObject();
	wall1->setModel(models[3]);
	wall1->setCanMove(false);
	wall1->setOverlapLevel(1);
	wall1->setVecNowPos(&D3DXVECTOR3(-3, 0, 10));
	wall1->setVecScale(&D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall1);
	map->addGameObject(wall1);

	GameObject* wall2 = new GameObject();
	wall2->setModel(models[3]);
	wall2->setCanMove(false);
	wall2->setOverlapLevel(1);
	wall2->setVecNowPos(&D3DXVECTOR3(4, 0, 10));
	wall2->setVecScale(&D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall2);
	map->addGameObject(wall2);

	GameObject* wall3 = new GameObject();
	wall3->setModel(models[3]);
	wall3->setCanMove(false);
	wall3->setOverlapLevel(1);
	wall3->setVecNowPos(&D3DXVECTOR3(11, 0, 10));
	wall3->setVecScale(&D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall3);
	map->addGameObject(wall3);

	GameObject* wall4 = new GameObject();
	wall4->setModel(models[3]);
	wall4->setCanMove(false);
	wall4->setOverlapLevel(1);
	wall4->setVecNowPos(&D3DXVECTOR3(-17, 0, 10));
	wall4->setVecScale(&D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall4);
	map->addGameObject(wall4);

	GameObject* noWall = new GameObject();
	noWall->setModel(models[8]);
	noWall->setCanMove(false);
	noWall->setOverlapLevel(1);
	noWall->setIsDisplay(false);
	noWall->setVecNowPos(&D3DXVECTOR3(-17, 0, 0));
	noWall->setVecScale(&D3DXVECTOR3(1, 1, 1));
	others.push_back(noWall);
	map->addGameObject(noWall);

	GameObject* wall5 = new GameObject();
	wall5->setModel(models[3]);
	wall5->setCanMove(false);
	wall5->setOverlapLevel(-10);
	wall5->setVecNowPos(&D3DXVECTOR3(-17, 0, 7));
	wall5->setVecScale(&D3DXVECTOR3(1, 0.5, 0.5));
	wall5->setVecFront(new D3DXVECTOR3(1, 0, 0));
	others.push_back(wall5);
	map->addGameObject(wall5);

	GameObject* wall6 = new GameObject();
	wall6->setModel(models[3]);
	wall6->setCanMove(false);
	wall6->setOverlapLevel(-10);
	wall6->setVecNowPos(&D3DXVECTOR3(-17, 0, 0));
	wall6->setVecScale(&D3DXVECTOR3(1, 0.5, 0.5));
	wall6->setVecFront(new D3DXVECTOR3(1, 0, 0));
	others.push_back(wall6);
	map->addGameObject(wall6);

	GameObject* wall7 = new GameObject();
	wall7->setModel(models[3]);
	wall7->setCanMove(false);
	wall7->setOverlapLevel(-10);
	wall7->setVecNowPos(&D3DXVECTOR3(-17, 0, -7));
	wall7->setVecScale(&D3DXVECTOR3(1, 0.5, 0.5));
	wall7->setVecFront(new D3DXVECTOR3(1, 0, 0));
	others.push_back(wall7);
	map->addGameObject(wall7);

	GameObject* nowall2 = new GameObject();
	nowall2->setModel(models[8]);
	nowall2->setCanMove(false);
	nowall2->setOverlapLevel(1);
	nowall2->setIsDisplay(false);
	nowall2->setVecNowPos(&D3DXVECTOR3(17, 0, 0));
	nowall2->setVecScale(&D3DXVECTOR3(1, 1, 1));
	others.push_back(nowall2);
	map->addGameObject(nowall2);

	GameObject* wall65 = new GameObject();
	wall65->setModel(models[3]);
	wall65->setCanMove(false);
	wall65->setOverlapLevel(-10);
	wall65->setVecNowPos(&D3DXVECTOR3(17, 0, 7));
	wall65->setVecScale(&D3DXVECTOR3(1, 0.5, 0.5));
	wall65->setVecFront(new D3DXVECTOR3(1, 0, 0));
	others.push_back(wall65);
	map->addGameObject(wall65);

	GameObject* wall66 = new GameObject();
	wall66->setModel(models[3]);
	wall66->setCanMove(false);
	wall66->setOverlapLevel(-10);
	wall66->setVecNowPos(&D3DXVECTOR3(17, 0, 0));
	wall66->setVecScale(&D3DXVECTOR3(1, 0.5, 0.5));
	wall66->setVecFront(new D3DXVECTOR3(1, 0, 0));
	others.push_back(wall66);
	map->addGameObject(wall66);

	GameObject* wall67 = new GameObject();
	wall67->setModel(models[3]);
	wall67->setCanMove(false);
	wall67->setOverlapLevel(-10);
	wall67->setVecNowPos(&D3DXVECTOR3(17, 0, -7));
	wall67->setVecScale(&D3DXVECTOR3(1, 0.5, 0.5));
	wall67->setVecFront(new D3DXVECTOR3(1, 0, 0));
	others.push_back(wall67);
	map->addGameObject(wall67);

	GameObject* wall10 = new GameObject();
	wall10->setModel(models[3]);;
	wall10->setCanMove(false);
	wall10->setOverlapLevel(1);
	wall10->setVecNowPos(&D3DXVECTOR3(-10, 0, -10));
	wall10->setVecScale(&D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall10);
	map->addGameObject(wall10);

	GameObject* wall11 = new GameObject();
	wall11->setModel(models[3]);;
	wall11->setCanMove(false);
	wall11->setOverlapLevel(1);
	wall11->setVecNowPos(&D3DXVECTOR3(-3, 0, -10));
	wall11->setVecScale(&D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall11);
	map->addGameObject(wall11);

	GameObject* wall12 = new GameObject();
	wall12->setModel(models[3]);
	wall12->setCanMove(false);
	wall12->setOverlapLevel(1);
	wall12->setVecNowPos(&D3DXVECTOR3(4, 0, -10));
	wall12->setVecScale(&D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall12);
	map->addGameObject(wall12);

	GameObject* wall13 = new GameObject();
	wall13->setModel(models[3]);
	wall13->setCanMove(false);
	wall13->setOverlapLevel(1);
	wall13->setVecNowPos(&D3DXVECTOR3(11, 0, -10));
	wall13->setVecScale(&D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall13);
	map->addGameObject(wall13);

	GameObject* wall14 = new GameObject();
	wall14->setModel(models[3]);
	wall14->setCanMove(false);
	wall14->setOverlapLevel(1);
	wall14->setVecNowPos(&D3DXVECTOR3(-17, 0, -10));
	wall14->setVecScale(&D3DXVECTOR3(1, 0.5, 0.5));
	others.push_back(wall14);
	map->addGameObject(wall14);

	Workbench *wb = new Workbench(3, 3, 6, 6);
	wb->setVecRotateAxis(&D3DXVECTOR3(0, 1, 0));
	wb->setCanMove(false);
	wb->setVecNowPos(&D3DXVECTOR3(-7.5, 0, 0));
	wb->setOverlapLevel(-10);
	wbs.push_back(wb);
	map->addGameObject(wb);

	pMeshfield = new Meshfield();
	pMeshfield->Initialize(50.0f, 1, 1, TEX_GROUND, pD3DDevice);

	pEmitter = new Emitter();

	gs = GameState::GameState_game_state_running;
}

void GameManage::game_state_update(void)
{
	pEmitter->Update();

	ItemUpdate();
	workbenchUpdate();
	handOutBoxUpdate();
	factoryUpdate();

	state_read_input(GameState::GameState_game_state_clean);

	if (pEmitter->isEnd())
		gs = GameState::GameState_game_state_clean;
}

void GameManage::game_state_clean(void)
{
	totalScore = pEmitter->getScore();
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
	safe_delete<Player>(player);
	delete player;
	player = NULL;

	enemys.clear();
	others.clear();
	items.clear();
	vigliances.clear();
	wbs.clear();
	factorys.clear();
	handOutbox.clear();
	
	delete pMeshfield;
	pMeshfield = NULL;

	gs = GameState_result_state_init;
}

void GameManage::result_state_init(void)
{
	pResult = new GameResult();
	pResult->setScore(totalScore);
	gs = GameState_result_state_running;

	if (bgm == SOUND_LABEL_MUSIC_GAME) {
		StopSound(SOUND_LABEL_MUSIC_GAME);
		bgm = -1;
	}

	if (bgm != SOUND_LABEL_MUSIC_TITLE) {
		PlaySound(SOUND_LABEL_MUSIC_TITLE);
		bgm = SOUND_LABEL_MUSIC_TITLE;
	}
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
	PlaySound(SOUND_LABEL_SE_PASS);

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

void GameManage::factoryUpdate(void)
{
	int factorysNum = factorys.size();
	for (int i = 0; i < factorysNum; i++)
	{
		vector<NearInfo> list = map->calNearObject(factorys[i], 3);

		int listNum = list.size();
		for (int j = 0; j < listNum; j++)
		{
			if (list[j].obj == player && player->getFindHoldings())
			{
				D3DXVECTOR2 pos = player->getBoundingCenter();
				Item* item = factorys[i]->createItem(pos.x, pos.y);
				map->addGameObject(item);
				items.push_back(item);

				factorys[i]->setIsPlayAnima(true);
				factorys[i]->setAnimaPlayFream(120);
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
		for (int j = 0; j < listNum; j++)
		{
			if (typeid(*list[j].obj) == typeid(Item) && list[j].touchType == TouchType::cover
				&& ((Item*)list[j].obj)->getBelong() == NULL)
			{
				list[j].obj->setIsDisplay(false);
				list[j].obj->setIsDelete(true);
				pEmitter->Submit(((Item*)list[j].obj)->getStatusNow());

				handOutbox[i]->setIsPlayAnima(true);
				handOutbox[i]->setAnimaPlayFream(120);
			}
		}
	}
}
void GameManage::cleanDead(void)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i]->getIsDestory() || items[i]->getIsDelete())
		{
			Item* tmp = items[i];
			for (vector<Item*>::iterator it = items.begin(); it != items.end(); it++)
			{
				if (*it == items[i])
				{
					delete items[i];
					items.erase(it);
					it = items.begin();
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
	if (Keyboard_IsTrigger(DIK_RETURN) || Gamepad_isTrigger(XINPUT_GAMEPAD_BACK))
	{
		gs = name;
	}
}
