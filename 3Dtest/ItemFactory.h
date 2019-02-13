#pragma once
#include "Item.h"
#include "Common.h"
#include <d3dx9.h>

enum ResourceM
{
	RESOURCEM_NONE = -1,
	RESOURCEM_WOOD,
	RESOURCEM_IRON,
	RESOURCEM_BRICK,
	RESOURCEM_MARRY,
	RESOURCEM_ROLLER,
	RESOURCEM_FERRIS,
	RESOURCEM_VIKING,
	RESOURCEM_MAX
};


class ItemFactory
{
public:
	ItemFactory();
	~ItemFactory();

	static Item* create_item(float x, float y, ResourceM type);
	static BOOL item_unite(Item* ia, Item* ib);
	static void setItemStatus(Item* item, ResourceM type);

	static void setDevice(LPDIRECT3DDEVICE9 device);
private:
	static LPDIRECT3DDEVICE9 g_pD3DDevice;
};

