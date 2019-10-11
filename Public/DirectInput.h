#ifndef __CDIRECTINPUT_H_  
#define __CDIRECTINPUT_H_  
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h> 

class CDirectInput
{
private:
	IDirectInput8* m_pDirectInput;                  //DirectInput�ӿڶ���ָ��  
	IDirectInputDevice8* m_KeyboardDevice;          //�����豸�ӿ�  
	char m_keyBuffer[256];                          //���ڱ�����̼�ֵ������  
	char m_keyBufferlast[256];                      //���ڱ�����һ�μ��̼�ֵ������ 

	IDirectInputDevice8* m_MouseDevice;             //����豸�ӿ�  
	DIMOUSESTATE m_MouseState;                      //����ֵ�洢�ṹ��  
	DIMOUSESTATE m_MouseLastState;                  //�����һ�μ�ֵ�洢�ṹ��  
	HWND	m_hWnd;//���ھ��
public:
	CDirectInput(void);
	~CDirectInput(void);
	//��ʼ��DirectInput�Լ���������豸  
	HRESULT Init(HWND hWnd, HINSTANCE hInstance, DWORD keyboardCoopFlags, DWORD mouseCoopFlags);
	void GetInput();//���������Ϣ  
	bool IsKeyCurrentDown(int iKey);//������ĳ�����Ƿ�ոհ���
	bool IsKeyHold(int iKey);//������ĳ�����Ƿ񱻰���  
	bool IsKeyCurrentUp(int iKey);//������ĳ�����Ƿ�ոձ��ſ�
	bool IsKeyUp(int iKey);//������ĳ�����Ƿ�һֱ�ſ�
	bool IsMouseButtonCurrentDown(int iButton);//������ĳ�����Ƿ�ոձ�����  	
	bool IsMouseButtonHold(int iButton);//������ĳ�����Ƿ񱻰���  
	bool IsMouseButtonCurrentUp(int iButton);//������ĳ�����Ƿ�ոձ��ſ�
	bool IsMouseButtonUp(int iButton);//������ĳ�����Ƿ�һֱ�ſ�
	float MouseX();//��ȡ���X����
	float MouseY();//��ȡ���Y����
	void MousePosition(LPPOINT pos);//��ȡ�������
	float MouseDX();//�������������һ��Xλ�õ�ƫ��ֵ 	
	float MouseDY();//�������������һ��Yλ�õ�ƫ��ֵ 
	float MouseDZ();//������Z�ᣨ�����֣�����ֵ
};
#endif  
