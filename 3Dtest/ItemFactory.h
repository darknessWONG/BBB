#pragma once
#include "Item.h"
#include "Common.h"
#include <d3dx9.h>
class ItemFactory
{
public:
	ItemFactory();
	~ItemFactory();

	static Item* create_item(float x, float y, int type);
	static BOOL item_unite(Item* ia, Item* ib);

	static void setDevice(LPDIRECT3DDEVICE9 device);
private:
	static LPDIRECT3DDEVICE9 g_pD3DDevice;
};

