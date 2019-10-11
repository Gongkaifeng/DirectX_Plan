#ifndef __CDIRECTINPUT_H_  
#define __CDIRECTINPUT_H_  
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h> 

class CDirectInput
{
private:
	IDirectInput8* m_pDirectInput;                  //DirectInput接口对象指针  
	IDirectInputDevice8* m_KeyboardDevice;          //键盘设备接口  
	char m_keyBuffer[256];                          //用于保存键盘键值的数组  
	char m_keyBufferlast[256];                      //用于保存上一次键盘键值的数组 

	IDirectInputDevice8* m_MouseDevice;             //鼠标设备接口  
	DIMOUSESTATE m_MouseState;                      //鼠标键值存储结构体  
	DIMOUSESTATE m_MouseLastState;                  //鼠标上一次键值存储结构体  
	HWND	m_hWnd;//窗口句柄
public:
	CDirectInput(void);
	~CDirectInput(void);
	//初始化DirectInput以及键盘鼠标设备  
	HRESULT Init(HWND hWnd, HINSTANCE hInstance, DWORD keyboardCoopFlags, DWORD mouseCoopFlags);
	void GetInput();//获得输入信息  
	bool IsKeyCurrentDown(int iKey);//检测键盘某按键是否刚刚按下
	bool IsKeyHold(int iKey);//检测键盘某按键是否被按下  
	bool IsKeyCurrentUp(int iKey);//检测键盘某按键是否刚刚被放开
	bool IsKeyUp(int iKey);//检测键盘某按键是否一直放开
	bool IsMouseButtonCurrentDown(int iButton);//检测鼠标某按键是否刚刚被按下  	
	bool IsMouseButtonHold(int iButton);//检测鼠标某按键是否被按下  
	bool IsMouseButtonCurrentUp(int iButton);//检测鼠标某按键是否刚刚被放开
	bool IsMouseButtonUp(int iButton);//检测鼠标某按键是否一直放开
	float MouseX();//获取鼠标X坐标
	float MouseY();//获取鼠标Y坐标
	void MousePosition(LPPOINT pos);//获取鼠标坐标
	float MouseDX();//获得鼠标相对于上一个X位置的偏移值 	
	float MouseDY();//获得鼠标相对于上一个Y位置的偏移值 
	float MouseDZ();//获得鼠标Z轴（鼠标滚轮）滚动值
};
#endif  
