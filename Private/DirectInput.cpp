#include "stdafx.h"
#include "DirectInput.h"  

#define SAFE_RELEASE(p) {if(p) {(p)->Release(); (p) = NULL;}}  
//��ӿ��ļ�  
#pragma comment(lib, "dinput8.lib")  
#pragma comment(lib, "dxguid.lib")  
CDirectInput::CDirectInput(void)
{
	//����ֵ  
	m_pDirectInput = NULL;
	m_KeyboardDevice = NULL;
	m_MouseDevice = NULL;

	ZeroMemory(m_keyBuffer, sizeof(m_keyBuffer));
	ZeroMemory(&m_MouseState, sizeof(m_MouseState));
}
CDirectInput::~CDirectInput(void)
{
	//�ͷŶ���  
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
	//��ʼ���ӿڶ���  
	DirectInput8Create(
		hInstance,                  //����ʵ���ľ��  
		DIRECTINPUT_VERSION,        //0x0800��ǰʹ�õ�DirectInput�汾��  
		IID_IDirectInput8,          //�ӿڱ�ʶ��ʹ��IID_IDirectInput8����  
		(void**)&m_pDirectInput,    //�����ĽӿڵĶ����ָ��  
		NULL);                      //COM���������������ΪNULL  
	//��ʼ�������豸  
	m_pDirectInput->CreateDevice(       //�����豸  
		GUID_SysKeyboard,              //GUIDֵ���������ͼ����к궨�壬�����豸��Ҫͨ��ö���ҳ�  
		&m_KeyboardDevice,             //�����豸ָ���ָ��  
		NULL);                           //COM��ز�����ΪNULL  
	m_KeyboardDevice->SetCooperativeLevel(//����Э������  
		hWnd,                              //���ھ��  
		keyboardCoopFlags);                  //Э������ǰ̨��̨����ռ�Ƕ�ռ��  
	m_KeyboardDevice->SetDataFormat(        //�������ݸ�ʽ  
		&c_dfDIKeyboard);                  //�������ȵ����ݸ�ʽ���궨��  
	m_KeyboardDevice->Acquire();            //����豸����Ȩ  
	m_KeyboardDevice->Poll();               //��ѯ�豸  
	//��ʼ������豸  
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
	//����һ�εİ�����Ϣ����
	memcpy(m_keyBufferlast, m_keyBuffer, 256);
	//��ü���������Ϣ  
	HRESULT hr = m_KeyboardDevice->GetDeviceState(sizeof(m_keyBuffer), (void**)&m_keyBuffer);
	if (FAILED(hr))//���ʧ�ܳ������»�ȡ
	{
		m_KeyboardDevice->Acquire();//��ȡ���̿���
		m_KeyboardDevice->GetDeviceState(sizeof(m_keyBuffer), (void**)&m_keyBuffer);
	}

	//����һ�ε������Ϣ����
	memcpy(&m_MouseLastState, &m_MouseState, sizeof(m_MouseState));
	//������������Ϣ  
	hr = m_MouseDevice->GetDeviceState(sizeof(m_MouseState), (void**)&m_MouseState);
	if (FAILED(hr))//���ʧ�ܳ������»�ȡ
	{
		m_MouseDevice->Acquire();//��ȡ������
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