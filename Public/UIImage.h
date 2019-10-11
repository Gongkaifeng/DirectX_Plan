#pragma once
#include "UIObject.h"
#include ".\uipicture.h"

class CUIImage : public CUIObject
{
public:
	CUIImage(void);
	~CUIImage(void);

	VOID Init(int x, int y, HDC& hdc, char * strName);
	VOID Draw();

	//获取图片控件长宽
	int GetWidth();
	int GetHeight();
protected:
	CUIPicture	m_Picture;
	
};
