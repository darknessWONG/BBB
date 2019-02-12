#pragma once

#include "stdafx.h"

class Number
{
public:
	Number();
	~Number();

	// spriteで切り取って、数字を表示
	static void Draw(int number, int digit, D3DXVECTOR2 position, float scale);	// 数字 | 桁数 | 差表 | サイス 

private:

};
