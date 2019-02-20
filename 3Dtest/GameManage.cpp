#include "stdafx.h"
#include "GameManage.h"
#include "Model.h"
#include "Player.h"
#include "Ground.h"
#include "input.h"
#include "Enemy.h"
#include "MovePerform.h"
#include "TextureHandler2D.h"
#include "MeumUI.h"
#include "UI.h"
#include "MyMesh.h"
#include "NameTap.h"

GameManage::GameManage()
{
	gs = GameState::GameStateGameInit;
}

GameManage::GameManage(LPDIRECT3DDEVICE9 pD3DDevice)
{
	setPD3DDevice(pD3DDevice);
	gs = GameState::GameStateTitleInit;
}


GameManage::~GameManage()
{
	int gameObjectsNum = (int)models.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		SAFE_DELETE(models[i]);
	}
	models.clear();
}

void GameManage::init(void)
{
	map = new MapManage();

	D3DXVECTOR3* cameraPos = new D3DXVECTOR3(0, 6, -15);
	D3DXVECTOR3* cameraWatchAt = new D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3* cameraUp = new D3DXVECTOR3(0, 1, 0);
	camera = new Camera(cameraPos, cameraWatchAt, cameraUp);

	light = new Light();
	light->init(pD3DDevice);

	//load textures
	TextureHandler2D::AddTexture("net.jpg", 383, 300);
	TextureHandler2D::AddTexture("grass.jpg", 1024, 987);
	TextureHandler2D::AddTexture("shadow000.jpg", 80, 80);
	TextureHandler2D::AddTexture("brid1.png", 2736, 1824);
	TextureHandler2D::AddTexture("brid2.png", 2736, 1824);
	TextureHandler2D::AddTexture("win.png", 2736, 1824);
	TextureHandler2D::AddTexture("lose.png", 2736, 1824);
	TextureHandler2D::AddTexture("title.png", 580, 326);
	TextureHandler2D::AddTexture("fire ball.png", 2736, 1824);
	TextureHandler2D::AddTexture("arrow1.png", 2736, 1824);
	TextureHandler2D::LoadTextures(pD3DDevice);

	Billboard::initStaticMember(pD3DDevice);

	fadeFrame = new MeumUI();

	Model *playerModel = new Model("player.blend.x");
	playerModel->setIsWithAnimation(true);
	playerModel->loadModel(pD3DDevice);
	models.push_back(playerModel);
	Model *monsterModel = new Model("moster.blend.x");
	monsterModel->setIsWithAnimation(true);
	monsterModel->loadModel(pD3DDevice);
	models.push_back(monsterModel);
	Model *wallModel = new Model("rock wall.blend.x");
	wallModel->setIsWithAnimation(false);
	wallModel->loadModel(pD3DDevice);
	models.push_back(wallModel);
	Model *wall2Model = new Model("rock wall2.blend.x");
	wall2Model->setIsWithAnimation(false);
	wall2Model->loadModel(pD3DDevice);
	models.push_back(wall2Model);
	Model *groundModel = new Model("aaa.blend.x");
	groundModel->setIsWithAnimation(false);
	groundModel->loadModel(pD3DDevice);
	models.push_back(groundModel);
}

void GameManage::beforeUpdate(void)
{
	map->cleanGameObject();
	cleanDeletedObject();

	int gameObjectsNum = (int)enemys.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		map->addGameObject(enemys[i]);
	}
	gameObjectsNum = (int)others.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		map->addGameObject(others[i]);
	}
	gameObjectsNum = (int)vigliances.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		map->addGameObject(vigliances[i]);
	}

	map->addGameObject(player);

	gameObjectsNum = (int)uis.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		map->addGameObject2D(uis[i]);
	}

	map->gameObjectsBeforeUpdate();
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
		map->updateGameObejcts();
		break;
	case GameState::GameStateTitleClean:
		titleStateClean();
		break;
	case GameState::GameStateGameInit:
		gameStateInit();
		break;
	case GameState::GameStateGameRunning:
		gameStateUpdate();
		map->updateGameObejcts();
		break;
	case GameState::GameStateGameClean:
		gameStateClean();
		break;
	case GameState::GameStateEndInit:
		endStateInit();
		break;
	case GameState::GameStateEndRunning:
		endStateUpdate();
		map->updateGameObejcts();
		break;
	case GameState::GameStateEndClean:
		endStateClean();
		break;
	}


}

