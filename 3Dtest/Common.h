#pragma once
/*==============================================================================

Global values[Common.h]
Author : darknessWONG
Date   : 2018/11/23
--------------------------------------------------------------------------------

==============================================================================*/
#include <d3dx9.h>

class Common
{
public:
	Common();
	~Common();

	static LPDIRECT3D9 g_pD3D;
	static D3DPRESENT_PARAMETERS g_D3DPP;
	static LPDIRECT3DDEVICE9 g_pD3DDevice;
	static D3DVIEWPORT9 vp;
	static UINT frameCount;
	static FLOAT screen_width;
	static FLOAT screen_height;

	static bool MyDirect3D_Initialize(HWND hWnd);
	static void MyDirect3D_Finalize(void);
};

template <typename T>
inline void safe_delete(T *&target) {
	if (nullptr != target) {
		delete target;
		target = nullptr;
	}
}


template<typename T>
inline void safe_delete_arr(T *& target, int num)
{
	if (nullptr != target) {
		for (int i = 0; i < num; i++)
		{
			if (nullprt != target[i])
				delete target[i];
			target[i] = nullptr;
		}
		delete[] target;
		target = nullptr;
	}
}