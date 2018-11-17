#pragma once
#include "GameObject.h"
class Perform
{
public:
	Perform();
	~Perform();
	/*===========================================
	virtual member
	============================================*/
	virtual void play(void) = 0;
	virtual bool checkEnd(void) = 0;

	/*===========================================
	public function
	============================================*/

	/*===========================================
	public geter / seter
	============================================*/
	GameObject* getActor(void);
	void setActor(GameObject* actor);
private:
	GameObject* actor;
};

