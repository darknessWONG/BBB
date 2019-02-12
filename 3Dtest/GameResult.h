#pragma once

#include "stdafx.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "Common.h"
#include "Particle2D.h"

class GameResult
{
public:
	GameResult();
	~GameResult();

	void Update();
	void Draw();

	bool isEnd();	// check is result flag is end or not
private:
	// scene end flag
	bool bEnd;

	// texture index
	int texture_background;

	int counter;				// alpha��balloon���������߂̃t���b�N�X
	int increment;				// counter �����₷�l
	Particle2D *pParticle;
	D3DXCOLOR gColor;			// start icon��diffuse color

	// result grade
	int grade;
};