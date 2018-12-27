#pragma once
#include "AnimationSet.h"
#include "stdafx.h"
#include "MyMesh.h"
class AnimationManage
{
public:
	AnimationManage();
	~AnimationManage();

	/*===========================================
	virtual member
	============================================*/

	/*===========================================
	public function
	============================================*/
	void addAnimation(int templateIndex, MyMesh* mm);
	void play(void);
	void cleanEndAnimation(void);
	/*===========================================
	public geter / seter
	============================================*/

	/*===========================================
	static public function
	============================================*/
	static int addAnimateTemplate(vector<AnimationInfoTemplate> list);

private:
	vector<AnimationSet*> list;

	static vector<vector<AnimationInfoTemplate>> animateTemplate;
};

