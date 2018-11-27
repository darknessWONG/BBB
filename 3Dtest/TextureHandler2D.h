#pragma once
#include <d3dx9.h>
#include "stdafx.h"

typedef struct
{
	LPDIRECT3DTEXTURE9 tex_p = NULL;
	string paths = "";
	float width = 0;
	float height = 0;
}Texture;

class TextureHandler2D
{
public:
	TextureHandler2D();
	~TextureHandler2D();

	static void LoadTextures(LPDIRECT3DDEVICE9 g_pD3DDevice);
	static void AddTexture(string path, float width, float height);
	static Texture GetTexture(int index);
private:
	static vector<Texture> textures;
};

