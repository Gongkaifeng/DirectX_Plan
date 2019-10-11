#pragma once
#include "UIObject.h"
class CUIText
{
public:
	CUIText(void);
	~CUIText(void);
	VOID Init(int x,int y,HDC& hdc);

	//�����ַ�
	VOID SetText(const char* text);

	char * GetText(){return m_sText;}
	//�����ַ�
	VOID Draw();
protected:
	HFONT m_hFont;
	int nX;
	int nY;
	char m_sText[255];		//�洢�ַ�
	HDC m_hdc;				//����HDC
};