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
#include "NameTap.h"
#include "Bird.h"

GameManage::GameManage()
{
	gs = GameState::GameStateGameInit;
}

GameManage::GameManage(LPDIRECT3DDEVICE9 pD3DDevice)
{
	setPD3DDevice(pD3DDevice);
	//gs = GameState::GameStateTitleInit;
	gs = GameState::GameStateGameInit;
}


GameManage::~GameManage()
{
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
	TextureHandler2D::LoadTextures(pD3DDevice);

	Cube::initStaticMember(pD3DDevice);
	Billboard::initStaticMember(pD3DDevice);

	fadeFrame = new MeumUI();
}

void GameManage::beforeUpdate(void)
{
	map->cleanGameObject();
	cleanDeletedObject();

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

	map->addGameObject(player);

	gameObjectsNum = uis.size();
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

	//map->updateGameObejcts();

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
		//setIsFade(0);
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
	SideEffect* se = new SideEffect();
	se->setType(SideEffectType::SideEffectTypePull);
	se->setTarget(EffectTarget::EffectTargetEnemy);
	BattleSkill* fireBall = new BattleSkill();
	fireBall->setTextureIndex(8);
	fireBall->setCost(1);
	fireBall->setDamage(5);
	fireBall->setDamageTarget(EffectTarget::EffectTargetEnemy);
	fireBall->setDistance(10);
	fireBall->setHeal(0);
	fireBall->setHealTarget(EffectTarget::EffectTargetNoTarget);
	fireBall->setMainTarget(EffectTarget::EffectTargetEnemy);
	fireBall->setName("fire Ball");
	fireBall->setSideEffect(se);
	fireBall->setSkillType(DamageType::magic);
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
	Player* mesh = new Player("player.blend.x");
	mesh->setIsWithAnimation(true);
	mesh->loadModel(pD3DDevice);
	mesh->setWalkSpeed(0.3f);
	mesh->setMaxSpeed(0.3f);
	mesh->setCanMove(true);
	mesh->setVecNowPos(new D3DXVECTOR3(-90, 0, -85));
	mesh->setOverlapLevel(1);
	mesh->setBattleChara(bc);
	player = mesh;
	map->addGameObject(mesh);

	Model* tree = new Model("rock wall.blend.x");
	tree->loadModel(pD3DDevice);
	tree->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	tree->setCanMove(false);
	tree->setIsDisplay(true);
	tree->setVecNowPos(new D3DXVECTOR3(100, 0, 0));
	tree->setOverlapLevel(500);
	others.push_back(tree);
	map->addGameObject(tree);

	Model* tree10 = new Model("rock wall.blend.x");
	tree10->loadModel(pD3DDevice);
	tree10->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	tree10->setCanMove(false);
	tree10->setIsDisplay(true);
	tree10->setVecNowPos(new D3DXVECTOR3(-100, 0, 0));
	tree10->setOverlapLevel(500);
	others.push_back(tree10);
	map->addGameObject(tree10);

	Model* tree100 = new Model("rock wall.blend.x");
	tree100->setVecScale(new D3DXVECTOR3(0.5, 1, 0.3));
	tree100->loadModel(pD3DDevice);
	tree100->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	tree100->setCanMove(false);
	tree100->setIsDisplay(true);
	tree100->setVecNowPos(new D3DXVECTOR3(-50, 0, 80));
	tree100->setOverlapLevel(500);
	others.push_back(tree100);
	map->addGameObject(tree100);

	Model* tree8 = new Model("rock wall2.blend.x");
	tree8->loadModel(pD3DDevice);
	tree8->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	tree8->setCanMove(false);
	tree8->setIsDisplay(true);
	tree8->setVecNowPos(new D3DXVECTOR3(0, 0, 100));
	tree8->setOverlapLevel(500);
	others.push_back(tree8);
	map->addGameObject(tree8);

	Model* tree9 = new Model("rock wall2.blend.x");
	tree9->loadModel(pD3DDevice);
	tree9->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	tree9->setCanMove(false);
	tree9->setIsDisplay(true);
	tree9->setVecNowPos(new D3DXVECTOR3(0, 0, -100));
	tree9->setOverlapLevel(500);
	others.push_back(tree9);
	map->addGameObject(tree9);

	Model* tree18 = new Model("rock wall2.blend.x");
	tree18->setVecScale(new D3DXVECTOR3(0.8, 1, 0.5));
	tree18->loadModel(pD3DDevice);
	tree18->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	tree18->setCanMove(false);
	tree18->setIsDisplay(true);
	tree18->setVecNowPos(new D3DXVECTOR3(-90, 0, -60));
	tree18->setOverlapLevel(500);
	others.push_back(tree18);
	map->addGameObject(tree18);

	Model* tree19 = new Model("rock wall2.blend.x");
	tree19->setVecScale(new D3DXVECTOR3(0.8, 1, 0.5));
	tree19->loadModel(pD3DDevice);
	tree19->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	tree19->setCanMove(false);
	tree19->setIsDisplay(true);
	tree19->setVecNowPos(new D3DXVECTOR3(90, 0, 0));
	tree19->setOverlapLevel(500);
	others.push_back(tree19);
	map->addGameObject(tree19);

	Model* tree20 = new Model("rock wall2.blend.x");
	tree20->setVecScale(new D3DXVECTOR3(0.25, 1, 0.5));
	tree20->loadModel(pD3DDevice);
	tree20->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	tree20->setCanMove(false);
	tree20->setIsDisplay(true);
	tree20->setVecNowPos(new D3DXVECTOR3(0, 0, 50));
	tree20->setOverlapLevel(500);
	others.push_back(tree20);
	map->addGameObject(tree20);

	Model* tree3 = new Ground("aaa.blend.x");
	tree3->setIsWithAnimation(false);
	tree3->loadModel(pD3DDevice);
	tree3->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	//mesh1->setRotateSpeed(20);
	tree3->setCanMove(false);
	tree3->setIsDisplay(true);
	tree3->setVecNowPos(new D3DXVECTOR3(0, 0, 0));
	tree3->setOverlapLevel(-5);
	others.push_back(tree3);
	map->addGameObject(tree3);

	//BattleChara* bc1 = new BattleChara();
	//bc1->setAtk(10);
	//bc1->setCamp(CampType::CampTypeEnemy);
	//bc1->setHpMax(50);
	//bc1->setHpNow(50);
	//bc1->setMovePoint(30);
	//bc1->setMpMax(10);
	//bc1->setMpNow(10);
	//bc1->setName("enemy");
	//bc1->setSpeed(10);
	//Enemy* mesh3 = new Enemy("moster.blend.x");
	//mesh3->setIsWithAnimation(true);
	//mesh3->loadModel(pD3DDevice);
	//mesh3->setWalkSpeed(0.05f);
	//mesh3->setMaxSpeed(0.05f);
	//mesh3->setCanMove(true);
	//mesh3->setVecNowPos(new D3DXVECTOR3(1, 0, 1));
	//mesh3->setVecPatrolStart(new D3DXVECTOR3(1, 0, 1));
	//mesh3->setVecPatrolEnd(new D3DXVECTOR3(1, 0, 20));
	//mesh3->setOverlapLevel(1);
	//mesh3->setBattleChara(bc1);
	//mesh3->setTrackingRadius(10);
	//mesh3->setBattleRadius(5);
	//enemys.push_back(mesh3);
	//map->addGameObject(mesh3);

	BattleChara* bc3 = new BattleChara();
	bc3->setAtk(10);
	bc3->setCamp(CampType::CampTypeEnemy);
	bc3->setHpMax(10);
	bc3->setHpNow(10);
	bc3->setMovePoint(30);
	bc3->setMpMax(10);
	bc3->setMpNow(10);
	bc3->setName("enemy2");
	bc3->setSpeed(10);
	Enemy* mesh9 = new Enemy("moster.blend.x");
	mesh9->setIsWithAnimation(true);
	mesh9->loadModel(pD3DDevice);
	mesh9->setWalkSpeed(0.05f);
	mesh9->setMaxSpeed(0.05f);
	mesh9->setCanMove(true);
	mesh9->setVecNowPos(new D3DXVECTOR3(-30, 0, -85));
	mesh9->setVecPatrolStart(new D3DXVECTOR3(0, 0, -85));
	mesh9->setVecPatrolEnd(new D3DXVECTOR3(-30, 0, -85));
	mesh9->setOverlapLevel(1);
	mesh9->setBattleChara(bc3);
	mesh9->setTrackingRadius(10);
	mesh9->setBattleRadius(5);
	enemys.push_back(mesh9);
	map->addGameObject(mesh9);


	//BattleChara* bc2 = new BattleChara();
	//bc2->setAtk(10);
	//bc2->setCamp(CampType::CampTypeEnemy);
	//bc2->setHpMax(10);
	//bc2->setHpNow(10);
	//bc2->setMovePoint(30);
	//bc2->setMpMax(10);
	//bc2->setMpNow(10);
	//bc2->setName("enemy1");
	//bc2->setSpeed(10);
	//Enemy* enemy4 = new Enemy("moster.blend.x");
	////Enemy* enemy4 = new Enemy("funtest.x");
	//enemy4->setIsWithAnimation(true);
	//enemy4->loadModel(pD3DDevice);
	//enemy4->setWalkSpeed(0.05f);
	//enemy4->setMaxSpeed(0.05f);
	//enemy4->setCanMove(true);
	//enemy4->setVecNowPos(new D3DXVECTOR3(13, 0, 10));
	//enemy4->setVecPatrolStart(new D3DXVECTOR3(13, 0, 1));
	//enemy4->setVecPatrolEnd(new D3DXVECTOR3(13, 0, 20));
	//enemy4->setOverlapLevel(1);
	//enemy4->setBattleChara(bc2);
	//enemy4->setTrackingRadius(10);
	//enemy4->setBattleRadius(5);
	//enemys.push_back(enemy4);
	//map->addGameObject(enemy4);


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
		else
		{
			if (checkIsInBattle())
			{
				if (battle->getBattleState() != BattleState::BattleStateMapMove)
				{
					int enemyNum = enemys.size();
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
		animationUpdate();
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
		//setIsFade(0);
		gs = GameState::GameStateGameClean;
	}
}

void GameManage::gameStateClean(void)
{
	int gameObjectsNum = others.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		SAFE_DELETE(others[i]);
	}
	gameObjectsNum = vigliances.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		SAFE_DELETE(vigliances[i]);
	}
	gameObjectsNum = enemys.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		SAFE_DELETE(enemys[i]);
	}
	gameObjectsNum = uis.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		SAFE_DELETE(uis[i]);
	}
	safe_delete<Player>(player);

	enemys.clear();
	others.clear();
	vigliances.clear();
	uis.clear();
	//safe_delete<Battle>(battle);

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
		//setIsFade(0);
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
	else if(enemys.size() <= 0)
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
}

