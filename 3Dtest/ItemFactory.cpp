#include "stdafx.h"
#include "ItemFactory.h"

LPDIRECT3DDEVICE9 ItemFactory::g_pD3DDevice = NULL;

ItemFactory::ItemFactory()
{
}


ItemFactory::~ItemFactory()
{
}

Item * ItemFactory::create_item(float x, float y, int type)
{

	Item* item = new Item("tree.x");
	item->loadModel(ItemFactory::g_pD3DDevice);
	item->setVecRotateAxis(new D3DXVECTOR3(0, 1, 0));
	item->setCanMove(true);
	item->setVecNowPos(new D3DXVECTOR3(7.5, 0, 0));
	

	return item;
}

BOOL ItemFactory::item_unite(Item * ia, Item * ib)
{
	//int status_a = ia->get_status_now();
	//int status_b = ib->get_status_now();
	//int c = status_b ^ status_a;
	//int d = status_b + status_a;
	//if ((status_b ^ status_a) == (status_a + status_b))
	//{
	//	ib->set_is_destory(true);
	//	ia->set_status_now(status_b ^ status_a);
	//	return true;
	//}
	//return false;
	return false;
}

void ItemFactory::setDevice(LPDIRECT3DDEVICE9 device)
{
	 ItemFactory::g_pD3DDevice = device;
}
