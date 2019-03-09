#pragma once
#include "Chara.h"
#include "Item.h"
class Player :
	public Chara
{
public:
	Player();
	virtual ~Player();

	/*===========================================
	virtual member
	============================================*/
	virtual void dataUpdate(void);

	/*===========================================
	public function
	============================================*/
	void releaseHoldings(void);

	/*===========================================
	public geter / seter
	============================================*/
	bool getFindHoldings(void);
	void setFindHoldings(bool findHoldings);
	Item* getHoldings(void);
	void setHoldings(Item* item);

private:
	float walkAccele;
	bool findHoldings;


	Item* holdings = NULL;
};