void GameManage::draw(void)
{
	light->lightSet(pD3DDevice);
	camera->draw(pD3DDevice);

	if (gs == GameState::GameStateGameRunning || gs == GameState::GameStateTitleRunning || gs == GameState::GameStateEndRunning)
	{
		map->drawGameObjects(pD3DDevice);
	}
	fade();
}

void GameManage::release(void)
{
}

void GameManage::titleStateInit(void)
{
	UI* ui = new UI({ 0, 0 }, Common::screen_width, Common::screen_height, 7);

	MeumUI *title = new MeumUI();
	title->setBackground(ui);
	title->setPosition({ 0, 0 });
	title->setIsDisplay(true);

	uis.push_back(title);
	if (isFade == 1)
	{
		fadeoutFlage = false;
	}

	gs = GameState::GameStateTitleRunning;
}

void GameManage::titleStateUpdate(void)
{
	if (!fadeoutFlage)
	{
		setIsFade(-1);
		fadeoutFlage = true;
	}

	if (isFade == 0)
	{
		if (Keyboard_IsTrigger(DIK_SPACE))
		{
			setIsFade(1);
			
		}
	}

	if (fadeAlpha == 0 && isFade == -1)
	{
		setIsFade(0);
	}
	if (fadeAlpha >= 255 && isFade == 1)
	{
		gs = GameState::GameStateTitleClean;
	}
}

void GameManage::titleStateClean(void)
{
	safe_delete<MeumUI>(uis[0]);
	uis.clear();

	gs = GameState::GameStateGameInit;
}

