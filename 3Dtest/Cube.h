#pragma once
#include "Shape.h"
class Cube :
	public Shape
{
public:
	Cube();
	~Cube();

	/*===========================================
	virtual member
	============================================*/
	virtual void draw(LPDIRECT3DDEVICE9 pD3DDevice);
	virtual void setMtxWorld(D3DXMATRIX mtxWorld);
	/*===========================================
	public function
	============================================*/

	/*===========================================
	public geter / seter
	============================================*/

	/*===========================================
	static public function
	============================================*/
	//This function should be called once before this call first time be instanced
	static void initStaticMember(LPDIRECT3DDEVICE9 pD3DDevice);
private:
	D3DXMATRIX mtxWorld;



	static Vertex3D cubeVertex[CUBE_VERTEX_NUM];
	static WORD cubeIndex[CUBE_INDEX_NUM];
	static LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
	static LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
};