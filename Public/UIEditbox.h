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
	
	//初始化
	VOID Init(int x,int y,HDC& hdc,char* strBsice);

	//键盘响应
	VOID WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//绘制
	VOID Draw();

	//获取Editbox中的字符
	std::string GetText();

	//设置字符
	VOID SetText(char * sText);

	//设置最大输入字符数
	VOID SetMaxChar(int nCount);

protected:
	CUIPicture	m_Imgbasic;
	std::string m_Input;		//输入数据
	CUIText		m_Text;			//显示字符控件
	int			m_nMaxCount;	//最大字符数
};
