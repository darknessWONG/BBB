#pragma once
#include "stdafx.h"
#include "Item.h"
#include "GameObject.h"

//typedef struct
//{
//	Item* item;
//	D3DXVECTOR2 pos;
//}WorkbenchItem;



class Workbench :
	public GameObject
{
public:
	Workbench(int line, int column, float width, float length);
	~Workbench();

	/*===========================================
	virtual member
	============================================*/
	virtual void draw(LPDIRECT3DDEVICE9 pD3DDevice);
	virtual RECTF getBoundingRect(void);
	virtual D3DXVECTOR2 getBoundingCenter(void);
	virtual void setBoundingCenter(D3DXVECTOR2 center);

	/*===========================================
	public function
	============================================*/
	bool addItem(Item* item);
	void releaseItems(void);

	//void pop_w_items(void);
	void fuse_items(void);

	D3DXVECTOR2 cal_bolck_position(D3DXVECTOR2 block);
	void set_items_position(void);

	/*===========================================
	public geter / seter
	============================================*/
	int getLineNum(void);
	void setLineNum(int lineNum);
	int getColumnNum(void);
	void setColumnNum(int columnNum);
	float getWidth(void);
	void setWidth(float width);
	float getLength(void);
	void setLength(float length);
private:
	Item** items;

	int lineNum;
	int columnNum;
	float width;
	float length;
	Vertex* grid;
};

