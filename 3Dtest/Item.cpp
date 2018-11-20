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

int Item::getSstatusNow(void)
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
