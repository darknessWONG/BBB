#include "stdafx.h"
#include "Model.h"
#include "Common.h"

Model::Model()
	: m_pAllocateHier(NULL), m_pAnimController(NULL), m_pFrameRoot(NULL), m_pBoneMatrix(NULL)
{
	boundingBoxMin = { 0.0f, 0.0f, 0.0f };
	boundingBoxMax = { 0.0f, 0.0f, 0.0f };

	isWithAnimation = false;
	isPlayAnimation = true;
}

Model::Model(string modelPath)
	: m_pAllocateHier(NULL), m_pAnimController(NULL), m_pFrameRoot(NULL), m_pBoneMatrix(NULL)

{
	this->modelPath = modelPath;
	boundingBoxMin = { 0.0f, 0.0f, 0.0f };
	boundingBoxMax = { 0.0f, 0.0f, 0.0f };

	isWithAnimation = false;
	isPlayAnimation = true;
}


Model::~Model()
{
	if (!isWithAnimation)
	{
		mesh->Release();
		mesh = NULL;
		adacencyBuffer->Release();
		adacencyBuffer = NULL;

		for (DWORD i = 0; i < numMaterials; i++)
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
	else
	{

		D3DXFrameDestroy(m_pFrameRoot, m_pAllocateHier);
		SAFE_RELEASE(m_pAnimController);
		SAFE_DELETE(m_pAllocateHier);
	}
}

void Model::dataUpdate(void)
{
	if (isWithAnimation)
	{
		boundingBoxMin = { FLT_MAX, FLT_MAX ,FLT_MAX };
		boundingBoxMax = { FLT_MIN, FLT_MIN, FLT_MIN };

		if (isPlayAnimation)
		{
			updateAnimation(0.001);
		}
	}

	calBounding();
	GameObject::dataUpdate();
}

void Model::draw(LPDIRECT3DDEVICE9 pD3DDevice)
{
	if (getIsDisplay())
	{
		if (!isWithAnimation)
		{
			pD3DDevice->SetTransform(D3DTS_WORLD, getMtxWorld());
			for (int i = 0; i < (int)numMaterials; i++)
			{
				pD3DDevice->SetMaterial(&meshMat[i]);
				pD3DDevice->SetTexture(0, meshTexture[i]);
				mesh->DrawSubset(i);
			}
		}
		else
		{
			updateFrameMatrices(m_pFrameRoot, getMtxWorld());
			drawFrame(pD3DDevice, m_pFrameRoot);
		}

#ifdef _DEBUG
		//D3DMATERIAL9 blue;
		//blue.Diffuse = { 1.0f, 1.0f, 1.0f, 0.5f };
		//blue.Ambient = blue.Diffuse;
		//pD3DDevice->SetMaterial(&blue);
		//pD3DDevice->SetTexture(0, 0); // disable texture

		//LPD3DXMESH boxMesh;

		//D3DXMATRIX mtxBoxWorld = *getMtxWorld();
		//mtxBoxWorld._42 += (boundingBoxMax.y - boundingBoxMin.y) / 2;
		//D3DXVECTOR3 scale = *getVecScale();
		//float x = (boundingBoxMax.x - boundingBoxMin.x) / scale.x;
		//float y = (boundingBoxMax.y - boundingBoxMin.y) / scale.y;
		//float z = (boundingBoxMax.z - boundingBoxMin.z) / scale.z;
		//D3DXCreateBox(pD3DDevice, x, y, z, &boxMesh, 0);
		////D3DXCreateSphere(pD3DDevice, boundingSphereRadius, 20, 20, &sphereMesh, 0);
		//pD3DDevice->SetTransform(D3DTS_WORLD, &mtxBoxWorld);
		//boxMesh->DrawSubset(0);

		//boxMesh->Release();
#endif
	}
	pD3DDevice->SetTexture(0, NULL);
}

void Model::loadModel(LPDIRECT3DDEVICE9 pD3DDevice)
{
	if (modelPath == "")
	{
		return;
	}

	//material buffer
	LPD3DXBUFFER mtrlBuffer = NULL;

	if (isWithAnimation)
	{
		m_pAllocateHier = new CAllocateHierarchy();
		HRESULT hr = D3DXLoadMeshHierarchyFromX(modelPath.c_str(), D3DXMESH_MANAGED, pD3DDevice, m_pAllocateHier, NULL, &m_pFrameRoot, &m_pAnimController);
		setupBoneMatrixPointers(m_pFrameRoot, m_pFrameRoot);

		boundingBoxMin = { FLT_MAX, FLT_MAX ,FLT_MAX };
		boundingBoxMax = { FLT_MIN, FLT_MIN, FLT_MIN };
	}
	else
	{
		HRESULT hr = D3DXLoadMeshFromX(modelPath.c_str(), D3DXMESH_MANAGED, pD3DDevice, &adacencyBuffer, &mtrlBuffer, NULL, &numMaterials, &mesh);
		if (FAILED(hr))
		{
			return;
		}

		meshColor = new D3DCOLORVALUE[numMaterials];
		meshTexture = new LPDIRECT3DTEXTURE9[numMaterials];
		meshMat = new D3DMATERIAL9[numMaterials];
		materials = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		for (DWORD i = 0; i < numMaterials; i++)
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
	}

	calBounding();

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

	D3DXVECTOR3 scale = *getVecScale();
	boundingBoxMax = { scale.x * boundingBoxMax.x, scale.y * boundingBoxMax.y, scale.z * boundingBoxMax.z };
	boundingBoxMin = { scale.x * boundingBoxMin.x, scale.y * boundingBoxMin.y, scale.z * boundingBoxMin.z };
}

void Model::calBoundingBox(LPD3DXFRAME pFrameBase, D3DXVECTOR3 &boundingBoxMin, D3DXVECTOR3 &boundingBoxMax)
{
	if (pFrameBase->pMeshContainer != NULL)
	{
		BYTE* v = 0;
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pFrameBase->pMeshContainer;
		LPD3DXMESH pMesh = pMeshContainer->MeshData.pMesh;
		D3DXVECTOR3 boxMin = { 0, 0, 0 };
		D3DXVECTOR3 boxMax = { 0, 0, 0 };

		pMesh->LockVertexBuffer(0, (void**)&v);
		int num = pMesh->GetNumVertices();
		D3DXComputeBoundingBox((D3DXVECTOR3*)v, num, D3DXGetFVFVertexSize(pMesh->GetFVF()), &boxMin, &boxMax);
		pMesh->UnlockVertexBuffer();
		
		D3DXVec3TransformCoord(&boxMax, &boxMax, &pFrameBase->TransformationMatrix);
		D3DXVec3TransformCoord(&boxMin, &boxMin, &pFrameBase->TransformationMatrix);
		D3DXVECTOR3 scale = *getVecScale();
		boxMax = { scale.x * boxMax.x, scale.y * boxMax.y, scale.z * boxMax.z };
		boxMin = { scale.x * boxMin.x, scale.y * boxMin.y, scale.z * boxMin.z };
		boundingBoxMin = Physics::takeSmallerVaule(boxMin, boundingBoxMin);
		boundingBoxMax = Physics::takebiggerVaule(boxMax, boundingBoxMax);
	}
	if (pFrameBase->pFrameSibling != NULL)
	{
		calBoundingBox(pFrameBase->pFrameSibling, boundingBoxMin, boundingBoxMax);
	}

	if (pFrameBase->pFrameFirstChild != NULL)
	{
		calBoundingBox(pFrameBase->pFrameFirstChild, boundingBoxMin, boundingBoxMax);
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

bool Model::getIsWithAnimation(void)
{
	return isWithAnimation;
}

void Model::setIsWithAnimation(bool isWithAnimation)
{
	this->isWithAnimation = isWithAnimation;
}

bool Model::getIsPlayAnimation(void)
{
	return isPlayAnimation;
}

void Model::setIsPlayAnimation(bool isPlayAnimation)
{
	this->isPlayAnimation = isPlayAnimation;
}

D3DXVECTOR2 Model::getBoundingBoxMax(void)
{
	return{ boundingBoxMax.x, boundingBoxMin.z };
}

D3DXVECTOR2 Model::getBoundingBoxMin(void)
{
	return{ boundingBoxMin.x, boundingBoxMin.z };
}

void Model::calBounding(void)
{
	if (isWithAnimation)
	{
		calBoundingBox(m_pFrameRoot, boundingBoxMin, boundingBoxMax);
	}
	else
	{
		calBoundingBox();
	}
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

BOXF Model::getBoundingBox(void)
{
	BOXF box;
	float maxX = Physics::round(boundingBoxMax.x, FLOAT_BITS);
	float minX = Physics::round(boundingBoxMin.x, FLOAT_BITS);
	float maxY = Physics::round(boundingBoxMax.y, FLOAT_BITS);
	float minY = Physics::round(boundingBoxMin.y, FLOAT_BITS);
	float maxZ = Physics::round(boundingBoxMax.z, FLOAT_BITS);
	float minZ = Physics::round(boundingBoxMin.z, FLOAT_BITS);
	float posX = Physics::round(getVecNowPos()->x, FLOAT_BITS);
	float posY = Physics::round(getVecNowPos()->y, FLOAT_BITS);
	float posZ = Physics::round(getVecNowPos()->z, FLOAT_BITS);

	box.left = minX + posX;
	box.right = maxX + posX;
	box.bottom = minY + posY;
	box.top = maxY + posY;
	box.front = minZ + posZ;
	box.back = maxZ + posZ;
	return box;
}

D3DXVECTOR2 Model::getBoundingCenter(void)
{
	RECTF rect = getBoundingRect();
	D3DXVECTOR2 center = { 0, 0 };
	center.x = Physics::round((rect.left + rect.right) / 2, FLOAT_BITS);
	center.y = Physics::round((rect.bottom + rect.top) / 2, FLOAT_BITS);
	return center;
}

D3DXVECTOR3 Model::getBoundingCenter3D(void)
{
	BOXF box = getBoundingBox();
	D3DXVECTOR3 center = { 0, 0, 0 };
	center.x = Physics::round((box.left + box.right) / 2, FLOAT_BITS);
	center.y = Physics::round((box.bottom + box.top) / 2, FLOAT_BITS);
	center.z = Physics::round((box.front + box.back) / 2, FLOAT_BITS);
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

void Model::setBoundingCenter3D(D3DXVECTOR3 center)
{
	D3DXVECTOR3 boundingCenter3D = getBoundingCenter3D();
	D3DXVECTOR3 nowPos = *getVecNowPos();
	D3DXVECTOR3 offset = { nowPos.x - boundingCenter3D.x, nowPos.y - boundingCenter3D.y, nowPos.z - boundingCenter3D.z };

	nowPos = { center.x + offset.x, center.y + offset.y, center.y + offset.y };
	setVecNowPos(&nowPos);
}

//--------------------------------------------------------------------------------------
// Name: SetupBoneMatrixPointers()
// Desc: 设置好各级框架的组合变换矩阵。
//--------------------------------------------------------------------------------------
HRESULT Model::setupBoneMatrixPointers(LPD3DXFRAME pFrameBase, LPD3DXFRAME pFrameRoot)
{
	if (pFrameBase->pMeshContainer != NULL)
	{
		D3DXFRAME_DERIVED* pFrame = NULL;
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pFrameBase->pMeshContainer;
		// if there is a skinmesh, then setup the bone matrices
		if (pMeshContainer->pSkinInfo != NULL)
		{
			UINT cBones = pMeshContainer->pSkinInfo->GetNumBones();
			pMeshContainer->ppBoneMatrixPtrs = new D3DXMATRIX*[cBones];
			for (UINT iBone = 0; iBone < cBones; iBone++)
			{
				pFrame = (D3DXFRAME_DERIVED*)D3DXFrameFind(pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(iBone));
				if (pFrame == NULL) return E_FAIL;

				pMeshContainer->ppBoneMatrixPtrs[iBone] = &pFrame->CombinedTransformationMatrix;
			}
		}
	}

	if (pFrameBase->pFrameSibling != NULL)
	{
		if (FAILED(setupBoneMatrixPointers(pFrameBase->pFrameSibling, pFrameRoot)))
			return E_FAIL;
	}

	if (pFrameBase->pFrameFirstChild != NULL)
	{
		if (FAILED(setupBoneMatrixPointers(pFrameBase->pFrameFirstChild, pFrameRoot)))
			return E_FAIL;
	}

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Name: DrawFrame()
// Desc: 绘制骨骼
//--------------------------------------------------------------------------------------
void Model::drawFrame(IDirect3DDevice9* pd3dDevice, LPD3DXFRAME pFrame)
{
	if (pFrame == NULL) return;
	LPD3DXMESHCONTAINER pMeshContainer;
	pMeshContainer = pFrame->pMeshContainer;                    // 取得网格容器
	while (pMeshContainer != NULL)
	{
		drawMeshContainer(pd3dDevice, pMeshContainer, pFrame);  // 绘制非空蒙皮网格
		pMeshContainer = pMeshContainer->pNextMeshContainer;    // 遍历所有网格容器
	}

	drawFrame(pd3dDevice, pFrame->pFrameSibling);               // 绘制兄弟框架
	drawFrame(pd3dDevice, pFrame->pFrameFirstChild);            // 绘制子框架
}

//--------------------------------------------------------------------------------------
// Name: DrawMeshContainer()
// Desc: 绘制蒙皮容器中的蒙皮网格
//--------------------------------------------------------------------------------------
void Model::drawMeshContainer(IDirect3DDevice9* pd3dDevice, LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase)
{
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
	UINT iMaterial;
	UINT NumBlend;
	UINT iAttrib;
	DWORD AttribIdPrev;
	LPD3DXBONECOMBINATION pBoneComb;

	UINT iMatrixIndex;
	D3DXMATRIXA16 matTemp;
	D3DCAPS9 d3dCaps;
	pd3dDevice->GetDeviceCaps(&d3dCaps);

	// first check for skinning
	if (pMeshContainer->pSkinInfo != NULL)
	{
		AttribIdPrev = UNUSED32;
		pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());

		// Draw using default vtx processing of the device (typically HW)
		for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
		{
			NumBlend = 0;
			for (DWORD i = 0; i < pMeshContainer->NumInfl; ++i)
			{
				if (pBoneComb[iAttrib].BoneId[i] != UINT_MAX)
				{
					NumBlend = i;
				}
			}

			if (d3dCaps.MaxVertexBlendMatrices >= NumBlend + 1)
			{
				// first calculate the world matrices for the current set of blend weights and get the accurate count of the number of blends
				for (DWORD i = 0; i < pMeshContainer->NumInfl; ++i)
				{
					iMatrixIndex = pBoneComb[iAttrib].BoneId[i];
					if (iMatrixIndex != UINT_MAX)
					{
						D3DXMatrixMultiply(&matTemp, &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
							pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]);
						pd3dDevice->SetTransform(D3DTS_WORLDMATRIX(i), &matTemp);
					}
				}

				pd3dDevice->SetRenderState(D3DRS_VERTEXBLEND, NumBlend);

				// lookup the material used for this subset of faces
				if ((AttribIdPrev != pBoneComb[iAttrib].AttribId) || (AttribIdPrev == UNUSED32))
				{
					pd3dDevice->SetMaterial(&pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D);
					pd3dDevice->SetTexture(0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId]);
					AttribIdPrev = pBoneComb[iAttrib].AttribId;
				}

				// draw the subset now that the correct material and matrices are loaded
				pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
			}
		}
		pd3dDevice->SetRenderState(D3DRS_VERTEXBLEND, 0);
	}
	else  // standard mesh, just draw it after setting material properties
	{
		pd3dDevice->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);

		for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
		{
			pd3dDevice->SetMaterial(&pMeshContainer->pMaterials[iMaterial].MatD3D);
			pd3dDevice->SetTexture(0, pMeshContainer->ppTextures[iMaterial]);
			pMeshContainer->MeshData.pMesh->DrawSubset(iMaterial);
		}
	}
}

//--------------------------------------------------------------------------------------
// Name: UpdateFrameMatrics()
// Desc: 更新框架中的变换矩阵
//--------------------------------------------------------------------------------------
void Model::updateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	if (pFrameBase == NULL || pParentMatrix == NULL) return;
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;

	// 将当前骨骼的相对于父骨骼的偏移矩阵作累积运算
	D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);

	updateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);                              // 更新兄弟骨骼
	updateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);   // 更新子骨骼
}

