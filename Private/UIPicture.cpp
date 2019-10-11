#include "StdAfx.h"
#include ".\uipicture.h"

CUIPicture::CUIPicture(void)
{
	m_hide = false;
}

CUIPicture::~CUIPicture(void)
{
}

VOID CUIPicture::Init(int x, int y, HDC& hdc,char * strName )
{
	nX = x;
	nY = y;
	m_hdc =&hdc;
	m_Hdc = CreateCompatibleDC( hdc );
	m_Img = (HBITMAP)LoadImage(NULL,(LPCWSTR)strName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	GetObject(m_Img,sizeof(BITMAP),&m_bmp);
	SelectObject(m_Hdc,m_Img);
}

void CUIPicture::SetImagePos(int x,int y)
{
	nX=x;
	nY=y;
}
VOID CUIPicture::Draw()
{
	if(!m_hide)
	{
		BitBlt(*m_hdc,nX,nY,m_bmp.bmWidth,m_bmp.bmHeight,m_Hdc,0,0,SRCCOPY);  
	}

}

int CUIPicture::GetWidth()
{
	return m_bmp.bmWidth;
}

int CUIPicture::GetHeight()
{
	return m_bmp.bmHeight;
}

VOID CUIPicture::Hide()
{
	m_hide = true;
}

VOID CUIPicture::Show()
{
	m_hide = false;
}