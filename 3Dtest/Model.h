#pragma once
#include "GameObject.h"
class Model :
	public GameObject
{
public:
	Model();
	~Model();

private:
	//mesh
	LPD3DXMESH g_pD3DXMesh = NULL;
	//adacency buffer
	LPD3DXBUFFER g_pD3DXAdacencyBuffer = NULL;
	//number of material
	DWORD g_dwNumMaterials = 0;

	//array of material 
	D3DCOLORVALUE *g_pMeshColor = NULL;
	LPDIRECT3DTEXTURE9 *g_pMeshTexture = NULL;

	//pointer of material buffer
	D3DXMATERIAL *g_d3dxMaterials = NULL;

	D3DMATERIAL9 *g_pMeshMat = NULL;

	D3DXMATRIX *g_pModelMtxWorld = NULL;
};

