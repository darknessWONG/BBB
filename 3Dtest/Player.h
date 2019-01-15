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
	void setIsReadInput(bool isi);
private:
	bool isReadInput;

	float walkAccele;
};