void GameManage::gameStateInit(void)
{
	BattleSkill* fireBall = new BattleSkill();
	fireBall->setTextureIndex(8);
	fireBall->setCost(1);
	fireBall->setDamage(5);
	fireBall->setDamageTarget(EffectTarget::EffectTargetEnemy);
	fireBall->setDistance(20);
	fireBall->setHeal(0);
	fireBall->setHealTarget(EffectTarget::EffectTargetNoTarget);
	fireBall->setMainTarget(EffectTarget::EffectTargetEnemy);
	fireBall->setName("fire Ball");
	fireBall->setSideEffect(NULL);
	fireBall->setSkillType(DamageType::magic);

	SideEffect* se = new SideEffect();
	se->setType(SideEffectType::SideEffectTypePull);
	se->setTarget(EffectTarget::EffectTargetEnemy);
	BattleSkill* chain = new BattleSkill();
	chain->setTextureIndex(9);
	chain->setCost(1);
	chain->setDamage(0);
	chain->setDamageTarget(EffectTarget::EffectTargetEnemy);
	chain->setDistance(20);
	chain->setHeal(0);
	chain->setHealTarget(EffectTarget::EffectTargetNoTarget);
	chain->setMainTarget(EffectTarget::EffectTargetEnemy);
	chain->setName("chain");
	chain->setSideEffect(se);
	chain->setSkillType(DamageType::magic);

	BattleChara* bc = new BattleChara();
	bc->setAtk(10);
	bc->setCamp(CampType::CampTypePlayer);
	bc->setHpMax(40);
	bc->setHpNow(40);
	bc->setMovePoint(20);
	bc->setMpMax(10);
	bc->setMpNow(10);
	bc->setName("Player");
	bc->setSpeed(10);
	bc->addSkill(fireBall);
	bc->addSkill(chain);
	Player* mesh = new Player();
	mesh->setModel(models[ModelType::ModelTypePlayer]);
	mesh->setWalkSpeed(0.3f);
	mesh->setMaxSpeed(0.3f);
	mesh->setCanMove(true);
	mesh->setVecNowPos(new D3DXVECTOR3(-90, 0, -85));
	mesh->setOverlapLevel(1);
	mesh->setBattleChara(bc);
	player = mesh;
	map->addGameObject(mesh);

	GameObject* tree = new GameObject();
	tree->setModel(models[ModelType::ModelTypeRockWall]);
	tree->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	tree->setCanMove(false);
	tree->setIsDisplay(true);
	tree->setVecNowPos(new D3DXVECTOR3(100, 0, 0));
	tree->setOverlapLevel(500);
	others.push_back(tree);
	map->addGameObject(tree);

	GameObject* tree10 = new GameObject();
	tree10->setModel(models[ModelType::ModelTypeRockWall]);
	tree10->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	tree10->setCanMove(false);
	tree10->setIsDisplay(true);
	tree10->setVecNowPos(new D3DXVECTOR3(-100, 0, 0));
	tree10->setOverlapLevel(500);
	others.push_back(tree10);
	map->addGameObject(tree10);

	GameObject* tree8 = new GameObject();
	tree8->setModel(models[ModelType::ModelTypeRockWall2]);
	tree8->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	tree8->setCanMove(false);
	tree8->setIsDisplay(true);
	tree8->setVecNowPos(new D3DXVECTOR3(0, 0, 100));
	tree8->setOverlapLevel(500);
	others.push_back(tree8);
	map->addGameObject(tree8);

	GameObject* tree9 = new GameObject();
	tree9->setModel(models[ModelType::ModelTypeRockWall2]);
	tree9->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	tree9->setCanMove(false);
	tree9->setIsDisplay(true);
	tree9->setVecNowPos(new D3DXVECTOR3(0, 0, -100));
	tree9->setOverlapLevel(500);
	others.push_back(tree9);
	map->addGameObject(tree9);

	GameObject* tree18 = new GameObject();
	tree18->setModel(models[ModelType::ModelTypeRockWall2]);
	tree18->setVecScale(new D3DXVECTOR3(0.8f, 1, 0.5f));
	tree18->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	tree18->setCanMove(false);
	tree18->setIsDisplay(true);
	tree18->setVecNowPos(new D3DXVECTOR3(-90, 0, -60));
	tree18->setOverlapLevel(500);
	others.push_back(tree18);
	map->addGameObject(tree18);

	GameObject* tree19 = new GameObject();
	tree19->setModel(models[ModelType::ModelTypeRockWall2]);
	tree19->setVecScale(new D3DXVECTOR3(0.8f, 1, 0.5f));
	tree19->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	tree19->setCanMove(false);
	tree19->setIsDisplay(true);
	tree19->setVecNowPos(new D3DXVECTOR3(90, 0, 0));
	tree19->setOverlapLevel(500);
	others.push_back(tree19);
	map->addGameObject(tree19);

	GameObject* tree3 = new Ground();
	tree3->setModel(models[ModelType::ModelTypeAAA]);
	tree3->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	tree3->setCanMove(false);
	tree3->setIsDisplay(true);
	tree3->setVecNowPos(new D3DXVECTOR3(0, 0, 0));
	tree3->setOverlapLevel(-5);
	others.push_back(tree3);
	map->addGameObject(tree3);

	BattleChara* bc4 = new BattleChara();
	bc4->setAtk(10);
	bc4->setCamp(CampType::CampTypeEnemy);
	bc4->setHpMax(10);
	bc4->setHpNow(10);
	bc4->setMovePoint(10);
	bc4->setMpMax(10);
	bc4->setMpNow(10);
	bc4->setName("enemy1");
	bc4->setSpeed(10);
	Enemy* enemy1 = new Enemy();
	enemy1->setModel(models[ModelType::ModelTypeMonster]);
	enemy1->setWalkSpeed(0.05f);
	enemy1->setMaxSpeed(0.05f);
	enemy1->setCanMove(true);
	enemy1->setVecNowPos(new D3DXVECTOR3(-75, 0, -80));
	enemy1->setVecPatrolStart(new D3DXVECTOR3(-75, 0, -85));
	enemy1->setVecPatrolEnd(new D3DXVECTOR3(-75, 0, -70));
	enemy1->setOverlapLevel(1);
	enemy1->setBattleChara(bc4);
	enemy1->setTrackingRadius(20);
	enemy1->setBattleRadius(5);
	enemys.push_back(enemy1);
	map->addGameObject(enemy1);

	BattleChara* bc6 = new BattleChara();
	bc6->setAtk(10);
	bc6->setCamp(CampType::CampTypeEnemy);
	bc6->setHpMax(10);
	bc6->setHpNow(10);
	bc6->setMovePoint(10);
	bc6->setMpMax(10);
	bc6->setMpNow(10);
	bc6->setName("enemy2");
	bc6->setSpeed(10);
	Enemy* enemy2 = new Enemy();
	enemy2->setModel(models[ModelType::ModelTypeMonster]);
	enemy2->setWalkSpeed(0.05f);
	enemy2->setMaxSpeed(0.05f);
	enemy2->setCanMove(true);
	enemy2->setVecNowPos(new D3DXVECTOR3(-70, 0, -70));
	enemy2->setVecPatrolStart(new D3DXVECTOR3(-70, 0, -70));
	enemy2->setVecPatrolEnd(new D3DXVECTOR3(-50, 0, -70));
	enemy2->setOverlapLevel(1);
	enemy2->setBattleChara(bc6);
	enemy2->setTrackingRadius(20);
	enemy2->setBattleRadius(5);
	enemys.push_back(enemy2);
	map->addGameObject(enemy2);

	BattleChara* bc5 = new BattleChara();
	bc5->setAtk(10);
	bc5->setCamp(CampType::CampTypeEnemy);
	bc5->setHpMax(10);
	bc5->setHpNow(10);
	bc5->setMovePoint(10);
	bc5->setMpMax(10);
	bc5->setMpNow(10);
	bc5->setName("enemy3");
	bc5->setSpeed(10);
	Enemy* enemy3 = new Enemy();
	enemy3->setModel(models[ModelType::ModelTypeMonster]);
	enemy3->setWalkSpeed(0.05f);
	enemy3->setMaxSpeed(0.05f);
	enemy3->setCanMove(true);
	enemy3->setVecNowPos(new D3DXVECTOR3(-30, 0, -72));
	enemy3->setVecPatrolStart(new D3DXVECTOR3(0, 0, -72));
	enemy3->setVecPatrolEnd(new D3DXVECTOR3(-30, 0, -72));
	enemy3->setOverlapLevel(1);
	enemy3->setBattleChara(bc5);
	enemy3->setTrackingRadius(20);
	enemy3->setBattleRadius(5);
	enemys.push_back(enemy3);
	map->addGameObject(enemy3);

	BattleChara* bc3 = new BattleChara();
	bc3->setAtk(10);
	bc3->setCamp(CampType::CampTypeEnemy);
	bc3->setHpMax(10);
	bc3->setHpNow(10);
	bc3->setMovePoint(10);
	bc3->setMpMax(10);
	bc3->setMpNow(10);
	bc3->setName("enemy4");
	bc3->setSpeed(10);
	Enemy* enemy4 = new Enemy();
	enemy4->setModel(models[ModelType::ModelTypeMonster]);
	enemy4->setWalkSpeed(0.05f);
	enemy4->setMaxSpeed(0.05f);
	enemy4->setCanMove(true);
	enemy4->setVecNowPos(new D3DXVECTOR3(-30, 0, -83));
	enemy4->setVecPatrolStart(new D3DXVECTOR3(0, 0, -83));
	enemy4->setVecPatrolEnd(new D3DXVECTOR3(-30, 0, -83));
	enemy4->setOverlapLevel(1);
	enemy4->setBattleChara(bc3);
	enemy4->setTrackingRadius(20);
	enemy4->setBattleRadius(5);
	enemys.push_back(enemy4);
	map->addGameObject(enemy4);

	BattleChara* bc7 = new BattleChara();
	bc7->setAtk(10);
	bc7->setCamp(CampType::CampTypeEnemy);
	bc7->setHpMax(10);
	bc7->setHpNow(10);
	bc7->setMovePoint(10);
	bc7->setMpMax(10);
	bc7->setMpNow(10);
	bc7->setName("enemy5");
	bc7->setSpeed(10);
	Enemy* enemy5 = new Enemy();
	enemy5->setModel(models[ModelType::ModelTypeMonster]);
	enemy5->setWalkSpeed(0.05f);
	enemy5->setMaxSpeed(0.05f);
	enemy5->setCanMove(true);
	enemy5->setVecNowPos(new D3DXVECTOR3(0, 0, -78));
	enemy5->setVecPatrolStart(new D3DXVECTOR3(0, 0, -78));
	enemy5->setVecPatrolEnd(new D3DXVECTOR3(30, 0, -78));
	enemy5->setOverlapLevel(1);
	enemy5->setBattleChara(bc7);
	enemy5->setTrackingRadius(20);
	enemy5->setBattleRadius(5);
	enemys.push_back(enemy5);
	map->addGameObject(enemy5);

	BattleChara* bc8 = new BattleChara();
	bc8->setAtk(10);
	bc8->setCamp(CampType::CampTypeEnemy);
	bc8->setHpMax(10);
	bc8->setHpNow(10);
	bc8->setMovePoint(10);
	bc8->setMpMax(10);
	bc8->setMpNow(10);
	bc8->setName("enemy6");
	bc8->setSpeed(10);
	Enemy* enemy6 = new Enemy();
	enemy6->setModel(models[ModelType::ModelTypeMonster]);
	enemy6->setWalkSpeed(0.05f);
	enemy6->setMaxSpeed(0.05f);
	enemy6->setCanMove(true);
	enemy6->setVecNowPos(new D3DXVECTOR3(0, 0, -50));
	enemy6->setVecPatrolStart(new D3DXVECTOR3(-30, 0, -50));
	enemy6->setVecPatrolEnd(new D3DXVECTOR3(30, 0, -50));
	enemy6->setOverlapLevel(1);
	enemy6->setBattleChara(bc8);
	enemy6->setTrackingRadius(20);
	enemy6->setBattleRadius(5);
	enemys.push_back(enemy6);
	map->addGameObject(enemy6);

	BattleChara* bc9 = new BattleChara();
	bc9->setAtk(10);
	bc9->setCamp(CampType::CampTypeEnemy);
	bc9->setHpMax(10);
	bc9->setHpNow(10);
	bc9->setMovePoint(10);
	bc9->setMpMax(10);
	bc9->setMpNow(10);
	bc9->setName("enemy7");
	bc9->setSpeed(10);
	Enemy* enemy7 = new Enemy();
	enemy7->setModel(models[ModelType::ModelTypeMonster]);
	enemy7->setWalkSpeed(0.05f);
	enemy7->setMaxSpeed(0.05f);
	enemy7->setCanMove(true);
	enemy7->setVecNowPos(new D3DXVECTOR3(10, 0, -40));
	enemy7->setVecPatrolStart(new D3DXVECTOR3(-30, 0, -40));
	enemy7->setVecPatrolEnd(new D3DXVECTOR3(30, 0, -40));
	enemy7->setOverlapLevel(1);
	enemy7->setBattleChara(bc9);
	enemy7->setTrackingRadius(20);
	enemy7->setBattleRadius(5);
	enemys.push_back(enemy7);
	map->addGameObject(enemy7);

	BattleChara* bc10 = new BattleChara();
	bc10->setAtk(10);
	bc10->setCamp(CampType::CampTypeEnemy);
	bc10->setHpMax(10);
	bc10->setHpNow(10);
	bc10->setMovePoint(10);
	bc10->setMpMax(10);
	bc10->setMpNow(10);
	bc10->setName("enemy8");
	bc10->setSpeed(10);
	Enemy* enemy8 = new Enemy();
	enemy8->setModel(models[ModelType::ModelTypeMonster]);
	enemy8->setWalkSpeed(0.05f);
	enemy8->setMaxSpeed(0.05f);
	enemy8->setCanMove(true);
	enemy8->setVecNowPos(new D3DXVECTOR3(20, 0, -30));
	enemy8->setVecPatrolStart(new D3DXVECTOR3(-30, 0, -30));
	enemy8->setVecPatrolEnd(new D3DXVECTOR3(30, 0, -30));
	enemy8->setOverlapLevel(1);
	enemy8->setBattleChara(bc10);
	enemy8->setTrackingRadius(20);
	enemy8->setBattleRadius(5);
	enemys.push_back(enemy8);
	map->addGameObject(enemy8);

	BattleChara* bc11 = new BattleChara();
	bc11->setAtk(10);
	bc11->setCamp(CampType::CampTypeEnemy);
	bc11->setHpMax(10);
	bc11->setHpNow(10);
	bc11->setMovePoint(10);
	bc11->setMpMax(10);
	bc11->setMpNow(10);
	bc11->setName("enemy9");
	bc11->setSpeed(10);
	Enemy* enemy9 = new Enemy();
	enemy9->setModel(models[ModelType::ModelTypeMonster]);
	enemy9->setWalkSpeed(0.05f);
	enemy9->setMaxSpeed(0.05f);
	enemy9->setCanMove(true);
	enemy9->setVecNowPos(new D3DXVECTOR3(0, 0, -20));
	enemy9->setVecPatrolStart(new D3DXVECTOR3(-30, 0, -20));
	enemy9->setVecPatrolEnd(new D3DXVECTOR3(30, 0, -20));
	enemy9->setOverlapLevel(1);
	enemy9->setBattleChara(bc11);
	enemy9->setTrackingRadius(20);
	enemy9->setBattleRadius(5);
	enemys.push_back(enemy9);
	map->addGameObject(enemy9);


	BattleChara* bc12 = new BattleChara();
	bc12->setAtk(10);
	bc12->setCamp(CampType::CampTypeEnemy);
	bc12->setHpMax(10);
	bc12->setHpNow(10);
	bc12->setMovePoint(10);
	bc12->setMpMax(10);
	bc12->setMpNow(10);
	bc12->setName("enemy10");
	bc12->setSpeed(10);
	Enemy* enemy10 = new Enemy();
	enemy10->setModel(models[ModelType::ModelTypeMonster]);
	enemy10->setWalkSpeed(0.05f);
	enemy10->setMaxSpeed(0.05f);
	enemy10->setCanMove(true);
	enemy10->setVecNowPos(new D3DXVECTOR3(-10, 0, -10));
	enemy10->setVecPatrolStart(new D3DXVECTOR3(-30, 0, -10));
	enemy10->setVecPatrolEnd(new D3DXVECTOR3(30, 0, -10));
	enemy10->setOverlapLevel(1);
	enemy10->setBattleChara(bc12);
	enemy10->setTrackingRadius(20);
	enemy10->setBattleRadius(5);
	enemys.push_back(enemy10);
	map->addGameObject(enemy10);

	BattleChara* bc13 = new BattleChara();
	bc13->setAtk(10);
	bc13->setCamp(CampType::CampTypeEnemy);
	bc13->setHpMax(10);
	bc13->setHpNow(10);
	bc13->setMovePoint(10);
	bc13->setMpMax(10);
	bc13->setMpNow(10);
	bc13->setName("enemy11");
	bc13->setSpeed(10);
	Enemy* enemy11 = new Enemy();
	enemy11->setVecScale(new D3DXVECTOR3( 5.0, 5.0, 5.0 ));
	enemy11->setModel(models[ModelType::ModelTypeMonster]);
	enemy11->setWalkSpeed(0.05f);
	enemy11->setMaxSpeed(0.05f);
	enemy11->setCanMove(true);
	enemy11->setVecNowPos(new D3DXVECTOR3(30, 0, 40));
	enemy11->setVecPatrolStart(new D3DXVECTOR3(30, 0, 20));
	enemy11->setVecPatrolEnd(new D3DXVECTOR3(30, 0, 40));
	enemy11->setOverlapLevel(1);
	enemy11->setBattleChara(bc13);
	enemy11->setTrackingRadius(50);
	enemy11->setBattleRadius(20);
	enemys.push_back(enemy11);
	boss = enemy11;
	map->addGameObject(enemy11);

	if (isFade == 1)
	{
		fadeoutFlage = false;
	}
	gs = GameState::GameStateGameRunning;
}

