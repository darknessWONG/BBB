#include "stdafx.h"
#include "GameTutorial.h"
#include "gamepad.h"

#define TEXTURE_BACKGROUND_PADDING	(20)

GameTutorial::GameTutorial()
{
	bEnd = false;

	texture_background = TEX_TUTORIAL;

}

GameTutorial::~GameTutorial()
{
}

void GameTutorial::Update()
{
	if (Keyboard_IsTrigger(DIK_RETURN) || Gamepad_isTrigger(XINPUT_GAMEPAD_START) || Gamepad_isTrigger(XINPUT_GAMEPAD_A)) {
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