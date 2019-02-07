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
			dir += *vecSpeedFront;
			isWalk = true;

		}
		if (Keyboard_IsPress(DIK_S))
		{
			dir -= *vecSpeedFront;
			isWalk = true;
		}
		if (Keyboard_IsPress(DIK_A))
		{
			//cal the left of vecSpeedFront
			D3DXMATRIX left;
			D3DXMatrixIdentity(&left);
			D3DXMatrixRotationY(&left, D3DXToRadian(-90));
			D3DXVECTOR3 vecLeft;
			D3DXVec3TransformNormal(&vecLeft, vecSpeedFront, &left);

			dir += vecLeft;
			isWalk = true;
		}
		if (Keyboard_IsPress(DIK_D))
		{
			//cal the right of vecSpeedFront
			D3DXMATRIX right;
			D3DXMatrixIdentity(&right);
			D3DXMatrixRotationY(&right, D3DXToRadian(90));
			D3DXVECTOR3 vecRight;
			D3DXVec3TransformNormal(&vecRight, vecSpeedFront, &right);

			dir += vecRight;
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

	//float speedSum = D3DXVec3LengthSq(getVecMoveSpeed());
	//if (getIsWithAnimation())
	//{
	//	if (Physics::round(speedSum, FLOAT_BITS) != 0)
	//	{
	//		setIsPlayAnimation(true);
	//	}
	//	else
	//	{
	//		setIsPlayAnimation(false);
	//		resetAnimation();
	//	}
	//}

	Chara::dataUpdate();
}

void Player::setIsReadInput(bool isi)
{
	isReadInput = isi;
}

D3DXVECTOR3 * Player::getVecSpeedFront(void)
{
	return vecSpeedFront;
}

void Player::setVecSpeedFront(D3DXVECTOR3 * vecspeedFront)
{
	safe_delete<D3DXVECTOR3>(this->vecSpeedFront);
	this->vecSpeedFront = new D3DXVECTOR3(*vecspeedFront);
	D3DXVec3Normalize(this->vecSpeedFront, this->vecSpeedFront);
}
