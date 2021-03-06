#include <stdio.h>

#include "stdafx.h"
#include "texture.h"
#include "Common.h"

#define TEXTURE_FILENAME_MAX (64)
//#define

typedef struct TextureFileData_tag {
	//LPDIRECT3DTEXTURE9 pTexture;
	const char filename[TEXTURE_FILENAME_MAX];
	int width;
	int height;
}TextureFileData;

static const TextureFileData TEXTURE_FILES[] = {
	{ "asset/sprite/logo.png", 800, 571 },
	{ "asset/sprite/result1.png", 1240, 729 },
	{ "asset/sprite/result2.png", 1240, 729 },
	{ "asset/sprite/result3.png", 1240, 729 },
	{ "asset/sprite/result4.png", 1240, 729 },
	{ "asset/sprite/result5.png", 1240, 729 },
	{ "asset/sprite/result6.png", 1240, 729 },
	{ "asset/sprite/start.png", 600, 100 },
	{ "asset/sprite/fail.png", 1000, 200 },
	{ "asset/sprite/limit_time.png", 1000, 200 },
	{ "asset/sprite/kusa.png", 200, 133 },
	{ "asset/sprite/hew_tutorial.png", 700, 412 },
	{ "asset/sprite/number.png", 728, 95 },
	{ "asset/sprite/balloon.png", 1218, 3059 },
	{ "asset/sprite/marry.png", 1583, 2155 },
	{ "asset/sprite/roller.png", 2666, 1488 },
	{ "asset/sprite/ferris.png", 1889, 1974 },
	{ "asset/sprite/viking.png", 2116, 2099 },
	{ "asset/sprite/none.png", 100, 100 },
	{ "asset/sprite/wood.png", 256, 256 },
	{ "asset/sprite/iron.jpg", 256, 256 },
	{ "asset/sprite/brick.jpg", 256, 256 },
	{ "asset/sprite/guage.png", 1190, 175 },
	{ "asset/sprite/crystal.png", 256, 256 },
};

static const int TEXTURE_MAX = sizeof(TEXTURE_FILES) / sizeof(TEXTURE_FILES[0]);

static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_MAX];

static HRESULT hr;

int Texture_Load(void) {

	int failed_count = 0;

	for (int i = 0; i < TEXTURE_MAX; i++) {
		hr = D3DXCreateTextureFromFile(Common::g_pD3DDevice, TEXTURE_FILES[i].filename, &g_pTextures[i]);
		if (FAILED(hr)) {
			failed_count++;
		}
	}
	return failed_count;
}

void Texture_Release(void) {
	for (int i = 0; i < TEXTURE_MAX; i++) {
		if (g_pTextures[i] != NULL) {
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}

LPDIRECT3DTEXTURE9 Texture_GetTexture(int index) {
	return g_pTextures[index];
}


int Texture_GetWidth(int index) {
	return TEXTURE_FILES[index].width;
}

int Texture_GetHeight(int index) {
	return TEXTURE_FILES[index].height;
}
