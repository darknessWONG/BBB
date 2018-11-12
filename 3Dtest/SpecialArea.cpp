#include "stdafx.h"
#include "Common.h"
#include "SpecialArea.h"


SpecialArea::SpecialArea()
{
}


SpecialArea::~SpecialArea()
{
}

float SpecialArea::getRadius(void)
{
	return radius;
}

void SpecialArea::setRadius(float radius)
{
	this->radius = radius;
}
