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
	// Direct3D�̏�����
	// Direct3D�C���^�[�t�F�[�X�̎擾
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL) {
		// Direct3D�C���^�[�t�F�[�X�̎擾�Ɏ��s
		MessageBox(hWnd, "Direct3D�C���^�[�t�F�[�X�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return false;
	}

	// �f�o�C�X�̐����ɗ��p������\���̂̍쐬
	D3DPRESENT_PARAMETERS d3dpp = {};

	d3dpp.BackBufferWidth = screen_width;                       // �o�b�N�o�b�t�@�̉���				
	d3dpp.BackBufferHeight = screen_height;                     // �o�b�N�o�b�t�@�̏c��
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;                    // �o�b�N�o�b�t�@�̃t�H�[�}�b�g�w��
	d3dpp.BackBufferCount = 1;                                  // �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                   // �X���b�v�G�t�F�N�g�i�X���b�v���@�j�̐ݒ�		
	d3dpp.Windowed = TRUE;                                      // �E�B���h�E���[�h or �t���X�N���[��
	d3dpp.EnableAutoDepthStencil = TRUE;                        // �[�x�o�b�t�@�E�X�e���V���o�b�t�@�̎g�p				
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                  // �[�x�o�b�t�@�E�X�e���V���o�b�t�@�̃t�H�[�}�b�g�w��
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // �t���X�N���[�����̃��t���b�V�����[�g�̎w��
																// d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;       // ���t���b�V�����[�g��Present�����̊֌W
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;       // ���t���b�V�����[�g��Present�����̊֌W

																		// Direct3D�f�o�C�X�̎擾
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))) {
		// �f�o�C�X�̍쐬�Ɏ��s
		MessageBox(hWnd, "Direct3D�f�o�C�X�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return false;
	}

	// �T���v���[�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// �A���t�@�u�����h�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���_�J���[�ƃe�N�X�`���̃u�����h�ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	return true;
}

void Common::MyDirect3D_Finalize(void)
{
	// Direct3D�f�o�C�X�̉��
	if (g_pD3DDevice) {
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3D�C���^�[�t�F�[�X�̉��
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
