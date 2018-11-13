#pragma once
#include "GameObject.h"
class SpecialArea :
	public GameObject
{
public:
	SpecialArea();
	~SpecialArea();

	/*===========================================
	virtual member
	============================================*/

	/*===========================================
	public geter / seter
	============================================*/
	float getRadius(void);
	void setRadius(float radius);
private:
	float radius;
};

