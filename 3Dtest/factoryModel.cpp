#include "stdafx.h"
#include "factoryModel.h"
#include "ItemFactory.h"


factoryModel::factoryModel()
{
}

factoryModel::~factoryModel()
{
}

Item * factoryModel::createItem(float x, float y)
{
	return ItemFactory::create_item(x, y, itemType);
}

ResourceM factoryModel::getItemType(void)
{
	return itemType;
}

void factoryModel::setItemType(ResourceM itemType)
{
	this->itemType = itemType;
}
