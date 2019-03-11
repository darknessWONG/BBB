#include "stdafx.h",
#include "GameTitle.h"
#include "gamepad.h"


GameTitle::GameTitle()
{
	bEnd = false;

	gColor = 0xffffffff;
	counter = 0;
	increment = 1;
	pParticle = new Particle2D();

	texture_logo = TEX_LOGO;
	texture_background = TEX_RESULT6;
	texture_startgame = TEX_START;
}

GameTitle::~GameTitle()
{
	delete pParticle;
	pParticle = NULL;
}

void GameTitle::Update()
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

	pParticle->Update();
}

void GameTitle::Draw()
{
	Sprite_Draw_Background(texture_background);
	pParticle->Draw();
	Sprite_Draw_Size(texture_logo, Common::screen_width * 0.5f, Common::screen_height * 0.25f, 600, 428);
	Sprite_Draw_Size(texture_startgame, Common::screen_width * 0.5f, Common::screen_height * 0.7f, 200, 50, gColor);
}

bool GameTitle::isEnd()
{
	return bEnd;
}