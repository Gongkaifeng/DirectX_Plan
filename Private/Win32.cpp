// Win32.cpp : ����Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include "Win32.h"

#define MAX_LOADSTRING 100
#pragma region ȫ�ֱ���
HWND				hWnd;
HINSTANCE			hInst;                              // ��ǰʵ��
WCHAR				szTitle[MAX_LOADSTRING];            // �������ı�
WCHAR				szWindowClass[MAX_LOADSTRING];      // ����������
RECT				g_clientRC;							// �ͻ���RC
CDirectInput		g_DXInput;							// �ȽϺõķ����
D3DVECTOR			LineText;
bool				flag = false;

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
#pragma endregion

void InitD3D(HWND hWnd)		//��ʼ��
{
	CGameManager::GetGameInstance()->InitD3D(hWnd);

	g_DXInput.Init(hWnd, hInst,
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE,	    //Э������ǰ̨��̨����ռ�Ƕ�ռ��  
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);		//Э������ǰ̨��̨����ռ�Ƕ�ռ��  	
}
void Init()
{
	CGameManager::GetGameInstance()->Init();
}
void Update()//�߼����£����ݴ���
{	
	CGameManager::GetGameInstance()->Update();
}
void Render()//��Ⱦ����ʾͼƬ��
{
	CGameManager::GetGameInstance()->Render();
}
void Destory()//����
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
    // TODO: �ڴ˷��ô��롣
	
	// ��ʼ��ȫ���ַ���
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WIN32, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
        return FALSE;

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32));
	
	InitD3D(hWnd);
	Init();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

    // ����Ϣѭ��: 
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
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����
   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, /*CW_USEDEFAULT, 0,*/ 900,900,nullptr, nullptr, hInstance, nullptr);//win32���ڵ�����
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
    //        // �����˵�ѡ��: 
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
    //        // TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
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
