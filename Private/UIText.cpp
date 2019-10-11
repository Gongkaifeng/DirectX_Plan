#include "StdAfx.h"
#include ".\uitext.h"

CUIText::CUIText(void)
{
}

CUIText::~CUIText(void)
{
}
VOID CUIText::Init(int x,int y,HDC& hdc)
{
	m_hFont=CreateFont(20,20,0,0,0,0,0,0,GB2312_CHARSET,0,0,0,0,_T("ÀŒÃÂ"));
	nX = x;
	nY = y;
	m_hdc = hdc;
	SelectObject(m_hdc,m_hFont);
	SetBkMode(hdc,TRANSPARENT);		//…Ë÷√±≥æ∞Õ∏√˜
}
VOID CUIText::SetText(const char* text)
{
	strcpy_s(m_sText,text);
}
VOID CUIText::Draw()
{
	TextOut(m_hdc,nX,nY,(LPCWSTR)m_sText,strlen(m_sText));
}