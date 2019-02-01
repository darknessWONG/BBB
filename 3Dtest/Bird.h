#pragma once
#include "Billboard.h"
class Bird :
	public Billboard
{
public:
	Bird();
	~Bird();

	/*===========================================
	virtual member
	============================================*/
	virtual void dataUpdate(void);

	void setTextureList(vector<int>list);
	int getNowTexture(void);
	void setNowTexture(int now);
	int getFrameGap(void);
	void setFrameGap(int gap);

private:
	vector<int> textureList;
	int nowTexture;
	int frameGap;
	int nowFrame;
};

