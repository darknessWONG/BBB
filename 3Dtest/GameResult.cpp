#include "stdafx.h"
#include "GameResult.h"

#define TEXTURE_BACKGROUND_PADDING	(20)

GameResult::GameResult()
{
	bEnd = false;

	texture_background = TEX_RESULT;

	gColor = 0xffffffff;
	counter = 0;
	increment = 1;
	pParticle = new Particle2D();

	// temp
	grade = 0;
}

GameResult::~GameResult()
{
}

void GameResult::Update()
{
	if (Keyboard_IsTrigger(DIK_RETURN)) {
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
	Sprite_Draw_Background(texture_background,grade % 2 * (1000 + TEXTURE_BACKGROUND_PADDING), grade / 2 * (562 + TEXTURE_BACKGROUND_PADDING), 1000 - TEXTURE_BACKGROUND_PADDING, 570 - TEXTURE_BACKGROUND_PADDING);
	pParticle->Draw();
}

bool GameResult::isEnd()
{
	return bEnd;
}