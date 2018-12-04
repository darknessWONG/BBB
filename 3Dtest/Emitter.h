#pragma once

#include "stdafx.h"
#include "Recipe.h"

#define MAX_ORDER			(4)
#define ORDER_COMING_SPEED	(60)
#define ORDER_MOVESPEED		(8.0f)
#define ORDER_WIDTH			(205.0f)
#define ORDER_TIME			(1000)

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

private:
	void Create();
	void Delete(int index);

	Order list[MAX_ORDER];
	int curActive;
	int create_count;

	int score;					// temp score
};
