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
	BattleChara* bc = new BattleChara();
	bc->setAtk(10);
	bc->setCamp(CampType::CampTypePlayer);
	bc->setHpMax(100);
	bc->setHpNow(100);
	bc->setMovePoint(10);
	bc->setMpMax(10);
	bc->setMpNow(10);
	bc->setName("wong");
	bc->setSpeed(10);
	Player* mesh = new Player("radio.x");
	mesh->loadModel(pD3DDevice);
	mesh->setWalkSpeed(0.01);
	mesh->setMaxSpeed(0.3);
	mesh->setCanMove(true);
	mesh->setVecNowPos(new D3DXVECTOR3(-10, 0, 0));
	mesh->setOverlapLevel(1);
	mesh->setBattleChara(bc);
	player = mesh;
	map->addGameObject(mesh);

	Model* tree = new Model("Rock1.blend.x");
	tree->loadModel(pD3DDevice);
	tree->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	tree->setCanMove(false);
	tree->setVecNowPos(new D3DXVECTOR3(7.5, 0, 0));
	tree->setOverlapLevel(1);
	others.push_back(tree);
	map->addGameObject(tree);

	//Model* tree2 = new Model("tree.x");
	//tree2->loadModel(pD3DDevice);
	//tree2->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	////mesh1->setRotateSpeed(20);
	//tree2->setCanMove(false);
	//tree2->setVecNowPos(new D3DXVECTOR3(-7.5, 0, 0));
	//tree2->setOverlapLevel(1);
	//others.push_back(tree2);
	//map->addGameObject(tree2);

	Model* tree3 = new Ground("grass ground.blend.x");
	tree3->loadModel(pD3DDevice);
	tree3->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	//mesh1->setRotateSpeed(20);
	tree3->setCanMove(false);
	tree3->setVecNowPos(new D3DXVECTOR3(0, 0, 0));
	tree3->setOverlapLevel(-5);
	others.push_back(tree3);
	map->addGameObject(tree3);

	BattleChara* bc1 = new BattleChara();
	bc1->setAtk(10);
	bc1->setCamp(CampType::CampTypeEnemy);
	bc1->setHpMax(10);
	bc1->setHpNow(10);
	bc1->setMovePoint(30);
	bc1->setMpMax(10);
	bc1->setMpNow(10);
	bc1->setName("enemy");
	bc1->setSpeed(10);
	Enemy* mesh3 = new Enemy("T-Rex.x");
	mesh3->loadModel(pD3DDevice);
	mesh3->setWalkSpeed(0.01);
	mesh3->setMaxSpeed(0.3);
	mesh3->setCanMove(true);
	mesh3->setVecNowPos(new D3DXVECTOR3(1, 0, 1));
	mesh3->setVecPatrolStart(new D3DXVECTOR3(1, 0, 1));
	mesh3->setVecPatrolEnd(new D3DXVECTOR3(1, 0, 5));
	mesh3->setOverlapLevel(1);
	mesh3->setBattleChara(bc1);
	mesh3->setTrackingRadius(10);
	mesh3->setBattleRadius(5);
	enemys.push_back(mesh3);
	map->addGameObject(mesh3);

	//Vigilance* mesh4 = new Vigilance();
	//mesh4->setMaxSpeed(0.3);
	//mesh4->setCanMove(true);
	//mesh4->setVecNowPos(new D3DXVECTOR3(1, 0, 1));
	//mesh4->setBelong(mesh3);
	//mesh4->setRadius(10);
	//mesh4->setOverlapLevel(-5);
	//vigliances.push_back(mesh4);
	//map->addGameObject(mesh4);

	Vigilance* mesh5 = new Vigilance();
	mesh5->setMaxSpeed(0.3);
	mesh5->setCanMove(true);
	mesh5->setVecNowPos(new D3DXVECTOR3(1, 0, 1));
	mesh5->setBelong(mesh3);
	mesh5->setRadius(5);
	mesh5->setOverlapLevel(-5);
	vigliances.push_back(mesh5);
	map->addGameObject(mesh5);

	//battleInit();


	//MovePerform *per = new MovePerform();
	//per->setActor(player);
	//per->setMoveSpeed(0.1);
	//per->setVecTarget(D3DXVECTOR3(-12, 0, -10));
	//per->setVecStart(D3DXVECTOR3(player->getBoundingCenter().x, 0, player->getBoundingCenter().y));
	//pm.addPerforms(per);

	//Parts* par = new Parts();
	//par->setModel(new Cube());

	//Parts* par2 = new Parts();
	//par2->setModel(new Cube());
	//par2->setOffsetS({ 2, 2, 2 });
	//par2->setOffsetT({ 0, 0, 0 });
	//par2->setOffsetR({ 0, 0, 0 });
	//par->addChild(par2);

	//Parts* par3 = new Parts();
	//par3->setModel(new Cube());
	//par3->setOffsetT({ 5, 0, 0 });
	//par3->setOffsetR({ 0, 0, 0 });
	//par->addChild(par3);

	//Parts* par4 = new Parts();
	//par4->setModel(new Cube());
	//par4->setOffsetT({ -5, 0, 0 });
	//par4->setOffsetR({ 0, 0, 0 });
	//par->addChild(par4);

	//Parts* par5 = new Parts();
	//par5->setModel(new Cube());
	//par5->setOffsetT({ 0, 2, 0 });
	//par5->setOffsetR({ 0, 0, 0 });
	//par->addChild(par5);
	//
	//MyMesh* mm = new MyMesh();
	//mm->setParts(par);
	//mm->setVecNowPos(new D3DXVECTOR3(0, 0, -10));
	//mm->setMaxSpeed(0.3);
	//mm->setCanMove(true);
	//mm->setOverlapLevel(1);
	//others.push_back(mm);
	//map->addGameObject(mm);

	//AnimationTemplate animateTamp(1, { 0, 0, 0 }, { 0, 0, 0 }, { 5, 0, 0 }, { 0, 0, 0 }, 300);
	//AnimationTemplate animateTamp1(4, { 0, 0, 0 }, { 0, 120, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 300);
	//AnimationTemplate animateTamp2(1, { 0, 0, 0 }, { 0, 120, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 300);
	//AnimationTemplate animateTamp3(1, { 0, 0, 0 }, { 0, 120, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 300);
	//AnimationTemplate animateTamp4(1, { 0, 0, 0 }, { 0, 120, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 300);
	//vector<AnimationInfoTemplate> list;
	//list.push_back({ &animateTamp, 0 });
	//list.push_back({ &animateTamp1, 150 });
	//AnimationManage::addAnimateTemplate(list);
	//am.addAnimation(0, mm);


	gs = GameState::GameStateGameRunning;
}

