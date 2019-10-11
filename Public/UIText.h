#pragma once
#include "UIObject.h"
class CUIText
{
public:
	CUIText(void);
	~CUIText(void);
	VOID Init(int x,int y,HDC& hdc);

	//ÉèÖÃ×Ö·û
	VOID SetText(const char* text);

	char * GetText(){return m_sText;}
	//»æÖÆ×Ö·û
	VOID Draw();
protected:
	HFONT m_hFont;
	int nX;
	int nY;
	char m_sText[255];		//´æ´¢×Ö·û
	HDC m_hdc;				//»æÖÆHDC
};