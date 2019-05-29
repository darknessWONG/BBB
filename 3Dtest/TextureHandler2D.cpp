#include "stdafx.h"
#include "TextureHandler2D.h"
#include "debugPrintf.h"
#include <fstream>


vector<Texture> TextureHandler2D::textures;

TextureHandler2D::TextureHandler2D()
{
}


TextureHandler2D::~TextureHandler2D()
{
}

void TextureHandler2D::LoadTextures(LPDIRECT3DDEVICE9 g_pD3DDevice)
{
	int texturesNum = (int)textures.size();
	for (int i = 0; i < texturesNum; i++)
	{
		if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, textures[i].paths.c_str(), &textures[i].tex_p)))
		{
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

void TextureHandler2D::AddTextureBatch(string batchFile)
{
	fstream f(batchFile);
	string file;
	int width, height;
	while (f >> file >> width >> height)
	{
		AddTexture(file, width, height);
	}
}

Texture TextureHandler2D::GetTexture(int index)
{
	return textures[index];
}
