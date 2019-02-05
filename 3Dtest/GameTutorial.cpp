#include "stdafx.h"
#include "GameTutorial.h"

#define TEXTURE_BACKGROUND_PADDING	(20)

GameTutorial::GameTutorial()
{
	bEnd = false;

	texture_background = TEX_NONE;

}

GameTutorial::~GameTutorial()
{
}

void GameTutorial::Update()
{
	if (Keyboard_IsTrigger(DIK_RETURN)) {
		bEnd = true;
	}
}

void GameTutorial::Draw()
{
	Sprite_Draw_Background(texture_background);
}

bool GameTutorial::isEnd()
{
	return bEnd;
}