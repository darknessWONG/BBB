#include "stdafx.h"
#include "HandoutBox.h"


HandoutBox::HandoutBox()
{
	nowAnimaFrame = 0;
	isPlayAnima = false;
}


HandoutBox::~HandoutBox()
{
}

void HandoutBox::dataUpdate(void)
{
	playAnima();
	GameObject::dataUpdate();
}

void HandoutBox::playAnima(void)
{
	if (isPlayAnima)
	{
		if (nowAnimaFrame <= 120)
		{
			getModel()->updateAnimation(1 / 60.0f);
			nowAnimaFrame++;
		}
		else
		{
			nowAnimaFrame = 0;
			isPlayAnima = false;
			getModel()->resetAnimation();
		}
	}
}

bool HandoutBox::getIsPlayAnima(void)
{
	return isPlayAnima;
}

void HandoutBox::setIsPlayAnima(bool isPlayAnima)
{
	this->isPlayAnima = isPlayAnima;
}

