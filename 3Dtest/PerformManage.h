#pragma once
#include "stdafx.h"
#include "Perform.h"

class PerformManage
{
public:
	PerformManage();
	~PerformManage();
	
	void addPerforms(Perform* perform);
	void removePerforms(int index);
	void removePerforms(Perform* perform);
	//if all performs are finished, return false
	//if is playing, return true
	bool playPerforms(void);
	Perform* getPlayingPerforms(void);
private:
	vector<Perform*> performs;
};

