#pragma once

#include "stdafx.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "Common.h"

class GameTutorial
{
public:
	GameTutorial();
	~GameTutorial();

	void Update();
	void Draw();

	bool isEnd();	// check is tutorial flag is end or not
private:
	// scene end flag
	bool bEnd;

	// texture index
	int texture_background;

};