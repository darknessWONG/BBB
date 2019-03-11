#include "stdafx.h"
#include "Emitter.h"
#include "Common.h"
#include "Recipe.h"
#include "font.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "Number.h"

#define TIMER_GUAGE_SIZE		(600.0f)
#define TIMER_POSITION_X		(20)
#define TIMER_POSITION_Y		(20)



Emitter::Emitter()
{
	for (int i = 0; i < MAX_ORDER; i++) {
		list[i].isActive = 0;
		list[i].recipe = -1;
		list[i].times = 0;
		list[i].count = 0;
	}

	timer = 0;
	score = 0;

	curActive = 0;
	create_count = 0;

	Create();
	srand((unsigned)time(NULL));
}

Emitter::~Emitter()
{
	// delete pointer
}

void Emitter::Create()
{
	for (int i = 0; i < MAX_ORDER; i++) {
		if (list[i].isActive == 0) {
			list[i].isActive = 1;
			list[i].recipe = rand() % Attraction::ATTRACTION_MAX;			// random recipe
			list[i].position = D3DXVECTOR2(Common::screen_width, 5.0f);		// padding from y axis 5.0f
			list[i].times = ORDER_TIME;										// expire time
			list[i].count = 0;												// time counter
			return;
		}
	}
}

void Emitter::Update()
{
	curActive = 0;
	// move order to left side
	bool canMove;
	for (int i = 0; i < MAX_ORDER; i++) {
		if (list[i].isActive == 0) continue;

		canMove = true;
		if (list[i].position.x > 5.0f) {					// x axis padding 5.0f
			for (int j = 0; j < MAX_ORDER; j++) {
				if (j == i) continue;
				if (list[j].isActive == 1) {
					if (list[i].position.x >= list[j].position.x && list[i].position.x <= list[j].position.x + ORDER_WIDTH) {
						canMove = false;
						break;
					}
				}
			}
			if (canMove) {
				list[i].position.x -= ORDER_MOVESPEED;
			}
		}
	}

	// timer counter
	for (int i = 0; i < MAX_ORDER; i++) {
		if (list[i].isActive == 1) {
			curActive++;
			list[i].count += 1;
			if (list[i].count >= list[i].times) {
				// TODO Score Minus
				score -= 1000;
				// Delete this order from list
				Delete(i);
			}
		}
	}

	// create next order
	if (curActive != MAX_ORDER) {
		create_count++;
		if (create_count >= ORDER_COMING_SPEED) {
			create_count = 0;
			Create();
		}
	}

	if (score < 0) {
		score = 0;
	}

	// debug
	if (timer < 0) 
		timer = 0;

	timer++;
}

void Emitter::Draw()
{
	for (int i = 0; i < MAX_ORDER; i++) {
		if (list[i].isActive == 1) {
			// TODO Draw list[i].index - texture get from Recipe class - at position
			Sprite_Draw_Size(TEX_ORDER_BG, list[i].position.x + 100, list[i].position.y + 55, 200, 110);
			Sprite_Draw_Size(Recipe::getRecipeTexture(list[i].recipe), list[i].position.x + 50, list[i].position.y + 50, 100, 100);
			for (int j = 0; j < 9; j++) {
				Sprite_Draw_Size(
					Recipe::getResourceTexture(list[i].recipe,j), 
					list[i].position.x + 100 + 17 + 33 * (j % 3), 
					list[i].position.y + 17 + 33 * ((int)j / 3), 
					33, 33);
			}
			Sprite_Draw_Size(TEX_GUAGE, 
				list[i].position.x + 100 - 100 * ((float)list[i].count / list[i].times), 
				list[i].position.y + 105, 
				200 - 200.0f * ((float)list[i].count/ list[i].times), 
				10);
		}
	}

	// score
	Number::Draw(score, 6, D3DXVECTOR2(Common::screen_width - 200, Common::screen_height - 20.0f), 0.5f);

	// timer
	Sprite_Draw_Size(TEX_GUAGE,
		TIMER_POSITION_X + TIMER_GUAGE_SIZE * 0.5f - TIMER_GUAGE_SIZE * ((float)timer / TIME_LIMIT) * 0.5f,
		Common::screen_height - TIMER_POSITION_Y,
		TIMER_GUAGE_SIZE - TIMER_GUAGE_SIZE * ((float)timer / TIME_LIMIT),
		20);

#if _DEBUG
	char buf[256];
	for (int i = 0; i < MAX_ORDER; i++) {
		sprintf_s(buf, "[%d] - %s | recipe:%d | pos:%.2f | time: %d/%d",
			i, list[i].isActive ? "on":"off" , list[i].recipe, list[i].position.x, list[i].count, list[i].times);
		Font_SetSize(20);
		Font_SetColor(255, 255, 255, 255);
		Font_Draw(10.0f, Common::screen_height - 30.0f - (i * 30.0f), buf);
	}
	sprintf_s(buf, "create timer : %d ", create_count);
	Font_SetSize(22);
	Font_SetColor(255, 255, 255, 255);
	Font_Draw(10.0f, Common::screen_height - 30.0f - (MAX_ORDER * 30.0f), buf);

	sprintf_s(buf, "TIMER : %+08d", timer);
	Font_SetSize(30);
	Font_SetColor(255, 255, 255, 255);
	Font_Draw(Common::screen_width - 200, Common::screen_height - 140.0f, buf);
#endif // _DEBUG

}

void Emitter::Submit(int index)
{
	for (int i = 0; i < MAX_ORDER; i++) {
		if (list[i].isActive == 1) {
			if (list[i].recipe + 3 == index) {
				// Plus Score
				timer -= 500.0f;
				score += Recipe::getScore(i);
				// Delete this Order
				Delete(i);
				return;
			}
		}
	}
	// Error check
	score -= 1000;
}

int Emitter::getScore()
{
	return score;
}

bool Emitter::isEnd()
{
	return timer > TIME_LIMIT;
}

void Emitter::Delete(int index)
{
	// TODO delete insert index number from list
	list[index].isActive = 0;
	list[index].recipe = Attraction::ATTRACTION_UNKNOWN;
	list[index].position = D3DXVECTOR2(Common::screen_width, 0.0f);
	list[index].times = 300;										// expire time
	list[index].count = 0;
}
