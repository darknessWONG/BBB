#include "stdafx.h"
#include "Ground.h"


Ground::Ground()
{
}

Ground::Ground(string modelPath)
	: Model(modelPath)
{
}


Ground::~Ground()
{
}

RECTF Ground::getBoundingRect(void)
{
	return{ 0, 0, 0, 0 };
}
