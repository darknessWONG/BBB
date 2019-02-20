#pragma once
/*==============================================================================

[MeumUI.h]
Author : darknessWONG
Date   : 2019/01/28
--------------------------------------------------------------------------------
Level struct of uis.
This is a 2D object, so it isn't a gameObject
==============================================================================*/
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
	//If you just want to use this meum to display a dialog, then only set the background and displayStr
	void setBackground(UI* ui);
	void setPointer(UI* ui);
	void setIsDisplay(bool isDisplay);
	bool getIsReadInput(void);
	void setIsReadInput(bool isReadInput);
	bool getIsDelete(void);
	void setIsDelete(bool isDelete);
	void setDisplayStr(string str);
private:
	D3DXVECTOR2 position;

	UI* background;
	UI* pointer;
	int nowPointing;
	vector<UI*> options;
	
	string displayStr;

	bool isDisplay;
	bool isReadInput;
	bool isDelete;
};

