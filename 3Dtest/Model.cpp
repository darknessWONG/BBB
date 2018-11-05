#include "stdafx.h"
#include "Model.h"
#include "Common.h"

Model::Model()
{
	boundingBoxMin = { 0.0f, 0.0f, 0.0f };
	boundingBoxMax = { 0.0f, 0.0f, 0.0f };
}

Model::Model(string modelPath)
{
	this->modelPath = modelPath;
	boundingBoxMin = { 0.0f, 0.0f, 0.0f };
	boundingBoxMax = { 0.0f, 0.0f, 0.0f };
}


Model::~Model()
{
}

void Model::dataUpdate(void)
{
	calBoundingBox();
	GameObject::dataUpdate();
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

#ifdef _DEBUG
	D3DMATERIAL9 blue;
	blue.Diffuse = { 1.0f, 1.0f, 1.0f, 0.5f };
	blue.Ambient = blue.Diffuse;
	pD3DDevice->SetMaterial(&blue);
	pD3DDevice->SetTexture(0, 0); // disable texture

	LPD3DXMESH boxMesh;

	D3DXMATRIX mtxBoxWorld = *getMtxWorld();
	mtxBoxWorld._42 += (boundingBoxMax.y - boundingBoxMin.y) / 2;

	D3DXCreateBox(pD3DDevice, boundingBoxMax.x - boundingBoxMin.x, boundingBoxMax.y - boundingBoxMin.y, boundingBoxMax.z - boundingBoxMin.z, &boxMesh, 0);
	//D3DXCreateSphere(pD3DDevice, boundingSphereRadius, 20, 20, &sphereMesh, 0);
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxBoxWorld);
	boxMesh->DrawSubset(0);
#endif
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
		meshMat[i].Ambient = materials[i].MatD3D.Diffuse;

		if (materials[i].pTextureFilename == NULL)
		{
			meshTexture[i] = NULL;
		}
		else
		{
			hr = D3DXCreateTextureFromFile(pD3DDevice, materials[i].pTextureFilename, &meshTexture[i]);
		}
	}

	calBoundingBox();

	if (mtrlBuffer != NULL)
	{
		mtrlBuffer->Release();
	}


}

void Model::calBoundingBox(void)
{
	BYTE* v = 0;
	mesh->LockVertexBuffer(0, (void**)&v);

	int num = mesh->GetNumVertices();
	D3DXComputeBoundingBox((D3DXVECTOR3*)v, num, D3DXGetFVFVertexSize(mesh->GetFVF()), &boundingBoxMin, &boundingBoxMax);
	//D3DXComputeBoundingSphere((D3DXVECTOR3*)v, num, D3DXGetFVFVertexSize(mesh->GetFVF()), &boundingSphereCenter, &boundingSphereRadius);
	mesh->UnlockVertexBuffer();
}

string Model::getModelPath(void)
{
	return modelPath;
}

void Model::setModelPath(string modelPath)
{
	this->modelPath = modelPath;
}

RECT Model::getBoundingRect(void)
{
	RECT rect;
	rect.left = boundingBoxMax.x + getVecNowPos()->x;
	rect.right = boundingBoxMin.x + getVecNowPos()->x;
	rect.top = boundingBoxMin.z + getVecNowPos()->z;
	rect.bottom = boundingBoxMax.z + getVecNowPos()->z;
	return rect;
}
