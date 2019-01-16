#include "stdafx.h"
#include "AnimationTemplate.h"


AnimationTemplate::AnimationTemplate(int index,
	D3DXVECTOR3 scale,
	D3DXVECTOR3 rotation,
	D3DXVECTOR3 transport,
	D3DXVECTOR3 revolution,
	int totalFream)
{
	this->index = index;
	this->scale = scale;
	this->rotation = rotation;
	this->transport = transport;
	this->revolution = revolution;
	this->totalFream = totalFream;
}


AnimationTemplate::~AnimationTemplate()
{
}

int AnimationTemplate::getIndex(void)
{
	return index;
}

D3DXVECTOR3 AnimationTemplate::getScale(void)
{
	return scale;
}

D3DXVECTOR3 AnimationTemplate::getRotation(void)
{
	return rotation;
}

D3DXVECTOR3 AnimationTemplate::getTransport(void)
{
	return transport;
}

D3DXVECTOR3 AnimationTemplate::getRevolution(void)
{
	return revolution;
}

int AnimationTemplate::getTotalFream(void)
{
	return totalFream;
}
