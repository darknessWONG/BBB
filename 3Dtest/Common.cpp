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

bool Common::MyDirect3D_Initialize(HWND hWnd)
{
	// Direct3Dの初期化
	// Direct3Dインターフェースの取得
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL) {
		// Direct3Dインターフェースの取得に失敗
		MessageBox(hWnd, "Direct3Dインターフェースの作成に失敗しました", "エラー", MB_OK);
		return false;
	}

	// デバイスの生成に利用する情報構造体の作成
	D3DPRESENT_PARAMETERS d3dpp = {};

	d3dpp.BackBufferWidth = screen_width;                       // バックバッファの横幅				
	d3dpp.BackBufferHeight = screen_height;                     // バックバッファの縦幅
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;                    // バックバッファのフォーマット指定
	d3dpp.BackBufferCount = 1;                                  // バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                   // スワップエフェクト（スワップ方法）の設定		
	d3dpp.Windowed = TRUE;                                      // ウィンドウモード or フルスクリーン
	d3dpp.EnableAutoDepthStencil = TRUE;                        // 深度バッファ・ステンシルバッファの使用				
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                  // 深度バッファ・ステンシルバッファのフォーマット指定
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // フルスクリーン時のリフレッシュレートの指定
																// d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;       // リフレッシュレートとPresent処理の関係
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;       // リフレッシュレートとPresent処理の関係

																		// Direct3Dデバイスの取得
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))) {
		// デバイスの作成に失敗
		MessageBox(hWnd, "Direct3Dデバイスの作成に失敗しました", "エラー", MB_OK);
		return false;
	}

	// サンプラーの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// アルファブレンドの設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// 頂点カラーとテクスチャのブレンド設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	return true;
}

void Common::MyDirect3D_Finalize(void)
{
	// Direct3Dデバイスの解放
	if (g_pD3DDevice) {
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3Dインターフェースの解放
	if (g_pD3D) {
		g_pD3D->Release();
		g_pD3D = NULL;
	}
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
