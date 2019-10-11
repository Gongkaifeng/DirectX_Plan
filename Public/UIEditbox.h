#pragma once
#include "UIObject.h"
#include "UIImage.h"
#include"UIText.h"
#include <string>
#include ".\uimanager.h"
class CUIEditbox: public CUIObject
{
public:
	CUIEditbox(void);
	~CUIEditbox(void);
	
	//��ʼ��
	VOID Init(int x,int y,HDC& hdc,char* strBsice);

	//������Ӧ
	VOID WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//����
	VOID Draw();

	//��ȡEditbox�е��ַ�
	std::string GetText();

	//�����ַ�
	VOID SetText(char * sText);

	//������������ַ���
	VOID SetMaxChar(int nCount);

protected:
	CUIPicture	m_Imgbasic;
	std::string m_Input;		//��������
	CUIText		m_Text;			//��ʾ�ַ��ؼ�
	int			m_nMaxCount;	//����ַ���
};
