#pragma once
#include "Chara.h"
class Player :
	public Chara
{
public:
	Player();
	Player(string modelPath);
	virtual ~Player();

	/*===========================================
	virtual member
	============================================*/
	virtual void dataUpdate(void);

	/*===========================================
	public function
	============================================*/

	/*===========================================
	public geter / seter
	============================================*/

private:
	float walkAccele;
};

