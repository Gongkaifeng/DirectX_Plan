#include "stdafx.h"
#include "DirectInput.h"  

#define SAFE_RELEASE(p) {if(p) {(p)->Release(); (p) = NULL;}}  
//添加库文件  
#pragma comment(lib, "dinput8.lib")  
#pragma comment(lib, "dxguid.lib")  
CDirectInput::CDirectInput(void)
{
	//赋初值  
	m_pDirectInput = NULL;
	m_KeyboardDevice = NULL;
	m_MouseDevice = NULL;

	ZeroMemory(m_keyBuffer, sizeof(m_keyBuffer));
	ZeroMemory(&m_MouseState, sizeof(m_MouseState));
}
CDirectInput::~CDirectInput(void)
{
	//释放对象  
	if (m_KeyboardDevice)
		m_KeyboardDevice->Unacquire();
	if (m_MouseDevice)
		m_MouseDevice->Unacquire();
	SAFE_RELEASE(m_MouseDevice);
	SAFE_RELEASE(m_KeyboardDevice);
	SAFE_RELEASE(m_pDirectInput);
}

HRESULT CDirectInput::Init(HWND hWnd, HINSTANCE hInstance, DWORD keyboardCoopFlags, DWORD mouseCoopFlags)
{
	//初始化接口对象  
	DirectInput8Create(
		hInstance,                  //程序实例的句柄  
		DIRECTINPUT_VERSION,        //0x0800当前使用的DirectInput版本号  
		IID_IDirectInput8,          //接口标识，使用IID_IDirectInput8即可  
		(void**)&m_pDirectInput,    //创建的接口的对象的指针  
		NULL);                      //COM对象相关联参数，为NULL  
	//初始化键盘设备  
	m_pDirectInput->CreateDevice(       //创建设备  
		GUID_SysKeyboard,              //GUID值，对于鼠标和键盘有宏定义，其余设备需要通过枚举找出  
		&m_KeyboardDevice,             //键盘设备指针的指针  
		NULL);                           //COM相关参数，为NULL  
	m_KeyboardDevice->SetCooperativeLevel(//设置协作级别  
		hWnd,                              //窗口句柄  
		keyboardCoopFlags);                  //协作级别（前台后台，独占非独占）  
	m_KeyboardDevice->SetDataFormat(        //设置数据格式  
		&c_dfDIKeyboard);                  //键盘鼠标等的数据格式，宏定义  
	m_KeyboardDevice->Acquire();            //获得设备控制权  
	m_KeyboardDevice->Poll();               //轮询设备  
	//初始化鼠标设备  
	m_pDirectInput->CreateDevice(GUID_SysMouse, &m_MouseDevice, NULL);
	m_MouseDevice->SetCooperativeLevel(hWnd, mouseCoopFlags);
	m_MouseDevice->SetDataFormat(&c_dfDIMouse);
	m_MouseDevice->Acquire();
	m_MouseDevice->Poll();
	m_hWnd = hWnd;
	return true;
}

void CDirectInput::GetInput()
{
	//将上一次的按键信息更新
	memcpy(m_keyBufferlast, m_keyBuffer, 256);
	//获得键盘输入消息  
	HRESULT hr = m_KeyboardDevice->GetDeviceState(sizeof(m_keyBuffer), (void**)&m_keyBuffer);
	if (FAILED(hr))//如果失败尝试重新获取
	{
		m_KeyboardDevice->Acquire();//获取键盘控制
		m_KeyboardDevice->GetDeviceState(sizeof(m_keyBuffer), (void**)&m_keyBuffer);
	}

	//将上一次的鼠标信息更新
	memcpy(&m_MouseLastState, &m_MouseState, sizeof(m_MouseState));
	//获得鼠标输入信息  
	hr = m_MouseDevice->GetDeviceState(sizeof(m_MouseState), (void**)&m_MouseState);
	if (FAILED(hr))//如果失败尝试重新获取
	{
		m_MouseDevice->Acquire();//获取鼠标控制
		m_MouseDevice->GetDeviceState(sizeof(m_MouseState), (void**)&m_MouseState);
	}
}

bool CDirectInput::IsKeyCurrentDown(int iKey)
{
	if (((m_keyBuffer[iKey] & 0x80) != 0) && ((m_keyBufferlast[iKey] & 0x80) == 0))
		return true;
	return false;
}
bool CDirectInput::IsKeyHold(int iKey)
{
	if (m_keyBuffer[iKey] & 0x80)
		return true;
	return false;
}
bool CDirectInput::IsKeyCurrentUp(int iKey)
{
	if (((m_keyBuffer[iKey] & 0x80) == 0) && ((m_keyBufferlast[iKey] & 0x80) != 0))
		return true;
	return false;
}
bool CDirectInput::IsKeyUp(int iKey)
{
	if (((m_keyBuffer[iKey] & 0x80) == 0) && ((m_keyBufferlast[iKey] & 0x80) == 0))
		return true;
	return false;
}

bool CDirectInput::IsMouseButtonCurrentDown(int iButton)
{
	if (((m_MouseState.rgbButtons[iButton] & 0x80) != 0) && (m_MouseLastState.rgbButtons[iButton] & 0x80) == 0)
		return true;
	return false;
}
bool CDirectInput::IsMouseButtonHold(int iButton)
{
	return (m_MouseState.rgbButtons[iButton] & 0x80) != 0;
}
bool CDirectInput::IsMouseButtonCurrentUp(int iButton)
{
	if (((m_MouseState.rgbButtons[iButton] & 0x80) == 0) && (m_MouseLastState.rgbButtons[iButton] & 0x80) != 0)
		return true;
	return false;
}
bool CDirectInput::IsMouseButtonUp(int iButton)
{
	if (((m_MouseState.rgbButtons[iButton] & 0x80) == 0) && (m_MouseLastState.rgbButtons[iButton] & 0x80) == 0)
		return true;
	return false;
}

float CDirectInput::MouseX()
{
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(m_hWnd, &pos);
	return pos.x;
}

float CDirectInput::MouseY()
{
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(m_hWnd, &pos);
	return pos.y;
}
void CDirectInput::MousePosition(LPPOINT pos)
{
	GetCursorPos(pos);
	ScreenToClient(m_hWnd, pos);
}

float CDirectInput::MouseDX()
{
	return (float)m_MouseState.lX;
}

float CDirectInput::MouseDY()
{
	return (float)m_MouseState.lY;
}

float CDirectInput::MouseDZ()
{
	return (float)m_MouseState.lZ;
}