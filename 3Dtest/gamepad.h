//=============================================================================
//
// �R���g���[���[���͏���
//
//=============================================================================
#pragma once
#include "stdafx.h"

#ifndef GAMEPAD_H_
#define GAMEPAD_H_

#define DIRECTINPUT_VERSION (0x0800)
#include <iostream>
#include <Windows.h>
#include <Xinput.h>
#pragma comment (lib, "xinput.lib")

bool Gamepad_Initialize(void);
void Gamepad_Update(void);
bool Gamepad_isPress(int button);
bool Gamepad_isTrigger(int button);
bool Gamepad_GetLeftTrigger(void);
bool Gamepad_GetRightTrigger(void);
// Analog�p
float Gamepad_GetLX(void);
float Gamepad_GetLY(void);
float Gamepad_GetRX(void);
float Gamepad_GetRY(void);
// �k�x
void Gamepad_Vibrate(int speed, int time);			// speed�̍ō���65535 time���b�̒P�ʂ�

#endif