#include "stdafx.h"
//// 3Dtest.cpp : 定义应用程序的入口点。
////
//
//#include "stdafx.h"
//#include "3Dtest.h"
//#include "Common.h"
//#include "debugPrintf.h"
//#include <d3dx9.h>
//
//static void InitGame(HINSTANCE hInstance, HWND hWnd);
//static void CreateMesh(void);
//static void Transform(void);
//static void onRender(void);
//
//#define MAX_LOADSTRING 100
//#define SAFE_RELEASE(p) {if(p) {(p)->Release(); (p) = NULL;}} 
//
//// 全局变量: 
//HINSTANCE hInst;                                // 当前实例
//WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
//WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
//
//static LPD3DXMESH g_pMesh = NULL;  //网格对象
//LPDIRECT3DTEXTURE9* g_pTextures = NULL;			//网格纹理信息
//static DWORD g_dwNumMtrls = 0;  //网格材质数目
//static D3DMATERIAL9* g_pMaterials = NULL;  //网格材质信息
//
//
//// 此代码模块中包含的函数的前向声明: 
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//
////int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
////                     _In_opt_ HINSTANCE hPrevInstance,
////                     _In_ LPWSTR    lpCmdLine,
////                     _In_ int       nCmdShow)
////{
////    UNREFERENCED_PARAMETER(hPrevInstance);
////    UNREFERENCED_PARAMETER(lpCmdLine);
////
////    // TODO: 在此放置代码。
////
////    // 初始化全局字符串
////    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
////    LoadStringW(hInstance, IDC_MY3DTEST, szWindowClass, MAX_LOADSTRING);
////    MyRegisterClass(hInstance);
////
////    // 执行应用程序初始化: 
////    if (!InitInstance (hInstance, nCmdShow))
////    {
////        return FALSE;
////    }
////
////    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3DTEST));
////
////    MSG msg;
////
////
////    // 主消息循环: 
////    while (GetMessage(&msg, nullptr, 0, 0))
////    {
////        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
////        {
////            TranslateMessage(&msg);
////            DispatchMessage(&msg);
////        }
////		onRender();
////    }
////
////    return (int) msg.wParam;
////}
//
//
//
////
////  函数: MyRegisterClass()
////
////  目的: 注册窗口类。
////
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//    WNDCLASSEXW wcex;
//
//    wcex.cbSize = sizeof(WNDCLASSEX);
//
//    wcex.style          = CS_HREDRAW | CS_VREDRAW;
//    wcex.lpfnWndProc    = WndProc;
//    wcex.cbClsExtra     = 0;
//    wcex.cbWndExtra     = 0;
//    wcex.hInstance      = hInstance;
//    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3DTEST));
//    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
//    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
//    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY3DTEST);
//    wcex.lpszClassName  = szWindowClass;
//    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//    return RegisterClassExW(&wcex);
//}
//
////
////   函数: InitInstance(HINSTANCE, int)
////
////   目的: 保存实例句柄并创建主窗口
////
////   注释: 
////
////        在此函数中，我们在全局变量中保存实例句柄并
////        创建和显示主程序窗口。
////
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//   hInst = hInstance; // 将实例句柄存储在全局变量中
//
//   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
//
//   if (!hWnd)
//   {
//      return FALSE;
//   }
//
//   ShowWindow(hWnd, nCmdShow);
//   UpdateWindow(hWnd);
//
//   InitGame(hInstance, hWnd);
//   CreateMesh();
//
//   return TRUE;
//}
//
////
////  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
////
////  目的:    处理主窗口的消息。
////
////  WM_COMMAND  - 处理应用程序菜单
////  WM_PAINT    - 绘制主窗口
////  WM_DESTROY  - 发送退出消息并返回
////
////
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    switch (message)
//    {
//    case WM_COMMAND:
//        {
//            int wmId = LOWORD(wParam);
//            // 分析菜单选择: 
//            switch (wmId)
//            {
//            case IDM_ABOUT:
//                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//                break;
//            case IDM_EXIT:
//                DestroyWindow(hWnd);
//                break;
//            default:
//                return DefWindowProc(hWnd, message, wParam, lParam);
//            }
//        }
//        break;
//    case WM_PAINT:
//        {
//            PAINTSTRUCT ps;
//            HDC hdc = BeginPaint(hWnd, &ps);
//            // TODO: 在此处添加使用 hdc 的任何绘图代码...
//            EndPaint(hWnd, &ps);
//        }
//        break;
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}
//
//// “关于”框的消息处理程序。
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}
//
//static void InitGame(HINSTANCE hInstance, HWND hWnd)
//{
//	Common::g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
//	if (Common::g_pD3D == NULL)
//	{
//		return;
//	}
//
//	ZeroMemory(&Common::g_D3DPP, sizeof(Common::g_D3DPP)); //set the memory tobe 0
//	Common::g_D3DPP.Windowed = TRUE; //window mode
//	Common::g_D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD; //frame swap mode
//	//Common::g_D3DPP.BackBufferFormat = D3DFMT_UNKNOWN; //back frame format
//	Common::g_D3DPP.BackBufferFormat = D3DFMT_A8R8G8B8; //back frame format
//	Common::g_D3DPP.BackBufferWidth = Common::screen_width; //back frame's width
//	Common::g_D3DPP.BackBufferHeight = Common::screen_height; //back frame's height
//	Common::g_D3DPP.BackBufferCount = 2; //back frame num
//	Common::g_D3DPP.MultiSampleType = D3DMULTISAMPLE_NONE;
//	Common::g_D3DPP.MultiSampleQuality = 0;
//	Common::g_D3DPP.hDeviceWindow = hWnd;
//	Common::g_D3DPP.EnableAutoDepthStencil = TRUE; //
//	Common::g_D3DPP.AutoDepthStencilFormat = D3DFMT_D24S8;
//	//g_D3DPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //fps control
//	Common::g_D3DPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
//	Common::g_D3DPP.FullScreen_RefreshRateInHz = 0; //refresh rate when full screen mode
//	//Common::g_D3DPP.Flags = D3DPRESENTFLAG_VIDEO;
//	Common::g_D3DPP.Flags = 0;
//
//
//
//
//	HRESULT hr = Common::g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
//		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &Common::g_D3DPP, &Common::g_pD3DDevice);
//
//	if (FAILED(hr))
//	{
//		return;
//	}
//
//	Common::vp.X = 0;
//	Common::vp.Y = 0;
//	Common::vp.Width = Common::g_D3DPP.BackBufferWidth;
//	Common::vp.Height = Common::g_D3DPP.BackBufferHeight;
//	Common::vp.MaxZ = 1.0f;
//	Common::vp.MinZ = 0.0f;
//	hr = Common::g_pD3DDevice->SetViewport(&Common::vp);
//	if (FAILED(hr))
//	{
//		return;
//	}
//	Common::g_pD3DDevice->SetFVF(FVF_VERTEX3D);
//	Common::g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);
//	//Common::g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
//	Common::g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255, 255, 255));
//
//	Common::g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
//	//Keyboard_Initialize(hInstance, hWnd);
//
//}
//
//void CreateMesh(void)
//{
//	LPD3DXBUFFER pAdjBuffer = NULL;
//	LPD3DXBUFFER pMtrlBuffer = NULL;
//
//	//根据.X文件创建Mesh模型
//	D3DXLoadMeshFromX(TEXT("radio.blend.X"), D3DXMESH_MANAGED, Common::g_pD3DDevice, &pAdjBuffer, &pMtrlBuffer, NULL, &g_dwNumMtrls, &g_pMesh);
//
//	//读取材质和纹理数据
//	D3DXMATERIAL *pMtrl = (D3DXMATERIAL*)pMtrlBuffer->GetBufferPointer();
//	//真正存储材质以及纹理的缓冲区，动态申请内存
//	g_pMaterials = new D3DMATERIAL9[g_dwNumMtrls];
//	g_pTextures = new LPDIRECT3DTEXTURE9[g_dwNumMtrls];
//
//	//根据材质纹理数遍历，设置材质纹理信息
//	for (int i = 0; i < g_dwNumMtrls; i++)
//	{
//		g_pMaterials[i] = pMtrl[i].MatD3D; //设置材质
//		g_pMaterials[i].Ambient = g_pMaterials[i].Diffuse;	//设置环境光
//
//		g_pTextures[i] = NULL;
//		D3DXCreateTextureFromFileA(Common::g_pD3DDevice, pMtrl[i].pTextureFilename, &g_pTextures[i]);		//根据获得的纹理文件名创建纹理
//	}
//
//	g_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_STRIPREORDER | D3DXMESHOPT_ATTRSORT,
//		(DWORD*)pAdjBuffer->GetBufferPointer(), NULL, NULL, NULL);
//
//	//释放刚才传递给D3DXLoadMeshFromX函数的两个指针所指向的缓冲区
//	SAFE_RELEASE(pAdjBuffer);
//	SAFE_RELEASE(pMtrlBuffer);
//}
//
//void Transform(void)
//{
//	//WorldTransform:世界变换
//	D3DXMATRIXA16 matWorld;
//	D3DXMATRIXA16 matScaling;
//
//	//生成缩放矩阵
//	D3DXMatrixScaling(&matScaling, 3.0f, 3.0f, 3.0f);
//
//	//生成绕Y轴旋转矩阵，存储于矩阵中
//	D3DXMatrixRotationY(&matWorld, 10.0f);
//
//	D3DXMatrixMultiply(&matWorld, &matWorld, &matScaling);
//	Common::g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
//
//
//	//view matrix
//	D3DXMATRIX g_cubeMtxView;
//	D3DXVECTOR3 camera_position = { 0.0f, 10.0f, 10.0f };
//	D3DXVECTOR3 camera_up = { 0.0f, 1.0f, 0.0f };
//	D3DXVECTOR3 camera_watch_at = { 0.0f, 0.0f, 0.0f };
//	D3DXMatrixLookAtLH(&g_cubeMtxView, &camera_position, &camera_watch_at, &camera_up);
//	Common::g_pD3DDevice->SetTransform(D3DTS_VIEW, &g_cubeMtxView);
//
//	//projection matirx
//	D3DXMATRIX g_cubeMtxProjection;
//	//visual angle, Screen ratio, near point, far point
//	D3DXMatrixPerspectiveFovLH(&g_cubeMtxProjection, D3DXToRadian(60), (float)Common::screen_width / Common::screen_height, 0.1f, 100.0f);
//	Common::g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &g_cubeMtxProjection);
//
//
//}
//
//void onRender(void)
//{
//	Common::g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 100, 100), 1.0f, 0);
//
//	Common::g_pD3DDevice->BeginScene();
//
//	Transform();
//	for (int i = 0; i < g_dwNumMtrls; i++)
//	{
//		Common::g_pD3DDevice->SetMaterial(&g_pMaterials[i]);
//		Common::g_pD3DDevice->SetTexture(0, g_pTextures[i]);
//		g_pMesh->DrawSubset(i);
//
//	}
//	Common::g_pD3DDevice->EndScene();
//
//	Common::g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
//}