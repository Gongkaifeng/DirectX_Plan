#include "StdAfx.h"
#include ".\uilistbox.h"
#include ".\uimanager.h"

CUIListbox::CUIListbox(void)
{
	m_nMaxCount = 0;
	m_nListIteamIndex = 0;
}

CUIListbox::~CUIListbox(void)
{
}

VOID CUIListbox::Init( int x,int y,HDC& hdc,char* strImage )
{
	nX = x;
	nY = y;
	m_Imgbasic.Init(x,y,hdc,strImage);
	
	//初始化文本控件列表
	for (int i=0;i<MaxShow;i++)
	{
		m_Text[i].Init(x+10,y+10+i*15,hdc);
	}

	CUIManager::GetManager().AddNew(this);
}

VOID CUIListbox::Draw()
{
	if(!m_hide)
	{
		m_Imgbasic.Draw();
		for(int i=0;i< MaxShow && i< m_nMaxCount;i++)
		{
			m_Text[i].Draw();
	    }
	}
}

VOID CUIListbox::AddIteam( char* strIteam )
{
	if(m_nMaxCount<MaxIteam)
	{
		m_Input[m_nMaxCount] = strIteam;
		m_nMaxCount++;
	}
	if(m_nMaxCount>MaxShow)
	{
		m_nListIteamIndex++;
	}
	CopyShowIteam();
}

VOID CUIListbox::CopyShowIteam()
{
	for(int i =m_nListIteamIndex , j = 0; i<m_nMaxCount && i< m_nListIteamIndex + MaxShow;i++ ,j++)
	{
		m_Text[j].SetText(m_Input[i].c_str());
	}
}

VOID CUIListbox::PageUp()
{
	if(m_nListIteamIndex>0)
	{
		m_nListIteamIndex--;
		CopyShowIteam();
	}
}

VOID CUIListbox::PageDown()
{
	if(m_nListIteamIndex<m_nMaxCount-MaxShow)
	{
		m_nListIteamIndex++;
		CopyShowIteam();
	}
}

VOID CUIListbox::MoveToEndIteam()
{
	m_nListIteamIndex= m_nMaxCount-MaxShow >0 ? m_nMaxCount-MaxShow:0;
	CopyShowIteam();
}