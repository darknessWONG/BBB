#pragma once

#include "stdafx.h"
#include "Common.h"

#define MAX_PARTICLE	(128)

class Particle2D
{
public:
	Particle2D();
	~Particle2D();

	void Spawn(int type);		// paticleÇÃê∂éY
	void Update();
	void Draw();

private:

	typedef struct Particle2D_tag {
		int enable;
		int type;						// type 1 = balloon random spawn
		D3DXVECTOR2 position;
		D3DXVECTOR2 direction;
		float speed;
		int life;
		int lifespan;
	}Particle2DList;
	
	Particle2DList pList[MAX_PARTICLE];

	void deleteMember(int index);		// paticleÇÃè¡Ç∑
	
};
