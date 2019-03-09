#pragma once
/*==============================================================================
[Model.h]
Author : darknessWONG
Date   : 2018/11/23
--------------------------------------------------------------------------------
The model with is from xfile,
you can only load the model once even if there are many gameObject is useing a
same model.
==============================================================================*/
#include "stdafx.h"
#include "AllocateHierarchy.h"
#include "Physics.h"
class Model
{
public:
	Model();
	Model(string modelPath);
	virtual ~Model();
	/*===========================================
	virtual member
	============================================*/
	//it will cal the animation status in this function,
	//so every gameObejct should save there onw animaCount
	virtual void dataUpdate(float animaCount);
	virtual void draw(LPDIRECT3DDEVICE9 pD3DDevice, D3DXMATRIX * const matWorld, float animaCount);
	/*cal the new bounding box
	so that you should call it every time you set a new position or bounding center*/
	virtual void calBounding(void);
	virtual RECTF getBoundingRect(void);
	virtual BOXF getBoundingBox(void);
	/*===========================================
	public function
	============================================*/
	void loadModel(LPDIRECT3DDEVICE9 pD3DDevice);
	void calBoundingBox(void);
	void calBoundingBox(LPD3DXFRAME pFrameBase, D3DXVECTOR3 &boundingBoxMin, D3DXVECTOR3 &boundingBoxMax);

	/*===========================================
	public geter / seter
	============================================*/
	string getModelPath(void);
	void setModelPath(string modelPath);
	bool getIsWithAnimation(void);
	void setIsWithAnimation(bool isWithAnimation);

	//提供给外界的接口

	//通过名字设置要播放的骨骼动画
	void setAnimationByName(LPCTSTR name);
	void setAnimationByName(LPCTSTR name, int track, float wigth);
	LPD3DXANIMATIONSET getAnimationSetByName(LPCTSTR name);
	//更新动画
	void updateAnimation(double timeDelay);
	void resetAnimation(void);



private:
	//一些微软自带函数，关于骨骼动画加载与绘制更新的函数，将其封装，不使用这些接口

	void drawMeshContainer(IDirect3DDevice9* pd3dDevice, LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase);
	void drawFrame(IDirect3DDevice9* pd3dDevice, LPD3DXFRAME pFrame);
	HRESULT setupBoneMatrixPointers(LPD3DXFRAME pFrameBase, LPD3DXFRAME pFrameRoot);
	void updateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);



	string modelPath;
	bool isWithAnimation;

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

	CAllocateHierarchy* m_pAllocateHier;			//骨骼动画网格模型指针
	LPD3DXFRAME			m_pFrameRoot;				//帧
	LPD3DXANIMATIONCONTROLLER m_pAnimController;	//动画控制器
	D3DXMATRIX*			m_pBoneMatrix;				//骨骼矩阵
};