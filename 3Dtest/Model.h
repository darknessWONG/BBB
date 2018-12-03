#pragma once
#include "stdafx.h"
#include "GameObject.h"
class Model :
	public GameObject
{
public:
	Model();
	Model(string modelPath);
	virtual ~Model();
	/*===========================================
	virtual member
	============================================*/
	virtual void dataUpdate(void);
	virtual void draw(LPDIRECT3DDEVICE9 pD3DDevice);
	virtual RECTF getBoundingRect(void);
	virtual D3DXVECTOR2 getBoundingCenter(void);
	virtual void setBoundingCenter(D3DXVECTOR2 center);

	/*===========================================
	public function
	============================================*/
	void loadModel(LPDIRECT3DDEVICE9 pD3DDevice);
	void calBoundingBox(void);

	/*===========================================
	public geter / seter
	============================================*/
	string getModelPath(void);
	void setModelPath(string modelPath);
	D3DXVECTOR3 getBoundingBoxMin(void);
	D3DXVECTOR3 getBoundingBoxMax(void);

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

	D3DXVECTOR3 boundingBoxMin;
	D3DXVECTOR3 boundingBoxMax;

	//D3DXVECTOR3 boundingSphereCenter;
	//float boundingSphereRadius;
};

