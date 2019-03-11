#pragma once
#include "GameObject.h"
class HandoutBox :
	public GameObject
{
public:
	HandoutBox();
	~HandoutBox();

	virtual void dataUpdate(void);

	void playAnima(void);

	bool getIsPlayAnima(void);
	void setIsPlayAnima(bool isPlayAnima);
private:
	int nowAnimaFrame;
	bool isPlayAnima;
};

