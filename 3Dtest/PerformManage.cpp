#include "stdafx.h"
#include "PerformManage.h"


PerformManage::PerformManage()
{
}


PerformManage::~PerformManage()
{
}

void PerformManage::addPerforms(Perform * perform)
{
	performs.push_back(perform);
}

void PerformManage::removePerforms(int index)
{
	if (index >= 0 && index < (int)performs.size())
	{
		delete performs[index];
		vector<Perform*>::iterator it = performs.begin() + index;
		performs.erase(it);
	}
}

void PerformManage::removePerforms(Perform * perform)
{
	for (vector<Perform*>::iterator it = performs.begin(); it != performs.end(); it++)
	{
		if (*it == perform)
		{
			delete *it;
			performs.erase(it);
			it = performs.begin();
			if (performs.size() == 0)
			{
				break;
			}
		}
	}
}

bool PerformManage::playPerforms(void)
{
	if (performs.size() <= 0)
	{
		return false;
	}
	if (performs[0]->checkEnd())
	{
		removePerforms(0);
	}
	if (performs.size() > 0)
	{
		performs[0]->play();
		return true;
	}
	return false;
}

Perform * PerformManage::getPlayingPerforms(void)
{
	if (performs.size() <= 0)
	{
		return NULL;
	}
	return performs[0];
}
