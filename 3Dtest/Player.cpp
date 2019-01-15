#include "stdafx.h"
#include "Player.h"
#include "input.h"


Player::Player()
{
}

Player::Player(string modelPath)
	:Chara(modelPath)
{
}


Player::~Player()
{
}

void Player::dataUpdate(void)
{
	D3DXVECTOR3 dir = { 0.0f, 0.0f, 0.0f };
	bool isWalk = false;
	if (isReadInput)
	{
		if (Keyboard_IsPress(DIK_W))
		{
			dir.z += 1;
			isWalk = true;

		}
		if (Keyboard_IsPress(DIK_S))
		{
			dir.z -= 1;
			isWalk = true;
		}
		if (Keyboard_IsPress(DIK_A))
		{
			dir.x -= 1;
			isWalk = true;
		}
		if (Keyboard_IsPress(DIK_D))
		{
			dir.x += 1;
			isWalk = true;
		}
		isReadInput = false;
	}

	if (true == isWalk)
	{
		addSpeed(&dir, getWalkSpeed());
		D3DXVECTOR3 nowSpeed = *getVecMoveSpeed();
		D3DXVec3Normalize(&nowSpeed, &nowSpeed);
		setVecTargetFront(&nowSpeed);
	}

	Chara::dataUpdate();
}

void Player::setIsReadInput(bool isi)
{
	isReadInput = isi;
}
