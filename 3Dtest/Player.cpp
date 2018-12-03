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
	if (Keyboard_IsTrigger(DIK_SPACE))
	{
		if (holdings == NULL)
		{
			findHoldings = true;
		}
		else
		{
			releaseHoldings();
		}
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

void Player::releaseHoldings(void)
{
	holdings->setBelong(NULL);
	holdings = NULL;
}

bool Player::getFindHoldings(void)
{
	return findHoldings;
}

void Player::setFindHoldings(bool findHoldings)
{
	this->findHoldings = findHoldings;
}

Item * Player::getHoldings(void)
{
	return holdings;
}

void Player::setHoldings(Item * item)
{
	this->holdings = item;
}
