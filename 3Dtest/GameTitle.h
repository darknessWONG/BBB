#pragma once

#include "stdafx.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "Common.h"

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

	// texture index
	int texture_logo;
	int texture_background;
	int texture_startgame;
	int texture_cursor;
};