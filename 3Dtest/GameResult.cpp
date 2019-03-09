#include "stdafx.h"
#include "GameResult.h"
#include "gamepad.h"

GameResult::GameResult()
{
	bEnd = false;

	texture_background = TEX_RESULT1;

	gColor = 0xffffffff;
	counter = 0;
	increment = 1;
	pParticle = new Particle2D();

	// temp
	grade = 0;
}

GameResult::~GameResult()
{
	delete pParticle;
	pParticle = NULL;
}

void GameResult::Update()
{
	if (Keyboard_IsTrigger(DIK_RETURN) || Gamepad_isTrigger(XINPUT_GAMEPAD_START) || Gamepad_isTrigger(XINPUT_GAMEPAD_A)) {
		bEnd = true;
	}

	counter += increment;
	gColor.a = (float)counter / 60;
	if (counter == 90 || counter == 0) {
		pParticle->Spawn(1);
		increment = -increment;
	}
}

void GameResult::Draw()
{
	Sprite_Draw_Background(texture_background);
	pParticle->Draw();
}

bool GameResult::isEnd()
{
	return bEnd;
}