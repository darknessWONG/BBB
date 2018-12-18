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
	mesh->Release();
	mesh = NULL;
	adacencyBuffer->Release();
	adacencyBuffer = NULL;

	for (int i = 0; i < numMaterials; i++)
	{
		if (meshTexture[i] != NULL)
		{
			meshTexture[i]->Release();
			meshTexture[i] = NULL;
		}
	}
	delete[] meshColor;
	meshColor = NULL;
	delete[] meshTexture;
	meshTexture = NULL;

	materials = NULL;
}

void Model::dataUpdate(void)
{
	calBoundingBox();
	GameObject::dataUpdate();
}

void Model::draw(LPDIRECT3DDEVICE9 pD3DDevice)
{
	pD3DDevice->SetFVF(FVF_VERTEX3D);
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

	boxMesh->Release();
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

RECTF Model::getBoundingRect(void)
{
	RECTF rect;
	float maxX = Physics::round(boundingBoxMax.x, FLOAT_BITS);
	float minX = Physics::round(boundingBoxMin.x, FLOAT_BITS);
	float maxZ = Physics::round(boundingBoxMax.z, FLOAT_BITS);
	float minZ = Physics::round(boundingBoxMin.z, FLOAT_BITS);
	float posX = Physics::round(getVecNowPos()->x, FLOAT_BITS);
	float posZ = Physics::round(getVecNowPos()->z, FLOAT_BITS); 

	//rect.left = (float)((double)boundingBoxMin.x + (double)getVecNowPos()->x);
	//rect.right = (float)((double)boundingBoxMax.x + (double)getVecNowPos()->x);
	//rect.top = (float)((double)boundingBoxMax.z + (double)getVecNowPos()->z);
	//rect.bottom = (float)((double)boundingBoxMin.z + (double)getVecNowPos()->z);
	rect.left = minX + posX;
	rect.right = maxX + posX;
	rect.top = maxZ + posZ;
	rect.bottom = minZ + posZ;
	return rect;
}

D3DXVECTOR2 Model::getBoundingCenter(void)
{
	RECTF rect = getBoundingRect();
	D3DXVECTOR2 center = { 0, 0 };
	center.x = Physics::round((rect.left + rect.right) / 2, FLOAT_BITS);
	center.y = Physics::round((rect.bottom + rect.top) / 2, FLOAT_BITS);
	return center;
}

void Model::setBoundingCenter(D3DXVECTOR2 center)
{
	D3DXVECTOR2 boundingCenter = getBoundingCenter();
	D3DXVECTOR3 nowPos = *getVecNowPos();
	D3DXVECTOR2 offset = { nowPos.x - boundingCenter.x, nowPos.z - boundingCenter.y };

	nowPos = { center.x + offset.x, nowPos.y, center.y + offset.y };
	setVecNowPos(&nowPos);
}
