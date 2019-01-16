#include "stdafx.h"
#include "AnimationManage.h"

vector<vector<AnimationInfoTemplate>> AnimationManage::animateTemplate;


AnimationManage::AnimationManage()
{
}


AnimationManage::~AnimationManage()
{
}

void AnimationManage::addAnimation(int templateIndex, MyMesh * mm)
{
	AnimationSet* set = new AnimationSet(AnimationManage::animateTemplate[templateIndex], mm);
	list.push_back(set);
}

void AnimationManage::play(void)
{
	int animationNum = list.size();
	for (int i = 0; i < animationNum; i++)
	{
		list[i]->play();
	}
}

void AnimationManage::cleanEndAnimation(void)
{
	if (list.size() != 0)
	{
		vector<AnimationSet*>::iterator it;
		for (it = list.begin(); it != list.end(); it++)
		{
			if ((*it)->checkEnd())
			{
				delete *it;
				it = list.erase(it);
				if (list.size() <= 0)
				{
					break;
				}
			}
		}
	}
}

int AnimationManage::addAnimateTemplate(vector<AnimationInfoTemplate> list)
{
	animateTemplate.push_back(list);
	return animateTemplate.size() - 1;
}
