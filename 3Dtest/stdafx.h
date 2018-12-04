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


#define FVF_VERTEX3D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define MOVEDAMPING 0.98f
#define ROTATEDAMPING 0.98f
#define FLOATBITS 5
#define ALPHAREF 10

typedef struct
{
	D3DXVECTOR3 position;
	D3DCOLOR color;
	D3DXVECTOR2 texPos;
}Vertex;
// TODO:  在此处引用程序需要的其他头文件
