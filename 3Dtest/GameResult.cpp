#include "stdafx.h"
#include "GameResult.h"
#include "gamepad.h"

#define SCORE_PER_GRADE	(5000)
#define MAX_GRADE		(5)
#define MIN_GRADE		(0)

GameResult::GameResult()
{
	bEnd = false;

	texture_background = TEX_RESULT1;

	gColor = 0xffffffff;
	counter = 0;
	increment = 1;
	pParticle = new Particle2D();

	setScore(0);
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

void GameResult::setScore(int number)
{
	score = number;

	grade = score / SCORE_PER_GRADE;
	grade = min(grade, MAX_GRADE);
	grade = max(grade, MIN_GRADE);

	texture_background = TEX_RESULT1 + grade;
}

bool GameResult::isEnd()
{
	return bEnd;
}