void GameManage::gameStateUpdate(void)
{
	if (!fadeoutFlage)
	{
		setIsFade(-1);
		fadeoutFlage = true;
	}
	if (isFade == 0)
	{
		player->setIsReadInput(true);
		int enemyNum = (int)enemys.size();
		for (int i = 0; i < enemyNum; i++)
		{
			enemys[i]->setIsPatrol(true);
		}


		if (pm.playPerforms())
		{
			int enemyNum = (int)enemys.size();
			for (int i = 0; i < enemyNum; i++)
			{
				enemys[i]->setIsPatrol(false);
			}
			player->setIsReadInput(false);
			lockUnmoveObject();
			return;
		}
		else
		{
			if (checkIsInBattle())
			{
				if (battle->getBattleState() != BattleState::BattleStateMapMove)
				{
					int enemyNum = (int)enemys.size();
					for (int i = 0; i < enemyNum; i++)
					{
							enemys[i]->setIsPatrol(false);
					}
				}
				player->setIsReadInput(false);
				battleUpdate();
			}
		}
		cameraUpdate();
		enemyUpdate();
		othersUpdate();

		winStatus = checkEnd();
		if (winStatus)
		{
			setIsFade(1);
		}
	}
	if (fadeAlpha == 0 && isFade == -1)
	{
		setIsFade(0);
	}

	if (fadeAlpha >= 255 && isFade == 1)
	{
		gs = GameState::GameStateGameClean;
	}
}

