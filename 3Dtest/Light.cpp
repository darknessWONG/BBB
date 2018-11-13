#include "stdafx.h"
#include "Light.h"


Light::Light()
{
}


Light::~Light()
{
}

void Light::init(LPDIRECT3DDEVICE9 pD3DDevice)
{
	//set the ligh to the device
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vecDirLight(-1.0f, -1.0f, -1.0f);
	D3DXVec3Normalize(&vecDirLight, &vecDirLight);
	light.Direction = vecDirLight;
	light.Diffuse.r = 10.0f;
	light.Diffuse.g = 10.0f;
	light.Diffuse.b = 10.0f;
	light.Diffuse.a = 255.0f;
}

void Light::lightSet(LPDIRECT3DDEVICE9 pD3DDevice)
{
	pD3DDevice->SetLight(0, &light);
	pD3DDevice->LightEnable(0, TRUE);
	//pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	
	//normalize the normals which scaled when scaling
	pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	//Ambient light
	pD3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_RGBA(128, 128, 128, 255));
	//pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
	pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	//MyDirect3D_GetDevice()->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_RGBA(255, 255, 255, 255));
	//MyDirect3D_GetDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

}
