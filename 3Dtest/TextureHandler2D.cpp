#include "stdafx.h"
#include "TextureHandler2D.h"
#include "debugPrintf.h"


vector<Texture> TextureHandler2D::textures;

TextureHandler2D::TextureHandler2D()
{
}


TextureHandler2D::~TextureHandler2D()
{
}

void TextureHandler2D::LoadTextures(LPDIRECT3DDEVICE9 g_pD3DDevice)
{
	for (int i = 0; i < textures.size(); i++)
	{
		if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, textures[i].paths.c_str(), &textures[i].tex_p)))
		{
			//FaultLog("open texture failed");
		}
	}
}

void TextureHandler2D::AddTexture(string path, float width, float height)
{
	Texture tex;
	tex.tex_p = NULL;
	tex.paths = path;
	tex.width = width;
	tex.height = height;
	textures.push_back(tex);
}

Texture TextureHandler2D::GetTexture(int index)
{
	return textures[index];
}