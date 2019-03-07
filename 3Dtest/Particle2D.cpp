#include "stdafx.h"
#include "Particle2D.h"
#include "texture.h"
#include "sprite.h"

#define BALLOON_X		(30)
#define BALLOON_Y		(75)

Particle2D::Particle2D()
{
	srand((unsigned)time(NULL));

	// cleanup list
	for (int i = 0; i < MAX_PARTICLE; i++) {
		deleteMember(i);
	}
}

Particle2D::~Particle2D()
{
}

void Particle2D::Spawn(int type)
{
	switch (type)
	{
	case 1:
		for (int i = 0; i < MAX_PARTICLE; i++) {
			if (pList[i].enable == 0) {
				pList[i].enable = 1;
				pList[i].type = 1;
				pList[i].position = D3DXVECTOR2(rand() % (int)Common::screen_width, Common::screen_height + BALLOON_Y);
				pList[i].direction = D3DXVECTOR2(0.0f, -1.0f);
				pList[i].speed = rand() % 5 * 0.1f + 0.5f;
				pList[i].life = 0;
				pList[i].lifespan = 600;
				break;
			}
		}
		break;
	default:
		break;
	}
}

void Particle2D::Update()
{
	for (int i = 0; i < MAX_PARTICLE; i++) {
		if (pList[i].enable == 1) {
			switch (pList[i].type)
			{
			case 1:
				pList[i].position += pList[i].direction * pList[i].speed;
				if (pList[i].position.y < -(float)BALLOON_Y / 2) deleteMember(i);
				break;
			default:
				break;
			}
			
		}
	}
}

void Particle2D::Draw()
{
	for (int i = 0; i < MAX_PARTICLE; i++) {
		if (pList[i].enable == 1) {
			switch (pList[i].type)
			{
			case 1:
				Sprite_Draw_Size(TEX_BALLOON, pList[i].position.x, pList[i].position.y, BALLOON_X, BALLOON_Y);
				break;
			default:
				break;
			}
			
		}
	}
}

void Particle2D::deleteMember(int index)
{
	pList[index].enable = 0;
	pList[index].type = 0;
	pList[index].position = D3DXVECTOR2(0.0f, 0.0f);
	pList[index].direction = D3DXVECTOR2(0.0f, 0.0f);
	pList[index].speed = 0;
	pList[index].life = 0;
	pList[index].lifespan = 0;
}