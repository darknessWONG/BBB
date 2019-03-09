#include "stdafx.h"
#include "Recipe.h"
#include "texture.h"

// ATTRACTION DATA
Building list[Attraction::ATTRACTION_MAX] = {
	// MARRY
	{ 8, 0, TEX_MARRY,{
		Resource::RESOURCE_WOOD,		Resource::RESOURCE_NONE,		Resource::RESOURCE_BRICK,
		Resource::RESOURCE_NONE,		Resource::RESOURCE_BRICK,		Resource::RESOURCE_IRON,
		Resource::RESOURCE_IRON,		Resource::RESOURCE_WOOD,		Resource::RESOURCE_NONE, }
	},
	// ROLLER
	{ 20, 0, TEX_ROLLER,{
		Resource::RESOURCE_NONE,		Resource::RESOURCE_NONE,		Resource::RESOURCE_IRON,
		Resource::RESOURCE_IRON,		Resource::RESOURCE_IRON,		Resource::RESOURCE_WOOD,
		Resource::RESOURCE_WOOD,		Resource::RESOURCE_WOOD,		Resource::RESOURCE_BRICK, }
	},
	// FERRIS
	{ 100, 0, TEX_FERRIS,{
		Resource::RESOURCE_NONE,		Resource::RESOURCE_BRICK,		Resource::RESOURCE_NONE,
		Resource::RESOURCE_IRON,		Resource::RESOURCE_BRICK,		Resource::RESOURCE_IRON,
		Resource::RESOURCE_NONE,		Resource::RESOURCE_IRON,		Resource::RESOURCE_NONE, }
	},
	// VIKING
	{ 1000, 0, TEX_VIKING,{
		Resource::RESOURCE_NONE,		Resource::RESOURCE_IRON,		Resource::RESOURCE_NONE,
		Resource::RESOURCE_WOOD,		Resource::RESOURCE_NONE,		Resource::RESOURCE_WOOD,
		Resource::RESOURCE_WOOD,		Resource::RESOURCE_WOOD,		Resource::RESOURCE_WOOD, }
	},
};

Recipe::Recipe()
{
}

Recipe::~Recipe()
{
}

int Recipe::getTexture(int index)
{
	return list[index].texture;
}

int Recipe::getRecipeTexture(int index)
{
	return list[index].Rtexture;
}

int Recipe::getBuild(int * arr)
{
	for (int i = 0; i < Attraction::ATTRACTION_MAX; i++) {
		// check insert array is same which any recipes
		for (int j = 0; j <= 9; j++) {
			// return index of the index of item that have same with recipe
			if (j == 9) return i;

			// check is item that insert in any slot same with recipe
			if (arr[j] != list[i].item[j]) {
				break;
			}
		}
	}
	// in case of not same as any recipes
	return Attraction::ATTRACTION_UNKNOWN;
}

int Recipe::getScore(int index)
{
	return list[index].point;
}

int Recipe::getResourceTexture(int index, int number)
{
	int ref = -1;

	switch (list[index].item[number])
	{
	case RESOURCE_UNKNOWN:
		ref = 0;
		break;
	case RESOURCE_NONE:
		ref = TEX_NONE;
		break;
	case RESOURCE_WOOD:
		ref = TEX_WOOD;
		break;
	case RESOURCE_IRON:
		ref = TEX_IRON;
		break;
	case RESOURCE_BRICK:
		ref = TEX_BRICK;
		break;
	default:
		break;
	}

	return ref;
}
