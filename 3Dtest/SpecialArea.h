#pragma once
#include "GameObject.h"
class SpecialArea :
	public GameObject
{
public:
	SpecialArea();
	virtual ~SpecialArea();

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

