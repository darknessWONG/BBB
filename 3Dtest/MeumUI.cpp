#include "stdafx.h"
#include "MeumUI.h"
#include "input.h"


MeumUI::MeumUI()
{
	isDelete = false;
}


MeumUI::~MeumUI()
{
}

void MeumUI::assembleUIs(void)
{
	if (background != NULL)
	{
		background->releaseChain();
		background->addChild(pointer);
		int optionsNum = options.size();
		for (int i = 0; i < optionsNum; i++)
		{
			background->addChild(options[i]);
		}
	}
}

void MeumUI::dataUpdate(void)
{
	if (background != NULL)
	{
		background->setIsDisplay(isDisplay);
	}

	if (isDisplay)
	{
		if (Keyboard_IsTrigger(DIK_UP))
		{
			setNowPointing(nowPointing - 1);
		}
		else if (Keyboard_IsTrigger(DIK_DOWN))
		{
			setNowPointing(nowPointing + 1);
		}
		calPointerPosition();
	}
}

void MeumUI::draw(LPDIRECT3DDEVICE9 g_pD3DDevice)
{
	assembleUIs();
	if (background != NULL)
	{
		background->draw(g_pD3DDevice, &position);
	}
}

void MeumUI::addOptins(UI * option)
{
	options.push_back(option);
}

void MeumUI::calPointerPosition(void)
{
	D3DXVECTOR2 opPos = options[nowPointing]->getPosition();
	pointer->setPosition({ opPos.x - pointer->getWidth(), opPos.y });
}

UIIdentity MeumUI::getNowPointingIdentity(void)
{
	return options[nowPointing]->getIdentity();
}

int MeumUI::getNowPointingIndex(void)
{
	return options[nowPointing]->getIndex();
}

void MeumUI::cleanOption(void)
{
	if (background != NULL)
	{
		background->releaseChain();
		int optionNum = options.size();
		for (int i = 0; i < optionNum; i++)
		{
			delete options[optionNum - i - 1];
			options.pop_back();
		}
		nowPointing = 0;
	}
}

D3DXVECTOR2 MeumUI::getPosition(void)
{
	return position;
}

void MeumUI::setPosition(D3DXVECTOR2 pos)
{
	this->position = pos;
}

int MeumUI::getNowPointing(void)
{
	return nowPointing;
}

void MeumUI::setNowPointing(int nowPointing)
{
	nowPointing %= options.size();
	if (nowPointing < 0)
	{
		nowPointing = options.size() - nowPointing;
	}
	this->nowPointing = nowPointing;
}

void MeumUI::setBackground(UI * ui)
{
	background = ui;
}

void MeumUI::setPointer(UI * ui)
{
	pointer = ui;
}

void MeumUI::setIsDisplay(bool isDisplay)
{
	this->isDisplay = isDisplay;
}

bool MeumUI::getIsDelete(void)
{
	return isDelete;
}

void MeumUI::setIsDelete(bool isDelete)
{
	this->isDelete = isDelete;
}

