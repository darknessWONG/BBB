#include "stdafx.h"
#include "Model.h"
#include "Common.h"

Model::Model()
{

}

Model::Model(string modelPath)
{
	this->modelPath = modelPath;
}


Model::~Model()
{
}

void Model::draw(LPDIRECT3DDEVICE9 pD3DDevice)
{
	pD3DDevice->SetTransform(D3DTS_WORLD, getMtxWorld());
	for (int i = 0; i < numMaterials; i++)
	{
		pD3DDevice->SetMaterial(&meshMat[i]);
		pD3DDevice->SetTexture(0, meshTexture[i]);
		mesh->DrawSubset(i);
	}
}

void Model::loadModel(LPDIRECT3DDEVICE9 pD3DDevice)
{
	if (modelPath == "")
	{
		return;
	}

	//material buffer
	LPD3DXBUFFER mtrlBuffer = NULL;

	HRESULT hr = D3DXLoadMeshFromX(modelPath.c_str(), D3DXMESH_MANAGED, pD3DDevice, &adacencyBuffer, &mtrlBuffer, NULL, &numMaterials, &mesh);
	if (FAILED(hr))
	{
		return;
	}

	meshColor = new D3DCOLORVALUE[numMaterials];
	meshTexture = new LPDIRECT3DTEXTURE9[numMaterials];
	meshMat = new D3DMATERIAL9[numMaterials];
	materials = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

	for (int i = 0; i < numMaterials; i++)
	{
		meshMat[i] = materials[i].MatD3D;
		meshColor[i] = materials[i].MatD3D.Diffuse;

		if (materials[i].pTextureFilename == NULL)
		{
			meshTexture[i] = NULL;
		}
		else
		{
			hr = D3DXCreateTextureFromFile(pD3DDevice, materials[i].pTextureFilename, &meshTexture[i]);
		}
	}

	if (mtrlBuffer != NULL)
	{
		mtrlBuffer->Release();
	}
}

string Model::getModelPath(void)
{
	return modelPath;
}

void Model::setModelPath(string modelPath)
{
	this->modelPath = modelPath;
}
