#include "stdafx.h"
#include "MeumUI.h"


MeumUI::MeumUI()
{
}


MeumUI::~MeumUI()
{
}

void MeumUI::assembleUIs(void)
{
	background->releaseChain();
	background->addChild(pointer);
	int optionsNum = options.size();
	for (int i = 0; i < optionsNum; i++)
	{
		background->addChild(options[i]);
	}
}

void MeumUI::draw(LPDIRECT3DDEVICE9 g_pD3DDevice);
{
	background->draw(g_pD3DDevice, position);
}

void MeumUI::addOptins(UI * option)
{
	options.push_back(option);
}

