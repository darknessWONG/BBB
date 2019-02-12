#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "stdafx.h"

enum {
	TEX_LOGO,
	TEX_RESULT,
	TEX_START,
	TEX_NUMBER,
	TEX_BALLOON,
	TEX_MARRY,
	TEX_ROLLER,
	TEX_FERRIS,
	TEX_VIKING,
	TEX_NONE,
	TEX_WOOD,
	TEX_IRON,
	TEX_BRICK,
	TEX_GUAGE,
	TEX_ORDER_BG,
	TEX_MAX
};

int Texture_Load(void);

void Texture_Release(void);

LPDIRECT3DTEXTURE9 Texture_GetTexture(int index);

int Texture_GetWidth(int index);

int Texture_GetHeight(int index);

#endif TEXTURE_H_