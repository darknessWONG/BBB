#pragma once
#include "Model.h"
#include "Item.h"
#include "ItemFactory.h"

class factoryModel :
	public Model
{
public:
	factoryModel();
	factoryModel(string modelName);
	~factoryModel();

	Item* createItem(float x, float y);

	ResourceM getItemType(void);
	void setItemType(ResourceM itemType);
private:
	ResourceM itemType;
};

