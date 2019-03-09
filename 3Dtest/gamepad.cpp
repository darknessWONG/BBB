#include "stdafx.h"
#include "gamepad.h"


#define DIRECTINPUT_VERSION (0x0800)
#include <iostream>
#include <Windows.h>
#include <Xinput.h>
#pragma comment (lib, "xinput.lib")

#include <math.h>

#define DEADZONEX (0.10f)
#define DEADZONEY (0.10f)
#define MAX_PRESS	(16)

static XINPUT_STATE state;
static XINPUT_VIBRATION vibration;
static DWORD dwResult;
static int playerID;

static int motorSpeed;
static int timer;
static int curPress[MAX_PRESS];

static float leftStickX;
static float leftStickY;
static float rightStickX;
static float rightStickY;

static float normLX;
static float normLY;
static float normRX;
static float normRY;

bool Gamepad_Initialize(void)
{
	timer = 0;
	motorSpeed = 0;

	for (DWORD i = 0; i< XUSER_MAX_COUNT; i++)
	{
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(i, &state);

		if (dwResult == ERROR_SUCCESS)
		{
			// Controller is connected 
			playerID = i;
			return 1;
		}
		else
		{
			// Controller is not connected 
		}
	}

	for (int i = 0; i < MAX_PRESS; i++) {
		curPress[i] = 0;
	}

	return 0;
}


void Gamepad_Update(void) 
{
	XInputGetState(playerID, &state);

	normLX = fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);
	normLY = fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);
	normRX = fmaxf(-1, (float)state.Gamepad.sThumbRX / 32767);
	normRY = fmaxf(-1, (float)state.Gamepad.sThumbRY / 32767);

	leftStickX = (abs(normLX) < DEADZONEX ? 0 : (abs(normLX) - DEADZONEX) * (normLX / abs(normLX)));
	leftStickY = (abs(normLY) < DEADZONEY ? 0 : (abs(normLY) - DEADZONEY) * (normLY / abs(normLY)));
	rightStickX = (abs(normRX) < DEADZONEX ? 0 : (abs(normRX) - DEADZONEX) * (normRX / abs(normRX)));
	rightStickY = (abs(normRY) < DEADZONEY ? 0 : (abs(normRY) - DEADZONEY) * (normRY / abs(normRY)));
	
	if (timer > 0) timer--;
	if (timer <= 0) motorSpeed = 0;

	vibration.wLeftMotorSpeed = motorSpeed;
	vibration.wRightMotorSpeed = motorSpeed;
	XInputSetState(playerID, &vibration);

	for (int i = 0; i < MAX_PRESS; i++) {
		if (!Gamepad_isPress(curPress[i])) {
			curPress[i] = 0;
		}
	}
	
}

void Gamepad_Vibrate(int speed, int time)
{
	motorSpeed = speed;
	timer = time;
}

bool Gamepad_isPress(int button) {
	if ((state.Gamepad.wButtons & button)) {
		return true;
	}
	return false;
}

bool Gamepad_isTrigger(int button)
{
	if (state.Gamepad.wButtons & button) {
		for (int i = 0; i < MAX_PRESS; i++) {
			if (curPress[i] == button) {
				return false;
			}
		}
		for (int i = 0; i < MAX_PRESS; i++) {
			if (curPress[i] == 0) {
				curPress[i] = button;
				break;
			}
		}
		return true;
	}
	return false;
}

bool Gamepad_GetLeftTrigger(void) {
	if (state.Gamepad.bLeftTrigger >= 255 / 2)
	{
		return true;
	}
	return false;
}

bool Gamepad_GetRightTrigger(void) {
	if (state.Gamepad.bRightTrigger >= 255 / 2)
	{
		return true;
	}
	return false;
}

float Gamepad_GetLX(void) {
	return leftStickX;
}

float Gamepad_GetLY(void) {
	return leftStickY;
}

float Gamepad_GetRX(void) {
	return rightStickX;
}

float Gamepad_GetRY(void) {
	return rightStickY;
}