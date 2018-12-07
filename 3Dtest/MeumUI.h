#pragma once
#include "stdafx.h"
#include "UI.h"
class MeumUI
{
public:
	MeumUI();
	~MeumUI();

	/*===========================================
	virtual member
	============================================*/
	virtual void assembleUIs(void);

	/*===========================================
	public function
	============================================*/
	void draw(LPDIRECT3DDEVICE9 g_pD3DDevice);
	void addOptins(UI* option);


	/*===========================================
	public geter / seter
	============================================*/

private:
	D3DXVECTOR2 position;

	UI* background;
	UI* pointer;
	vector<UI*> options;
};

