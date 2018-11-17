#include "stdafx.h"
#include "Perform.h"


Perform::Perform()
{
}


Perform::~Perform()
{
}

GameObject * Perform::getActor(void)
{
	return actor;
}

void Perform::setActor(GameObject * actor)
{
	this->actor = actor;
}
