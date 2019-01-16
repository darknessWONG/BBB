#pragma once
#include "AnimationTemplate.h"
#include "Animation.h"
#include "MyMesh.h"
#include "stdafx.h"
typedef struct SAnimationInfoTemplate
{
	AnimationTemplate* anima;
	int startFream;
}AnimationInfoTemplate;

typedef struct SAnimationInfo
{
	Animation* anima;
	int startFream;
}AnimationInfo;

class AnimationSet
{
public:
	AnimationSet(vector<AnimationInfoTemplate> list, MyMesh* mesh);
	~AnimationSet();

	/*===========================================
	virtual member
	============================================*/

	/*===========================================
	public function
	============================================*/
	bool checkEnd(void);
	void play(void);

	/*===========================================
	public geter / seter
	============================================*/
	vector<AnimationInfo> getList(void);
	MyMesh* getTarget(void);
	int getNowFream(void);
private:
	vector<AnimationInfo> list;
	MyMesh* target;

	int nowFream;
};

