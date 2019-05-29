#pragma once

#ifndef ROUNDSHADOWHANDLER
#define ROUNDSHADOWHANDLER
#endif

class RoundShadowHandler
{
public:
	RoundShadowHandler();
	~RoundShadowHandler();

	/*===========================================
	virtual member
	============================================*/
	static void draw(LPDIRECT3DDEVICE9 pD3DDevice);


	/*===========================================
	static function
	============================================*/
	static void init(LPDIRECT3DDEVICE9 pD3DDevice, int textureIndex);
	static void setTextureIndex(int textureIndex);
	static void addPos(D3DXVECTOR2 pos);
private:
	static vector<D3DXVECTOR2> pos;

	static int textureIndex;
	static Vertex3D point[4];
	static WORD index[6];

	static LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
	static LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
};

