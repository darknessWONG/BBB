#include "stdafx.h"
#include "NameTap.h"


NameTap::NameTap()
{
}


NameTap::~NameTap()
{
}

void NameTap::dataUpdate(void)
{
	if (belong->getIsDelete())
	{
		setIsDelete(true);
	}
	if (!belong->getIsDisplay())
	{
		setIsDisplay(false);
	}
	Billboard::dataUpdate();
}

void NameTap::positionUpdateX(void)
{
	D3DXVECTOR3 pos = *getVecNowPos();
	pos.x = belong->getBoundingCenter().x;
	setVecNowPos(&pos);
}

void NameTap::positionUpdateY(void)
{
	D3DXVECTOR3 pos = *getVecNowPos();
	BOXF box = belong->getBoundingBox();
	pos.y = belong->getBoundingCenter3D().y + (box.top - box.bottom);
	setVecNowPos(&pos);
}

void NameTap::positionUpdateZ(void)
{
	D3DXVECTOR3 pos = *getVecNowPos();
	pos.z = belong->getBoundingCenter().y;
	setVecNowPos(&pos);
}

void NameTap::positionUpdate(void)
{
	D3DXVECTOR3 pos = belong->getBoundingCenter3D();
	BOXF box = belong->getBoundingBox();
	pos.y += (box.top - box.bottom) / 2;
	setVecNowPos(&pos);
}

void NameTap::draw(LPDIRECT3DDEVICE9 pD3DDevice)
{
	if (getIsDisplay())
	{
		D3DMATERIAL9 white;
		white.Diffuse = { 1.0f, 0.0f, 0.0f, 1.0f };
		white.Ambient = white.Diffuse;
		white.Power = 2.0;
		white.Emissive = white.Diffuse;
		white.Specular = white.Diffuse;


		pD3DDevice->SetMaterial(&white);
		pD3DDevice->SetTexture(0, 0); // disable texture
		pD3DDevice->SetFVF(FVF_VERTEX3D);
		pD3DDevice->SetTransform(D3DTS_WORLD, getMtxWorld());
		Text->DrawSubset(0);
	}
}

void NameTap::initName(LPDIRECT3DDEVICE9 pD3DDevice)
{
	// Obtain a handle to a device context.
	HDC hdc = CreateCompatibleDC(0);
	// Fill out a LOGFONT structure that describes the fontfs properties.
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 25; // in logical units
	lf.lfWidth = 12; // in logical units
	lf.lfWeight = 500; // boldness, range 0(light) - 1000(bold)
	lf.lfItalic = false;
	lf.lfUnderline = false;
	lf.lfStrikeOut = false;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfOutPrecision = 0;
	lf.lfClipPrecision = 0;
	lf.lfQuality = 0;
	lf.lfPitchAndFamily = 0;
	strcpy_s(lf.lfFaceName, "Times New Roman"); // font style
	
	// Create a font and select that font with the device context.
	HFONT hFont;
	HFONT hFontOld;
	hFont = CreateFontIndirect(&lf);
	hFontOld = (HFONT)SelectObject(hdc, hFont);
	// Create the 3D mesh of text.
	D3DXCreateText(pD3DDevice, hdc, belong->getBattleChara()->getName().c_str(), 0.001f, 0.1f, &Text, 0, 0);
	// Reselect the old font, and free resources.
	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);
}

void NameTap::setBelong(Chara * belong)
{
	this->belong = belong;
}
