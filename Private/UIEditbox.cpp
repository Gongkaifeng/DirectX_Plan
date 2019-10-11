#include "StdAfx.h"
#include ".\uieditbox.h"

CUIEditbox::CUIEditbox(void)
{
	m_nMaxCount = 10;
}

CUIEditbox::~CUIEditbox(void)
{
}

VOID CUIEditbox::Init(int x,int y,HDC& hdc,char* strBsice)
{
    nX = x;
	nY = y;
	m_Imgbasic.Init(x,y,hdc,strBsice);
	
	m_Text.Init(x+5,y+8,hdc);
	CUIManager::GetManager().AddNew(this);
}

VOID CUIEditbox::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	if(!m_hide)
	{
		switch(message)
		{
		case WM_CHAR:
			
			switch(wParam)
			{
			case VK_BACK:
				{
				int length=m_Input.length();
				m_Input = m_Input.substr(0,length-1);
				m_Text.SetText((char*)m_Input.c_str());
				break;}
			default:
				if(m_Input.length()<m_nMaxCount)
				{
					m_Input += (char) wParam;
					m_Text.SetText((char*)m_Input.c_str());
				}
				break;
				
			}
		}

		

		
	}
}
VOID CUIEditbox::Draw()
{
	HDC hdc;

	hdc=CreateCompatibleDC(NULL);
	if(!m_hide)
	{
		m_Imgbasic.Draw();
		m_Text.Draw();


	}
	DeleteDC(hdc);
}

std::string  CUIEditbox::GetText()
{
	return m_Input;
}

VOID CUIEditbox::SetText(char * sText)
{
	m_Input = sText;
	m_Text.SetText((char*)m_Input.c_str());	
}

VOID CUIEditbox::SetMaxChar( int nCount )
{
	m_nMaxCount = nCount;
}