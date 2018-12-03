#include "stdafx.h"
#include "Item.h"


Item::Item()
{
}

Item::Item(string modelPath)
	:Model(modelPath)
{
}


Item::~Item()
{
}

void Item::positionUpdateX(void)
{
	if (belong != NULL)
	{
		D3DXVECTOR2 center = getBoundingCenter();
		center.x = belong->getBoundingCenter().x;
		setBoundingCenter(center);
	}
}

void Item::positionUpdateY(void)
{
	if (belong != NULL)
	{
		D3DXVECTOR3 pos = *getVecNowPos();
		pos.y = belong->getBoundingBoxMax().y;
		setVecNowPos(&pos);
	}
	else
	{
		D3DXVECTOR3 pos = *getVecNowPos();
		pos.y = 0;
		setVecNowPos(&pos);
	}
}

void Item::positionUpdateZ(void)
{
	if (belong != NULL)
	{
		D3DXVECTOR2 center = getBoundingCenter();
		center.y = belong->getBoundingCenter().y;
		setBoundingCenter(center);
	}
}

void Item::positionUpdate(void)
{
	if (belong != NULL)
	{
		D3DXVECTOR2 center = getBoundingCenter();
		center.x = belong->getBoundingCenter().x;
		center.y = belong->getBoundingCenter().y;
		setBoundingCenter(center);

		D3DXVECTOR3 pos = *getVecNowPos();
		pos.y = belong->getBoundingBoxMax().y;
		setVecNowPos(&pos);
	}
	else
	{
		D3DXVECTOR3 pos = *getVecNowPos();
		pos.y = 0;
		setVecNowPos(&pos);
	}
}

void Item::item_status_change()
{
}

void Item::item_status_change(Item * item)
{
	//status_now++;
	//item->set_is_destory(true);
}

bool Item::getIsContainer(void)
{
	return isContainer;
}

void Item::setIsContainer(bool isContainer)
{
	this->isContainer = isContainer;
}

Chara * Item::getBelong(void)
{
	return belong;
}

void Item::setBelong(Chara * belong)
{
	this->belong = belong;
}

int Item::getStatusMax(void)
{
	return statusMax;
}

void Item::setStatusMax(int statusMax)
{
	this->statusMax = statusMax;
}

int Item::getStatusNow(void)
{
	return statusNow;
}

void Item::setStatusNow(int statusNow)
{
	this->statusNow = statusNow;
}

bool Item::getIsDestory(void)
{
	return isDestory;
}

void Item::setIsDestory(bool isDestory)
{
	this->isDestory = isDestory;
}
