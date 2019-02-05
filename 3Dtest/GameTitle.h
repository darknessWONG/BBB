#pragma once

#include "stdafx.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "Common.h"
#include "Particle2D.h"

class GameTitle
{
public:
	GameTitle();
	~GameTitle();

	void Update();
	void Draw();

	bool isEnd();	// check is title flag is end or not
private:
	// scene end flag
	bool bEnd;

	int counter;				// alpha��balloon���������߂̃t���b�N�X
	int increment;				// counter �����₷�l
	Particle2D *pParticle;
	D3DXCOLOR gColor;			// start icon��diffuse color

	// texture index
	int texture_logo;
	int texture_background;
	int texture_startgame;
};