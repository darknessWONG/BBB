#include "stdafx.h"
#include "Bird.h"


Bird::Bird()
{
	nowTexture = 0;
	nowFrame = 0;
}


Bird::~Bird()
{
}

void Bird::dataUpdate(void)
{
	nowFrame++;
	if (nowFrame > frameGap)
	{
		nowTexture = (nowTexture + 1) % textureList.size();
		nowFrame = 0;
		setTextureIndex(textureList[nowTexture]);
	}
	Billboard::dataUpdate();
}

void Bird::setTextureList(vector<int> list)
{
	this->textureList = list;
}

int Bird::getNowTexture(void)
{
	return nowTexture;
}

void Bird::setNowTexture(int now)
{
	this->nowFrame = now;
}

int Bird::getFrameGap(void)
{
	return frameGap;
}

void Bird::setFrameGap(int gap)
{
	this->frameGap = gap;
}
