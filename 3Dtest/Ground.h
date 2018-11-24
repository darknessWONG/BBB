#pragma once
#include "Model.h"
class Ground :
	public Model
{
public:
	Ground();
	Ground(string modelPath);
	~Ground();

	/*===========================================
	virtual member
	============================================*/
	virtual RECTF getBoundingRect(void);
};

