// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <math.h>
#include <d3dx9.h>
#include <sstream>
#include <iomanip>

using namespace std;


#define FVF_VERTEX3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define MOVE_DAMPING (0.98f)
#define ROTATE_DAMPING (0.98f)
#define FLOAT_BITS (4)
#define ALPHAREF (10)

#define CUBE_FACE_NUM (6)
#define CUBE_FACE_VERTEX_NUM (4)
#define CUBE_FACE_INDEX_NUM (6)
#define CUBE_VERTEX_NUM (CUBE_FACE_NUM * CUBE_FACE_VERTEX_NUM)
#define CUBE_INDEX_NUM (CUBE_FACE_NUM * CUBE_FACE_INDEX_NUM)
#define CUBE_EDGE_LENGTH (1)

#define SKILL_EFFICIENCY (1.0f)
#define DEFENSE_EFFICIENCY (1.0f)

enum GameState
{
	GameStateTitleInit,
	GameStateTitleRunning,
	GameStateTitleClean,
	GameStateGameInit,
	GameStateGameRunning,
	GameStateGameClean,
	GameStateEndInit,
	GameStateEndRunning,
	GameStateEndClean,
	GameStateMax
};

enum BattleState
{
	BattleStateStandby,
	BattleStateCommand,
	BattleStateTaragetSelect,
	BattleStateMove,
	BattleStatePlaceSelect,
	BattleStateDamage,
	BattleStateMapMove,
	BattleStateEnd
};

enum ActionPhaseStatus
{
	ActionPhaseStatusActionZero,
	ActionPhaseStatusActionSelect,
	ActionPhaseStatusSkillSelect,
	ActionPhaseStatusTargetSelect,
	ActionPhaseStatusShowStatus,
	ActionPhaseStatusMpCheck
};

enum MovePhaseStatus
{
	MovePhaseStatusZero,
	MovePhaseStatusPlaceSelect,
	MovePhaseStatusMove
};

enum EffectTarget
{
	EffectTargetNoTarget,
	EffectTargetSelf,
	EffectTargetFriendly,
	EffectTargetAllFriendly,
	EffectTargetEnemy,
	EffectTargetAllEnemy
};

enum DamageType
{
	magic,
	physics
};

enum SideEffectType
{
	SideEffectTypeNormal,
	SideEffectTypeComa,
	SideEffectTypeTaunt,
	SideEffectTypePoison,
	SideEffectTypeParalysis,
	SideEffectTypeHpMaxUp,
	SideEffectTypeStrengthUp,
	SideEffectTypeIntelligenceUp,
	SideEffectTypeMentalityUp,
	SideEffectTypeSpeedUp,
	SideEffectTypeLuckUp,
	SideEffectTypeHpMaxDown,
	SideEffectTypeStrengthDown,
	SideEffectTypeIntelligenceDown,
	SideEffectTypeMentalityDown,
	SideEffectTypeSpeedDown,
	SideEffectTypeLuckDown,
	SideEffectTypeDamageImmune,
	SideEffectTypeDebuffImmune
};

enum CampType
{
	CampTypePlayer,
	CampTypeEnemy
};

enum UIIdentity
{
	UIIdentityAttack,
	UIIdentityRun,
	UIIdentityMove,
	UIIdentityUseSkill,
	UIIdentityTarget,
	UIIdentitySkill,
	UIIdentityMAX
};

enum BattleResultType
{
	BattleResultTypeUnknow,
	BattleResultTypeWin,
	BattleResultTypeLose
};

typedef struct
{
	D3DXVECTOR4 pos;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
}Vertex2D;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
}Vertex3D;
// TODO:  在此处引用程序需要的其他头文件