void GameManage::gameStateClean(void)
{
	int gameObjectsNum = (int)others.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		SAFE_DELETE(others[i]);
	}
	gameObjectsNum = (int)vigliances.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		SAFE_DELETE(vigliances[i]);
	}
	gameObjectsNum = (int)enemys.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		SAFE_DELETE(enemys[i]);
	}
	gameObjectsNum = (int)uis.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		SAFE_DELETE(uis[i]);
	}
	safe_delete<Player>(player);

	enemys.clear();
	others.clear();
	vigliances.clear();
	uis.clear();

	gs = GameState::GameStateEndInit;
}

void GameManage::endStateInit(void)
{
	UI* ui = NULL;
	if (winStatus == 2)
	{
		ui = new UI({ 0, 0 }, Common::screen_width, Common::screen_height, 5);
	}
	else
	{
		ui = new UI({ 0, 0 }, Common::screen_width, Common::screen_height, 6);
	}

	MeumUI *title = new MeumUI();
	title->setBackground(ui);
	title->setPosition({ 0, 0 });
	title->setIsDisplay(true);

	uis.push_back(title);

	if (isFade == 1)
	{
		fadeoutFlage = false;
	}

	gs = GameState::GameStateEndRunning;
}

void GameManage::endStateUpdate(void)
{
	if (!fadeoutFlage)
	{
		setIsFade(-1);
		fadeoutFlage = true;
	}
	if (isFade == 0)
	{
		if (Keyboard_IsTrigger(DIK_SPACE))
		{
			setIsFade(1);

		}
	}
	if (fadeAlpha == 0 && isFade == -1)
	{
		setIsFade(0);
	}
	if (fadeAlpha >= 255 && isFade == 1)
	{
		gs = GameState::GameStateEndClean;
	}
}

