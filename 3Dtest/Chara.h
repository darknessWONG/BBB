#pragma once
#include "Model.h"

class Chara :
	public Model
{
public:
	Chara();
	Chara(string modelPath);
	virtual ~Chara();

	/*===========================================
	virtual member
	============================================*/

	/*===========================================
	public function
	============================================*/


	/*===========================================
	public geter / seter
	============================================*/
	float getWalkSpeed(void);
	void setWalkSpeed(float walkSpeed);

private:
	float walkSpeed;

};

