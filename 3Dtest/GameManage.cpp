#include "stdafx.h"
#include "GameManage.h"
#include "Model.h"
#include "input.h"


GameManage::GameManage()
{
	state = GameState::GameState_title_state_init;
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
	D3DXVECTOR3* cameraPos = new D3DXVECTOR3(0, 20, -20);
	D3DXVECTOR3* cameraWatchAt = new D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3* cameraUp = new D3DXVECTOR3(0, 1, 0);
	camera = new Camera(cameraPos, cameraWatchAt, cameraUp);

	light = new Light();
	light->init(pD3DDevice);
}

void GameManage::update(void)
{
	// past
	camera->dataUpdate();
	camera->calWatchAt();
	camera->calWorldMatrix();
	camera->draw(pD3DDevice);

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->dataUpdate();
		gameObjects[i]->calWorldMatrix();
	}

	switch (state)
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
}

void GameManage::draw(void)
{
	light->lightSet(pD3DDevice);
	camera->draw(pD3DDevice);
	
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->draw(pD3DDevice);
	}
}

void GameManage::release(void)
{
}

void GameManage::title_state_init(void)
{
	state = GameState_title_state_running;
}

void GameManage::title_state_update(void)
{
	state = GameState_title_state_clean;
}

void GameManage::title_state_clean(void)
{
	state = GameState_tutorial_state_init;
}

void GameManage::tutorial_state_init(void)
{
	state = GameState_tutorial_state_running;
}

void GameManage::tutorial_state_update(void)
{
	state = GameState_tutorial_state_clean;
}

void GameManage::tutorial_state_clean(void)
{
	state = GameState_game_state_init;
}

void GameManage::game_state_init(void)
{
	Model* mesh = new Model("radio.x");
	mesh->loadModel(pD3DDevice);
	mesh->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	mesh->setRotateSpeed(3);

	gameObjects.push_back(mesh);

	state = GameState_game_state_running;
}

void GameManage::game_state_update(void)
{
	state_read_input(GameState_game_state_clean);
	//state = GameState_game_state_clean;
}

void GameManage::game_state_clean(void)
{
	int idx = gameObjects.size();
	for (int i = 0; i < idx; i++)
	{
		// TODO
		GameObject* ptemp = gameObjects[idx - i - 1];
		gameObjects.pop_back();
		delete ptemp;
	}

	state = GameState_result_state_init;
}

void GameManage::result_state_init(void)
{
	state = GameState_result_state_running;
}

void GameManage::result_state_update(void)
{
	state = GameState_result_state_clean;
}

void GameManage::result_state_clean(void)
{
	state = GameState_naming_state_init;
}

void GameManage::naming_state_init(void)
{
	state = GameState_naming_state_running;
}

void GameManage::naming_state_update(void)
{
	state = GameState_naming_state_clean;
}

void GameManage::naming_state_clean(void)
{
	state = GameState_ranking_state_init;
}

void GameManage::ranking_state_init(void)
{
	state = GameState_ranking_state_running;
}

void GameManage::ranking_state_update(void)
{
	state = GameState_ranking_state_clean;
}

void GameManage::ranking_state_clean(void)
{
	state = GameState_title_state_init;
}

void GameManage::setPD3DDevice(LPDIRECT3DDEVICE9 pD3DDevice)
{
	this->pD3DDevice = pD3DDevice;
}

void GameManage::state_read_input(GameState name)
{
	if (Keyboard_IsPress(DIK_SPACE))
	{
		state = name;
	}
}