void GameManage::enemyUpdate(void)
{
	int enemyNum = enemys.size();
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
	vector<GameObject*> battleList = map->calObjectInCycle(enemy->getBoundingCenter(), enemy->getBattleRadius());
	int battleListNum = battleList.size();
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
	//enemy->setVecPatrolTarget(NULL);
	enemy->setIsTracking(false);
}

void GameManage::animationUpdate(void)
{
	am.play();
	am.cleanEndAnimation();
}

void GameManage::othersUpdate(void)
{
	if (!checkIsInBattle())
	{
		int othersNum = others.size();
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
		Player* pointMesh = new Player("face.x");
		pointMesh->setIsWithAnimation(false);
		pointMesh->loadModel(pD3DDevice);
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
		//billboard->setVecScale(new D3DXVECTOR3(5, 5, 5));
		others.push_back(billboard);
		map->addGameObject(billboard);

		battle = new Battle(map, &pm, cmdMeum, textBox, statusBox, pointMesh);
		addCharaToBattle(battle, player);
		battle->setSkillBillboard(billboard);
		//battle->addCharas(player);
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
		//billboard->setVecScale(new D3DXVECTOR3(5, 5, 5));
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
		player->setIsPlayAnimation(false);
	}
	int gameObjectsNum = enemys.size();
	for (int i = 0; i < gameObjectsNum; i++)
	{
		if (actor == enemys[i])
		{
			continue;
		}
		enemys[i]->lockThisTurn();
		enemys[i]->setIsPlayAnimation(false);
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