void GameManage::gameStateUpdate(void)
{
	//battle = NULL;
	player->setIsReadInput(true);
	int enemyNum = enemys.size();
	for (int i = 0; i < enemyNum; i++)
	{
		enemys[i]->setIsPatrol(true);
	}


	if (pm.playPerforms())
	{
		int enemyNum = enemys.size();
		for (int i = 0; i < enemyNum; i++)
		{
			enemys[i]->setIsPatrol(false);
		}
		player->setIsReadInput(false);
		lockUnmoveObject();
		return;
	}

	if (checkIsInBattle())
	{
		player->setIsReadInput(false);
		battleUpdate();
	}
	else
	{
		animationUpdate();
		enemyUpdate();
	}
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
	int enemyNum = enemys.size();
	for (int i = 0; i < enemyNum; i++)
	{
		enemyUpdate(enemys[i]);
	}
}

void GameManage::enemyUpdate(Enemy* enemy)
{
	vector<GameObject*> battleList = map->calObjectInCycle(enemy->getBoundingCenter(), enemy->getBattleRadius());
	int battleListNum = battleList.size();
	for (int i = 0; i < battleListNum; i++)
	{
		if (player != battleList[i])
		{
			continue;
		}
		battleInit();
		battle->addCharas(enemy);
		return;
	}

	vector<GameObject*> trackingList = map->calObjectInCycle(enemy->getBoundingCenter(), enemy->getTrackingRadius());
	int trackingListNum = trackingList.size();
	for (int i = 0; i < trackingListNum; i++)
	{
		if (player != trackingList[i])
		{
			continue;
		}
		D3DXVECTOR2 listObjCenter = trackingList[i]->getBoundingCenter();
		D3DXVECTOR3 targe = D3DXVECTOR3(listObjCenter.x, 0, listObjCenter.y);

		vector<GameObject*> sightList = map->calObjectOnSight(enemy, trackingList[i]);
		if (sightList.size() != 0)
		{
			continue;
		}
		enemy->setVecPatrolTarget(&targe);
		enemy->setIsTracking(true);
		return;
	}
}

void GameManage::animationUpdate(void)
{
	am.play();
	am.cleanEndAnimation();
}

void GameManage::battleInit(void)
{
	if (!checkIsInBattle())
	{
		Player* pointMesh = new Player("face.x");
		pointMesh->loadModel(pD3DDevice);
		pointMesh->setWalkSpeed(0.01);
		pointMesh->setMaxSpeed(0.3);
		pointMesh->setCanMove(true);
		pointMesh->setIsDisplay(false);
		pointMesh->setVecNowPos(new D3DXVECTOR3(-10, 0, -10));
		pointMesh->setOverlapLevel(-100);

		MeumUI *cmdMeum = new MeumUI();
		uis.push_back(cmdMeum);

		battle = new Battle(map, &pm, cmdMeum, pointMesh);
		battle->addCharas(player);
		battleResult = BattleResultType::BattleResultTypeUnknow;
	}
}

bool GameManage::checkIsInBattle(void)
{
	if (battle != NULL)
	{
		return battle->checkEnd() == 0 ? true : false;
	}
	return false;
}

void GameManage::battleUpdate(void)
{
	battle->start();
	if (!checkIsInBattle())
	{
		safe_delete<Battle>(battle);
	}
}

void GameManage::lockUnmoveObject(void)
{
	GameObject *actor = pm.getPlayingPerforms()->getActor();

	if (actor != player)
	{
		player->lockThisTurn();
	}
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
