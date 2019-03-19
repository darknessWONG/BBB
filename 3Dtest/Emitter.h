#pragma once

#include "stdafx.h"
#include "Recipe.h"

#define MAX_ORDER			(4)
#define ORDER_MOVESPEED		(4.0f)
#define ORDER_WIDTH			(205.0f)
#define ORDER_COMING_SPEED	((5.0f) * (60.0f))
#define ORDER_TIME			((30.0f) * (60.0f))
#define TIME_LIMIT			((60.0f) * (60.0f))

typedef struct Order_tag {
	int isActive;
	int recipe;
	D3DXVECTOR2 position;
	int times;
	int count;
}Order;

class Emitter
{
public:
	Emitter();
	~Emitter();

	void Update();
	void Draw();
	void Submit(int index);
	
	// getter
	int getScore();
	bool isEnd();

private:
	void Create();
	void Delete(int index);

	Order list[MAX_ORDER];
	int curActive;
	int create_count;

	int score;					// temp score
	int timer;
	int minusFX;
};
