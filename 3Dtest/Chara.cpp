#include "stdafx.h"
#include "Chara.h"


Chara::Chara()
{
}

Chara::Chara(string modelPath)
	:Model(modelPath)
{
}


Chara::~Chara()
{
}

float Chara::getWalkSpeed(void)
{
	return walkSpeed;
}

void Chara::setWalkSpeed(float walkSpeed)
{
	this->walkSpeed = walkSpeed;
}