void GameManage::endStateClean(void)
{
	safe_delete<MeumUI>(uis[0]);
	uis.clear();

	gs = GameState::GameStateTitleInit;
}

BOOL GameManage::checkEnd(void)
{
	if (player->getBattleChara() != NULL && player->getBattleChara()->getHpNow() <= 0)
	{
		return 1;
	}
	else if(boss == NULL)
	{
		return 2;
	}
	return FALSE;
}

void GameManage::cameraUpdate(void)
{
	if (gs == GameState::GameStateGameRunning && player != NULL)
	{
		camera->setVecWatchAt(player->getVecNowPos());
		camera->calPosition();

		D3DXVECTOR3 dir = *camera->getVecFront();
		dir.y = 0;
		player->setVecSpeedFront(&dir);
	}
	light->setDirection(camera->getVecFront());
}

void GameManage::enemyUpdate(void)
{
	int enemyNum = (int)enemys.size();
	for (int i = 0; i < enemyNum; i++)
	{
		if (!enemys[i]->getIsDelete())
		{
			enemyUpdate(enemys[i]);
		}
	}
}

void GameManage::enemyUpdate(Enemy* enemy)
{
	D3DXVECTOR3 dis = *enemy->getVecNowPos() - *player->getVecNowPos();
	if (D3DXVec3LengthSq(&dis) > 4900)
	{
		enemy->setDisappear(true);
		return;
	}
	else if(battle == NULL || !battle->checkCharaIsInBattle(enemy))
	{
		enemy->setDisappear(false);
	}

	vector<GameObject*> battleList = map->calObjectInCycle(enemy->getBoundingCenter(), enemy->getBattleRadius());
	int battleListNum = (int)battleList.size();
	for (int i = 0; i < battleListNum; i++)
	{
		if (player != battleList[i] || player->getIsDelete())
		{
			continue;
		}
		battleInit();
		addCharaToBattle(battle, enemy);
		return;
	}

	vector<GameObject*> trackingList = map->calObjectInCycle(enemy->getBoundingCenter(), enemy->getTrackingRadius());
	int trackingListNum = (int)trackingList.size();
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
	enemy->setIsTracking(false);
}

