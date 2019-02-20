#pragma once
/*==============================================================================

[PerformManage.h]
Author : darknessWONG
Date   : 2018/11/23
--------------------------------------------------------------------------------
It will manage the perform's.
perform will play one by one, It will play only one perform at the same time.
==============================================================================*/
#include "stdafx.h"
#include "Perform.h"

class PerformManage
{
public:
	PerformManage();
	~PerformManage();
	
	/*===========================================
	public function
	============================================*/
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

