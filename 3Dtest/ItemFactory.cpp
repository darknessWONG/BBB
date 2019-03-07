#include "stdafx.h"
#include "ItemFactory.h"

LPDIRECT3DDEVICE9 ItemFactory::g_pD3DDevice = NULL;

ItemFactory::ItemFactory()
{
}


ItemFactory::~ItemFactory()
{
}

Item * ItemFactory::create_item(float x, float y, ResourceM type)
{
	Item* item = new Item("radio.x");
	switch (type)
	{
	case RESOURCEM_WOOD:
		//item->setModelPath("asset\\hew_models\\hew_tree_material.x");
		item->setModelPath("asset\\hew_models\\ferrisTest.x");
		item->loadModel(ItemFactory::g_pD3DDevice);
		break;
	case RESOURCEM_IRON:
		item->setModelPath("asset\\hew_models\\hew_iron_material.x");
		item->loadModel(ItemFactory::g_pD3DDevice);
		break;
	case RESOURCEM_BRICK:
		item->setModelPath("asset\\hew_models\\hew_rock_material.x");
		item->loadModel(ItemFactory::g_pD3DDevice);
		break;
	case RESOURCEM_MARRY:
		item->setModelPath("asset\\sprite\\hew_ferris_block.blend.x");
		item->loadModel(ItemFactory::g_pD3DDevice);
		break;
	case RESOURCEM_ROLLER:
		item->setModelPath("radio.x");
		item->loadModel(ItemFactory::g_pD3DDevice);
		break;
	case RESOURCEM_FERRIS:
		item->setModelPath("radio.x");
		item->loadModel(ItemFactory::g_pD3DDevice);
		break;
	case RESOURCEM_VIKING:
		item->setModelPath("radio.x");
		item->loadModel(ItemFactory::g_pD3DDevice);
		break;
	}
	item->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
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
	switch (type)
	{
	case RESOURCEM_WOOD:
		item->setModelPath("mokiuzai.blend.x");
		item->loadModel(ItemFactory::g_pD3DDevice);
		break;
	case RESOURCEM_IRON:
		item->setModelPath("radio.x");
		item->loadModel(ItemFactory::g_pD3DDevice);
		break;
	case RESOURCEM_BRICK:
		item->setModelPath("radio.x");
		item->loadModel(ItemFactory::g_pD3DDevice);
		break;
	case RESOURCEM_MARRY:
		item->setModelPath("radio.x");
		item->loadModel(ItemFactory::g_pD3DDevice);
		break;
	case RESOURCEM_ROLLER:
		item->setModelPath("radio.x");
		item->loadModel(ItemFactory::g_pD3DDevice);
		break;
	case RESOURCEM_FERRIS:
		item->setModelPath("radio.x");
		item->loadModel(ItemFactory::g_pD3DDevice);
		break;
	case RESOURCEM_VIKING:
		item->setModelPath("radio.x");
		item->loadModel(ItemFactory::g_pD3DDevice);
		break;
	}
}

void ItemFactory::setDevice(LPDIRECT3DDEVICE9 device)
{
	 ItemFactory::g_pD3DDevice = device;
}
