#pragma once
#include "stdafx.h"
#include "GameObject.h"
class Model :
	public GameObject
{
public:
	Model();
	Model(string modelPath);
	~Model();
	/*===========================================
	virtual member
	============================================*/
	virtual void draw(LPDIRECT3DDEVICE9 pD3DDevice);

	/*===========================================
	public function
	============================================*/
	void loadModel(LPDIRECT3DDEVICE9 pD3DDevice);

	/*===========================================
	public geter / seter
	============================================*/
	string getModelPath(void);
	void setModelPath(string modelPath);

private:

	string modelPath;

	//mesh
	LPD3DXMESH mesh = NULL;
	//adacency buffer
	LPD3DXBUFFER adacencyBuffer = NULL;
	//number of material
	DWORD numMaterials = 0;

	//array of material 
	D3DCOLORVALUE *meshColor = NULL;
	LPDIRECT3DTEXTURE9 *meshTexture = NULL;

	//pointer of material buffer
	D3DXMATERIAL *materials = NULL;

	D3DMATERIAL9 *meshMat = NULL;
};

