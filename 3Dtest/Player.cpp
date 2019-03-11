#include "stdafx.h"
#include "Player.h"
#include "input.h"
#include "gamepad.h"
#include "sound.h"

Player::Player()
{
}


Player::~Player()
{
	holdings = NULL;
}

void Player::dataUpdate(void)
{
	findHoldings = false;
	D3DXVECTOR3 dir = { 0.0f, 0.0f, 0.0f };
	bool isWalk = false;
	if (Keyboard_IsPress(DIK_W) || Gamepad_isPress(XINPUT_GAMEPAD_DPAD_UP))
	{
		dir.z += 1;
		isWalk = true;
	}
	if (Keyboard_IsPress(DIK_S) || Gamepad_isPress(XINPUT_GAMEPAD_DPAD_DOWN))
	{
		dir.z -= 1;
		isWalk = true;
	}
	if (Keyboard_IsPress(DIK_A) || Gamepad_isPress(XINPUT_GAMEPAD_DPAD_LEFT))
	{
		dir.x -= 1;
		isWalk = true;
	}
	if (Keyboard_IsPress(DIK_D) || Gamepad_isPress(XINPUT_GAMEPAD_DPAD_RIGHT))
	{
		dir.x += 1;
		isWalk = true;
	}
	if (!isWalk) {
		dir.x += Gamepad_GetLX();
		dir.z += Gamepad_GetLY();
		isWalk = true;
	}
	if (Keyboard_IsTrigger(DIK_SPACE) || Gamepad_isTrigger(XINPUT_GAMEPAD_A))
	{
		if (getHoldings() == NULL)
		{
			findHoldings = true;
		}
		else
		{
			releaseHoldings();
			PlaySound(SOUND_LABEL_SE_DROP);
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

bool Player::getFindHoldings(void)
{
	return findHoldings;
}

void Player::setFindHoldings(bool findHoldings)
{
	this->findHoldings = findHoldings;
}


void Player::releaseHoldings(void)
{
	holdings->setBelong(NULL);
	holdings = NULL;
}


Item * Player::getHoldings(void)
{
	return holdings;
}

void Player::setHoldings(Item * item)
{
	this->holdings = item;
}
