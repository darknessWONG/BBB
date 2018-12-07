#pragma once

#include "stdafx.h"

// attraction name
enum Attraction
{
	ATTRACTION_UNKNOWN = -1,
	ATTRACTION_MARRY,
	ATTRACTION_ROLLER,
	ATTRACTION_FERRIS,
	ATTRACTION_VIKING,
	ATTRACTION_MAX
};

// resource name
enum Resource
{
	RESOURCE_UNKNOWN = -1,
	RESOURCE_NONE,
	RESOURCE_WOOD,
	RESOURCE_IRON,
	RESOURCE_BRICK,
	RESOURCE_MAX
};

typedef struct Building_tag {
	int point;			// score for this recipe
	int texture;		// item texture
	int Rtexture;		// order texture
	int item[9];		// attraction resource
}Building;

class Recipe
{
public:
	Recipe();
	~Recipe();

	static int getTexture(int index);						// return Attraction item texture
	static int getRecipeTexture(int index);					// return Attraction recipe texture
	static int getBuild(int * arr);							// return index of Attraction in recipe list which have same resource index as recipe 
	static int getScore(int index);
	static int getResourceTexture(int index, int number);	// return Resource texture index
private:
	
};
