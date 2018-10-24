#include <typeinfo>
#include "stdafx.h"
#include "Common.h"

LPDIRECT3D9 Common::g_pD3D = NULL;
D3DPRESENT_PARAMETERS Common::g_D3DPP = {};
LPDIRECT3DDEVICE9 Common::g_pD3DDevice = NULL;
D3DVIEWPORT9 Common::vp = {};
UINT Common::frameCount = 0;
FLOAT Common::screen_width = 1024;
FLOAT Common::screen_height = 768;

Common::Common()
{
}


Common::~Common()
{
}

//template <typename T>
//void Common::safe_delete(T *&target) {
//	if (nullptr != target) {
//		delete[] target;
//		target = nullptr;
//	}
//}
//
//template<typename T>
//void Common::safe_delete_arr(T *& target, int num)
//{
//	if (nullptr != target) {
//		for (int i = 0; i < num; i++)
//		{
//			if(nullprt != target[i])
//				delete target[i];
//				target[i] = nullptr;
//		}
//		delete[] target;
//		target = nullptr;
//	}
//}
