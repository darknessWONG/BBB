#pragma once
#include "stdafx.h"
#include "Perform.h"

class PerformManage
{
public:
	PerformManage();
	~PerformManage();
	
	void addPerforms(Perform* Perform);
	bool playPerforms(void);
private:
	vector<Perform*> performs;
};

