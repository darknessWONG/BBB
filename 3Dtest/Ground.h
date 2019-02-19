#pragma once
#include "GameObject.h"

class Ground :
	public GameObject
{
public:
	Ground();
	~Ground();

	/*===========================================
	virtual member
	============================================*/
	virtual RECTF getBoundingRect(void);
};

