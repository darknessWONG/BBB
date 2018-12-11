#include "stdafx.h"
#include "GameResult.h"

GameResult::GameResult()
{
	bEnd = false;

	texture_background = 0;
}

GameResult::~GameResult()
{
}

void GameResult::Update()
{
	if (Keyboard_IsTrigger(DIK_RETURN)) {
		bEnd = true;
	}
}

void GameResult::Draw()
{
	Sprite_Draw_Background(texture_background);
}

bool GameResult::isEnd()
{
	return bEnd;
}