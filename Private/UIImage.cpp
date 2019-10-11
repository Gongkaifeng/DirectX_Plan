#include "StdAfx.h"
#include ".\uiimage.h"
#include ".\uimanager.h"
CUIImage::CUIImage(void)
{
	//m_Hdc = GetDC(NULL);
}

CUIImage::~CUIImage(void)
{
}

VOID CUIImage::Init(int x, int y, HDC& hdc,char * strName )
{
	nX = x;
	nY = y;
	m_Picture.Init(x,y,hdc,strName);
	CUIManager::GetManager().AddNew(this);
}

VOID CUIImage::Draw()
{
	if(!m_hide)
	{
		m_Picture.Draw();
	}

}

int CUIImage::GetWidth()
{
	return m_Picture.GetWidth();
}

int CUIImage::GetHeight()
{
	return m_Picture.GetHeight();
}