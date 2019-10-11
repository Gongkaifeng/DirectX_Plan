// Win32.cpp : 定义应用程序的入口点。
#include "stdafx.h"
#include "Win32.h"

#define MAX_LOADSTRING 100
#pragma region 全局变量
HWND				hWnd;
HINSTANCE			hInst;                              // 当前实例
WCHAR				szTitle[MAX_LOADSTRING];            // 标题栏文本
WCHAR				szWindowClass[MAX_LOADSTRING];      // 主窗口类名
RECT				g_clientRC;							// 客户区RC
CDirectInput		g_DXInput;							// 比较好的方向库
D3DVECTOR			LineText;
bool				flag = false;

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
#pragma endregion

void InitD3D(HWND hWnd)		//初始化
{
	CGameManager::GetGameInstance()->InitD3D(hWnd);

	g_DXInput.Init(hWnd, hInst,
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE,	    //协作级别（前台后台，独占非独占）  
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);		//协作级别（前台后台，独占非独占）  	
}
void Init()
{
	CGameManager::GetGameInstance()->Init();
}
void Update()//逻辑更新（数据处理）
{	
	CGameManager::GetGameInstance()->Update();
}
void Render()//渲染（显示图片）
{
	CGameManager::GetGameInstance()->Render();
}
void Destory()//销毁
{
	if (CGameManager::GetGameInstance()->Direct3D != NULL)
		CGameManager::GetGameInstance()->Direct3D->Release();
	if (CGameManager::GetGameInstance()->D3DDevice != NULL)
		CGameManager::GetGameInstance()->D3DDevice->Release();
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
    // TODO: 在此放置代码。
	
	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WIN32, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
        return FALSE;

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32));
	
	InitD3D(hWnd);
	Init();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

    // 主消息循环: 
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		else
		{
			Update();
			Render();
		}	
    }

	Destory();
    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_WIN32));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WIN32);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中
   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, /*CW_USEDEFAULT, 0,*/ 900,900,nullptr, nullptr, hInstance, nullptr);//win32窗口的属性
   if (!hWnd)
   {
      return FALSE;
   }
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (flag == true)
		CUIManager::GetInstance()->WndProc(hWnd, message, wParam, lParam);
	
    switch (message)
    {
	case WM_CREATE:
		flag = true;
		break;
    //case WM_COMMAND:
    //    {
    //        int wmId = LOWORD(wParam);
    //        // 分析菜单选择: 
    //        switch (wmId)
    //        {
    //        case IDM_ABOUT:
    //            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
    //            break;
    //        case IDM_EXIT:
    //            DestroyWindow(hWnd);
    //            break;
    //        default:
    //            return DefWindowProc(hWnd, message, wParam, lParam);
    //        }
    //    }
    //    break;
    //case WM_PAINT:
    //    {
    //        PAINTSTRUCT ps;
    //        HDC hdc = BeginPaint(hWnd, &ps);
    //        // TODO: 在此处添加使用 hdc 的任何绘图代码...
    //        EndPaint(hWnd, &ps);
    //    }
    //    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