//---------------------------------------------------------
//Name:真正暴露给外部调用的函数
//Desc:关于动画的创建，更新，绘制
//---------------------------------------------------------

void Model::setAnimationByName(LPCTSTR name)
{
	//m_pAnimController->SetTrackPosition(0, 0.5);
	LPD3DXANIMATIONSET pAnimationSet = NULL;
	m_pAnimController->GetAnimationSetByName(name, &pAnimationSet);
	m_pAnimController->SetTrackAnimationSet((UINT)0.0, pAnimationSet);
	m_pAnimController->SetTrackEnable(0, true);
}

void Model::setAnimationByName(LPCTSTR name, int track, float wigth)
{
	//m_pAnimController->SetTrackPosition(0, 0.5);
	LPD3DXANIMATIONSET pAnimationSet = NULL;
	m_pAnimController->GetAnimationSetByName(name, &pAnimationSet);
	//m_pAnimController->SetTrackAnimationSet((UINT)1.0, pAnimationSet);
	m_pAnimController->SetTrackAnimationSet(track, pAnimationSet);
	m_pAnimController->SetTrackEnable(track, true);
	m_pAnimController->SetTrackWeight(track, wigth);
	m_pAnimController->SetTrackSpeed(track, 1.0);

}

LPD3DXANIMATIONSET Model::getAnimationSetByName(LPCTSTR name)
{
	LPD3DXANIMATIONSET pAnimationSet = NULL;
	m_pAnimController->GetAnimationSetByName(name, &pAnimationSet);
	return pAnimationSet;
}

void Model::updateAnimation(double timeDelay)
{
	m_pAnimController->AdvanceTime(timeDelay, NULL);
}

void Model::resetAnimation(void)
{
	m_pAnimController->SetTrackPosition(0, 0);

}