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
	virtual void dataUpdate(void);

	/*===========================================
	public function
	============================================*/
	void draw(LPDIRECT3DDEVICE9 g_pD3DDevice);
	void addOptins(UI* option);
	void calPointerPosition(void);
	UIIdentity getNowPointingIdentity(void);
	int getNowPointingIndex(void);
	void cleanOption(void);

	/*===========================================
	public geter / seter
	============================================*/
	D3DXVECTOR2 getPosition(void);
	void setPosition(D3DXVECTOR2 pos);
	int getNowPointing(void);
	void setNowPointing(int nowPointing);
	void setBackground(UI* ui);
	void setPointer(UI* ui);

private:
	D3DXVECTOR2 position;

	UI* background;
	UI* pointer;
	int nowPointing;
	vector<UI*> options;
};

