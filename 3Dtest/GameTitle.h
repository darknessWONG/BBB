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

	int counter;				// alphaとballoonがだすためのフラックス
	int increment;				// counter が増やす値
	Particle2D *pParticle;
	D3DXCOLOR gColor;			// start iconのdiffuse color

	// texture index
	int texture_logo;
	int texture_background;
	int texture_startgame;
};