#include "stdafx.h"
#include "GameTitle.h"

GameTitle::GameTitle()
{
	bEnd = false;

	gColor = 0xffffffff;
	counter = 0;
	increment = 1;
	pParticle = new Particle2D();

	texture_logo = TEX_LOGO;
	texture_background = TEX_RESULT;
	texture_startgame = TEX_START;
}

GameTitle::~GameTitle()
{
}

void GameTitle::Update()
{
	if (Keyboard_IsTrigger(DIK_RETURN)) {
		bEnd = true;
	}
	counter += increment;
	gColor.a = (float)counter / 30;
	if (counter == 60 || counter == 0) {
		pParticle->Spawn(1);
		increment = -increment;
	}

	pParticle->Update();
}

void GameTitle::Draw()
{
	Sprite_Draw_Background(texture_background, 0, 562 * 2 + 40, 980, 562 - 40 );			// ちょっと画像の問題の解決ため計算している
	pParticle->Draw();
	Sprite_Draw_Size(texture_logo, Common::screen_width * 0.5f, Common::screen_height * 0.3f, 600, 250);
	Sprite_Draw_Size(texture_startgame, Common::screen_width * 0.5f, Common::screen_height * 0.7f, 200, 50, gColor);
}

bool GameTitle::isEnd()
{
	return bEnd;
}