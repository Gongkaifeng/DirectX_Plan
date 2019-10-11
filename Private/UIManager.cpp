#pragma once
#include "stdafx.h"

CUIManager::CUIManager(void)
{
}

CUIManager::~CUIManager(void)
{
}

void CUIManager::AddNew( CUIObject * UIObject)
{
    m_UIList.push_back(UIObject);
}

void CUIManager::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	std::list<CUIObject*>::iterator it;
	for (it = m_UIList.begin(); it != m_UIList.end(); ++it)
		(*it)->WndProc(hWnd, message, wParam, lParam);
}

void CUIManager::Draw()
{
	std::list<CUIObject*>::iterator it;
	for(it = m_UIList.begin(); it != m_UIList.end(); ++it)
			(*it)->Draw();
}

//CUIManager& CUIManager::GetManager()
//{
//	static CUIManager Manager;
//	return Manager;
//}