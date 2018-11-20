#include "stdafx.h"
#include "PerformManage.h"


PerformManage::PerformManage()
{
}


PerformManage::~PerformManage()
{
}

void PerformManage::addPerforms(Perform * Perform)
{
	performs.push_back(Perform);
}

bool PerformManage::playPerforms(void)
{
	if (performs.size() <= 0)
	{
		return false;
	}
	if (performs[0]->checkEnd())
	{
		performs.pop_back();
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
