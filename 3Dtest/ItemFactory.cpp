#include "stdafx.h"
#include "ItemFactory.h"

LPDIRECT3DDEVICE9 ItemFactory::g_pD3DDevice = NULL;
vector<Model*> ItemFactory::models;

ItemFactory::ItemFactory()
{
}


ItemFactory::~ItemFactory()
{
}

void ItemFactory::Init(void)
{
	Model* itemModel = new Model("asset\\hew_models\\hew_tree_block.x");
	itemModel->setIsWithAnimation(false);
	itemModel->loadModel(ItemFactory::g_pD3DDevice);
	models.push_back(itemModel);

	itemModel = new Model("asset\\hew_models\\hew_iron_block.x");
	itemModel->setIsWithAnimation(false);
	itemModel->loadModel(ItemFactory::g_pD3DDevice);
	models.push_back(itemModel);

	itemModel = new Model("asset\\hew_models\\hew_rock_block.x");
	itemModel->setIsWithAnimation(false);
	itemModel->loadModel(ItemFactory::g_pD3DDevice);
	models.push_back(itemModel);

	itemModel = new Model("asset\\hew_models\\hew_marry_block.x");
	itemModel->setIsWithAnimation(false);
	itemModel->loadModel(ItemFactory::g_pD3DDevice);
	models.push_back(itemModel);

	itemModel = new Model("asset\\hew_models\\hew_roller_block.x");
	itemModel->setIsWithAnimation(false);
	itemModel->loadModel(ItemFactory::g_pD3DDevice);
	models.push_back(itemModel);

	itemModel = new Model("asset\\hew_models\\hew_ferris_block.x");
	itemModel->setIsWithAnimation(false);
	itemModel->loadModel(ItemFactory::g_pD3DDevice);
	models.push_back(itemModel);

	itemModel = new Model("asset\\hew_models\\hew_viking_block.x");
	itemModel->setIsWithAnimation(false);
	itemModel->loadModel(ItemFactory::g_pD3DDevice);
	models.push_back(itemModel);
}

void ItemFactory::Uninit(void)
{
	int modelNum = models.size();
	for (int i = 0; i < modelNum; i++)
	{
		safe_delete<Model>(models[i]);
	}
	models.clear();
}

Item * ItemFactory::create_item(float x, float y, ResourceM type)
{
	Item* item = new Item();
	item->setModel(models[type]);
	item->setCanMove(true);
	item->setOverlapLevel(-10);
	item->setVecNowPos(new D3DXVECTOR3(x, 0, y));
	item->setStatusNow(type);


	return item;
}

BOOL ItemFactory::item_unite(Item * ia, Item * ib)
{
	int status_a = ia->getStatusNow();
	int status_b = ib->getStatusNow();
	int c = status_b ^ status_a;
	int d = status_b + status_a;
	if ((status_b ^ status_a) == (status_a + status_b))
	{
		ib->setIsDestory(true);
		ia->setStatusNow(status_b ^ status_a);
		return true;
	}
	return false;
}

void ItemFactory::setItemStatus(Item * item, ResourceM type)
{
	item->setStatusNow(type);

	item->setModel(models[type]);

}

void ItemFactory::setDevice(LPDIRECT3DDEVICE9 device)
{
	 ItemFactory::g_pD3DDevice = device;
}