void GameManage::othersUpdate(void)
{
	if (!checkIsInBattle())
	{
		int othersNum = (int)others.size();
		for (int i = 0; i < othersNum; i++)
		{
			if (typeid(*others[i]) == typeid(NameTap))
			{
				others[i]->setIsDelete(true);
			}
		}
	}
}

void GameManage::battleInit(void)
{
	if (!checkIsInBattle())
	{
		Model *faceModel = new Model("face.x");
		faceModel->setIsWithAnimation(false);
		faceModel->loadModel(pD3DDevice);
		models.push_back(faceModel);

		Player* pointMesh = new Player();
		pointMesh->setModel(faceModel);
		pointMesh->setWalkSpeed(0.3f);
		pointMesh->setMaxSpeed(0.3f);
		pointMesh->setCanMove(true);
		pointMesh->setIsDisplay(false);
		pointMesh->setVecNowPos(new D3DXVECTOR3(-10, 0, -10));
		pointMesh->setOverlapLevel(-100);
		others.push_back(pointMesh);

		MeumUI *cmdMeum = new MeumUI();
		uis.push_back(cmdMeum);

		MeumUI *textBox = new MeumUI();
		uis.push_back(textBox);

		MeumUI *statusBox = new MeumUI();
		uis.push_back(statusBox);

		Billboard* billboard = new Billboard();
		billboard->setCamera(camera);
		billboard->setIsDisplay(false);
		billboard->setMaxSpeed(0.3f);
		billboard->setCanMove(true);
		billboard->setVecNowPos(new D3DXVECTOR3(0, 3, 0));
		billboard->setOverlapLevel(-1000);
		billboard->setIsDelete(false);
		billboard->setVecScale(new D3DXVECTOR3(5, 5, 5));
		others.push_back(billboard);
		map->addGameObject(billboard);

		battle = new Battle(map, &pm, cmdMeum, textBox, statusBox, pointMesh);
		addCharaToBattle(battle, player);
		battle->setSkillBillboard(billboard);
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

void GameManage::addCharaToBattle(Battle * battle, Chara* chara)
{
	if (!battle->checkCharaIsInBattle(chara))
	{

		NameTap* billboard = new NameTap();
		billboard->setCamera(camera);
		billboard->setIsDisplay(true);
		billboard->setMaxSpeed(0.3f);
		billboard->setCanMove(true);
		billboard->setVecNowPos(new D3DXVECTOR3(0, 3, 0));
		billboard->setOverlapLevel(-1000);
		billboard->setIsDelete(false);
		billboard->setBelong(chara);
		billboard->initName(pD3DDevice);
		others.push_back(billboard);
		map->addGameObject(billboard);

		battle->addCharas(chara);
	}
}

void GameManage::cleanDeletedObject(void)
{
	for (vector<Vigilance*>::iterator it = vigliances.begin(); it != vigliances.end();)
	{
		if ((*it)->getIsDelete() || (*it)->getBelong()->getIsDelete())
		{
			Vigilance* vi = *it;
			safe_delete<Vigilance>(vi);
			vigliances.erase(it);
			it = vigliances.begin();
			continue;
		}
		it++;
	}

	for (vector<Enemy*>::iterator it = enemys.begin(); it != enemys.end();)
	{
		if ((*it)->getIsDelete())
		{
			if (boss == *it)
			{
				boss = NULL;
			}
			Enemy* enemy = *it;
			safe_delete<Enemy>(enemy);
			enemys.erase(it);
			it = enemys.begin();
			continue;
		}
		it++;
	}

	for (vector<GameObject*>::iterator it = others.begin(); it != others.end();)
	{
		if ((*it)->getIsDelete())
		{
			GameObject* go = *it;
			safe_delete<GameObject>(go);
			others.erase(it);
			it = others.begin();
			continue;
		}
		it++;
	}

	for (vector<MeumUI*>::iterator it = uis.begin(); it != uis.end();)
	{
		if ((*it)->getIsDelete())
		{
			MeumUI* ui = *it;
			safe_delete<MeumUI>(ui);
			uis.erase(it);
			it = uis.begin();
			continue;
		}
		it++;
	}
}

void GameManage::lockUnmoveObject(void)
{
	GameObject *actor = pm.getPlayingPerforms()->getActor();

	if (actor != player)
	{
		player->lockThisTurn();
		player->setIsPlayAnima(false);
	}
	int gameObjectsNum = (int)enemys.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		if (actor == enemys[i])
		{
			continue;
		}
		enemys[i]->lockThisTurn();
		enemys[i]->setIsPlayAnima(false);
	}
	gameObjectsNum = (int)others.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		if (actor == others[i])
		{
			continue;
		}
		others[i]->lockThisTurn();
	}
	gameObjectsNum = (int)vigliances.size();
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

void GameManage::setIsFade(BOOL isFade)
{
	this->isFade = isFade;
	if (isFade == 1)
	{
		fadeAlpha = 0;
	}
	else if (isFade == -1)
	{
		fadeAlpha = 255;
	}
}

void GameManage::fade(void)
{
	if (isFade != 0)
	{
		if (isFade == 1)
		{
			fadeAlpha = fadeAlpha + 100 > 255 ? 255 : fadeAlpha + 100;
		}
		else
		{
			fadeAlpha = fadeAlpha - 100 < 0 ? 0 : fadeAlpha - 100;
		}

		UI *ui = new UI({ 0, 0 }, Common::screen_width, Common::screen_height, -1);
		ui->setColor(D3DCOLOR_RGBA(0, 0, 0, fadeAlpha));
		fadeFrame->setBackground(ui);
		fadeFrame->draw(pD3DDevice);
		delete ui;
	}
}
