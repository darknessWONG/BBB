#pragma once
#include "Model.h"
#include "Chara.h"
class Item :
	public Model
{
public:
	Item();
	Item(string modelPath);
	~Item();

	/*===========================================
	virtual member
	============================================*/
	virtual void positionUpdateX(void);
	virtual void positionUpdateY(void);
	virtual void positionUpdateZ(void);
	virtual void positionUpdate(void);
	virtual void item_status_change();
	virtual void item_status_change(Item* item);

	/*===========================================
	public function
	============================================*/

	/*===========================================
	public geter / seter
	============================================*/
	bool getIsContainer(void);
	void setIsContainer(bool isContainer);
	Chara* getBelong(void);
	void setBelong(Chara* belong);
	int getStatusMax(void);
	void setStatusMax(int statusMax);
	int getStatusNow(void);
	void setStatusNow(int statusNow);
	bool getIsDestory(void);
	void setIsDestory(bool isDestory);
private:
	bool isContainer;
	Chara* belong = NULL;

	int statusMax;
	int statusNow;

	bool isDestory;
};

