#include "stdafx.h"
#include "Number.h"
#include "sprite.h"
#include "texture.h"

Number::Number()
{
}

Number::~Number()
{
}

void Number::Draw(int number, int digit, D3DXVECTOR2 position, float scale)
{
	int texture_width = Texture_GetWidth(TEX_NUMBER) / 10;
	int texture_height = Texture_GetHeight(TEX_NUMBER);
	int value = 0;
	long long digit_value = 1;
	int padding = 0;

	for (int i = 0; i < digit; i++) {
		digit_value *= 10;
	}
	for (int i = 0; i < digit; i++) {
		value = number / digit_value % 10;
		Sprite_Draw_Size(TEX_NUMBER, position.x + padding, position.y, texture_width * scale, texture_height * scale, texture_width * value, 0, texture_width, texture_height);
		padding += texture_width * scale;
		digit_value /= 10;
	}
}

