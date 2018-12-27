#include "stdafx.h"
#include "GameManage.h"
#include "Model.h"
#include "Player.h"
#include "Ground.h"
#include "Vigilance.h"
#include "input.h"
#include "Enemy.h"
#include "MovePerform.h"
#include "TextureHandler2D.h"
#include "MeumUI.h"
#include "UI.h"
#include "MyMesh.h"
#include "AnimationSet.h"

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

	TextureHandler2D::AddTexture("net.jpg", 383, 300);
	TextureHandler2D::AddTexture("grass.jpg", 1024, 987);
	TextureHandler2D::LoadTextures(pD3DDevice);

	Cube::initStaticMember(pD3DDevice);
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

	int uiNum = uis.size();
	for (int i = 0; i < uiNum; i++)
	{
		uis[i]->dataUpdate();
		uis[i]->draw(pD3DDevice);
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
	mesh->setVecNowPos(new D3DXVECTOR3(-10, 0, 0));
	mesh->setOverlapLevel(1);
	player = mesh;
	map->addGameObject(mesh);


	Model* tree = new Model("Rock1.blend.x");
	tree->loadModel(pD3DDevice);
	tree->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	//mesh1->setRotateSpeed(20);
	tree->setCanMove(false);
	tree->setVecNowPos(new D3DXVECTOR3(7.5, 0, 0));
	tree->setOverlapLevel(1);
	others.push_back(tree);
	map->addGameObject(tree);

	Model* tree2 = new Model("tree.x");
	tree2->loadModel(pD3DDevice);
	tree2->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	//mesh1->setRotateSpeed(20);
	tree2->setCanMove(false);
	tree2->setVecNowPos(new D3DXVECTOR3(-7.5, 0, 0));
	tree2->setOverlapLevel(1);
	others.push_back(tree2);
	map->addGameObject(tree2);

	Model* tree3 = new Ground("grass ground.blend.x");
	tree3->loadModel(pD3DDevice);
	tree3->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	//mesh1->setRotateSpeed(20);
	tree3->setCanMove(false);
	tree3->setVecNowPos(new D3DXVECTOR3(0, 0, 0));
	tree3->setOverlapLevel(-5);
	others.push_back(tree3);
	map->addGameObject(tree3);


	Enemy* mesh3 = new Enemy("T-Rex.x");
	mesh3->loadModel(pD3DDevice);
	mesh3->setWalkSpeed(0.01);
	mesh3->setMaxSpeed(0.3);
	mesh3->setCanMove(true);
	mesh3->setVecNowPos(new D3DXVECTOR3(1, 0, 1));
	mesh3->setVecPatrolStart(new D3DXVECTOR3(1, 0, 1));
	mesh3->setVecPatrolEnd(new D3DXVECTOR3(1, 0, 5));
	mesh3->setOverlapLevel(1);
	//enemys.push_back(mesh3);
	//map->addGameObject(mesh3);

	Vigilance* mesh4 = new Vigilance();
	mesh4->setMaxSpeed(0.3);
	mesh4->setCanMove(true);
	mesh4->setVecNowPos(new D3DXVECTOR3(1, 0, 1));
	mesh4->setBelong(mesh3);
	mesh4->setRadius(10);
	mesh4->setOverlapLevel(-5);
	vigliances.push_back(mesh4);
	map->addGameObject(mesh4);

	MovePerform *per = new MovePerform();
	per->setActor(player);
	per->setMoveSpeed(0.1);
	per->setVecTarget(D3DXVECTOR3(-12, 0, 0));
	per->setVecStart(D3DXVECTOR3(player->getBoundingCenter().x, 0, player->getBoundingCenter().y));
	pm.addPerforms(per);

	UI* ui = new UI({ 0, 0 }, 200, 200, 0);
	UI* ui1 = new UI({ 20, 20 }, 50, 50, 1);
	UI* ui2 = new UI({ 80, 20 }, 50, 50, 1);
	ui2->setStr("ATTACK");
	UI* ui3 = new UI({ 80, 80 }, 50, 50, 1);
	ui3->setStr("RUN");
	MeumUI *meum = new MeumUI();
	meum->addOptins(ui2);
	meum->addOptins(ui3);
	meum->setBackground(ui);
	meum->setPointer(ui1);
	meum->setPosition({ 0, 0 });
	uis.push_back(meum);

	Parts* par = new Parts();
	par->setModel(new Cube());
	Parts* par2 = new Parts();
	par2->setModel(new Cube());
	par->addChild(par2);
	par2->setOffsetT({10, 2, 2 });
	par2->setOffsetR({ 45, 0, 0 });
	MyMesh* mm = new MyMesh();
	mm->setParts(par);
	mm->setVecNowPos(new D3DXVECTOR3(0, 0, -10));
	mm->setMaxSpeed(0.3);
	mm->setCanMove(true);
	mm->setOverlapLevel(1);
	others.push_back(mm);
	map->addGameObject(mm);

	AnimationTemplate animateTamp(1, { 0, 0, 0 }, { 0, 0, 0 }, { 10, 0, 0 }, { 0, 0, 0 }, 300);
	AnimationTemplate animateTamp1(1, { 0, 0, 0 }, { 0, 120, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 300);
	vector<AnimationInfoTemplate> list;
	list.push_back({ &animateTamp, 0 });
	list.push_back({ &animateTamp1, 150 });
	AnimationManage::addAnimateTemplate(list);
	am.addAnimation(0, mm);


	gs = GameState::GameStateGameRunning;
}

void GameManage::gameStateUpdate(void)
{
	if (pm.playPerforms())
	{
		lockUnmoveObject();
		return;
	}

	if (Keyboard_IsTrigger(DIK_0))
	{
		MovePerform *per = new MovePerform();
		per->setActor(player);
		per->setMoveSpeed(0.1);
		per->setVecTarget(D3DXVECTOR3(-12, 0, 0));
		per->setVecStart(D3DXVECTOR3(player->getBoundingCenter().x, 0, player->getBoundingCenter().y));
		pm.addPerforms(per);

		per = new MovePerform();
		per->setActor(player);
		per->setMoveSpeed(0.1);
		per->setVecTarget(D3DXVECTOR3(-12, 0, -10));
		per->setVecStart(D3DXVECTOR3(-12, 0, 0));
		pm.addPerforms(per);

		per = new MovePerform();
		per->setActor(player);
		per->setMoveSpeed(0.1);
		per->setVecTarget(D3DXVECTOR3(0, 0, -10));
		per->setVecStart(D3DXVECTOR3(-12, 0, -10));
		pm.addPerforms(per);
	}

	animationUpdate();
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
	if (player->getBattleChara() != NULL && player->getBattleChara()->getHpNow() <= 0)
	{
		gs = GameState::GameStateGameClean;
	}
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

void GameManage::animationUpdate(void)
{
	am.play();
	am.cleanEndAnimation();
}

void GameManage::lockUnmoveObject(void)
{
	GameObject *actor = pm.getPlayingPerforms()->getActor();

	int gameObjectsNum = enemys.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		if (actor == enemys[i])
		{
			continue;
		}
		enemys[i]->lockThisTurn();
	}
	gameObjectsNum = others.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		if (actor == others[i])
		{
			continue;
		}
		others[i]->lockThisTurn();
	}
	gameObjectsNum = vigliances.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		if (actor == vigliances[i])
		{
			continue;
		}
		vigliances[i]->lockThisTurn();
		map->addGameObject(vigliances[i]);
	}
}

void GameManage::setPD3DDevice(LPDIRECT3DDEVICE9 pD3DDevice)
{
	this->pD3DDevice = pD3DDevice;
}
