#include "stdafx.h"
#include "GameTitle.h"

GameTitle::GameTitle()
{
	bEnd = false;

	texture_logo = 0;
	texture_background = 0;
	texture_startgame = 0;				
	texture_cursor = 0;					// TODO
}

GameTitle::~GameTitle()
{
}

void GameTitle::Update()
{
	if (Keyboard_IsTrigger(DIK_RETURN)) {
		bEnd = true;
	}
}

void GameTitle::Draw()
{
	Sprite_Draw_Background(texture_background);
	Sprite_Draw_Size(texture_logo, Common::screen_width * 0.5f, Common::screen_height * 0.2f, 300, 100);
	Sprite_Draw_Size(texture_startgame, Common::screen_width * 0.5f, Common::screen_height * 0.8f, 200, 50);
}

bool GameTitle::isEnd()
{
	return bEnd;
}