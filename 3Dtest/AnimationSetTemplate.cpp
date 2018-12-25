#include "stdafx.h"
#include "AnimationSetTemplate.h"


AnimationSet::AnimationSet(vector<AnimationInfoTemplate> list, MyMesh* mesh)
{
	this->target = mesh;
	int listNum = list.size();
	for (int i = 0; i < listNum; i++)
	{
		Animation* p = new Animation(list[i].anima, mesh);
		AnimationInfo info = { p, list[i].startFream };
		this->list.push_back(info);
	}
}


AnimationSet::~AnimationSet()
{
}

bool AnimationSet::checkEnd(void)
{
	int listNum = list.size();
	for (int i = 0; i < listNum; i++)
	{
		if (!list[i].anima->checkEnd())
		{
			return false;
		}
	}
	return true;
}

void AnimationSet::play(void)
{
	int listNum = list.size();
	for (int i = 0; i < listNum; i++)
	{
		if (nowFream >= list[i].startFream)
		{
			list[i].anima->play();
		}
	}
	nowFream++;
}

vector<AnimationInfo> AnimationSet::getList(void)
{
	return list;
}

MyMesh * AnimationSet::getTarget(void)
{
	return target;
}

int AnimationSet::getNowFream(void)
{
	return nowFream;
}
