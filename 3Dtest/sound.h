//=============================================================================
//
// サウンド処理
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "stdafx.h"
#include <windows.h>
#include "xaudio2.h"						// サウンド処理で必要

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_MUSIC_TITLE,
	SOUND_LABEL_MUSIC_GAME,
	SOUND_LABEL_SE_TEMP,
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
