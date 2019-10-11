#pragma once
#include "stdafx.h"

CUIButton::CUIButton(void)
{
	m_Img = NULL;
	m_bButtonDown = false;
}

CUIButton::~CUIButton(void)
{
}

VOID CUIButton::Init(int x, int y, IDirect3DDevice9* g_pDevice, TSTRING strBasic, TSTRING strMouseOver, TSTRING strMouseUp)
{
	nX = x;
	nY = y;
	LPDIRECT3DDEVICE9 pDevice = (LPDIRECT3DDEVICE9)CGameManager::GetGameInstance()->GetDevice();
	D3DXCreateSprite(pDevice, &m_pSprite);
	
	m_Imgbasic = CGameManager::GetGameInstance()->pic[strBasic];
	m_ImgMouseOver = CGameManager::GetGameInstance()->pic[strMouseOver];
	m_ImgMouseUp =CGameManager::GetGameInstance()->pic[strMouseUp];

	m_Img = m_Imgbasic;
	CUIManager::GetInstance()->AddNew(this);
}

VOID CUIButton::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
		switch(message)
			{
			case WM_MOUSEMOVE:
			{
				m_Point.x = LOWORD(lParam);
				m_Point.y = HIWORD(lParam);
				if (InHot())
				{
					m_Img = m_ImgMouseOver;
				}
				else
				{
					m_Img = m_Imgbasic;
				}
				m_bButtonDown = false;
			}
				break;
			case WM_LBUTTONDOWN:
				if (InHot()&&!m_hide)
				{
					m_Img = m_ImgMouseUp;
					m_bButtonDown = true;
				}
				break;
			case WM_LBUTTONUP:
			{
				m_Img = m_Imgbasic;
				m_bButtonDown = false;
			}
			break;

			default:
				break;
			}
}

BOOL CUIButton::InHot()
{
	//PtInRect();
	if (m_Point.x >= nX && m_Point.x <= nX + m_Imgbasic->GetWidth() && m_Point.y >= nY && m_Point.y <= nY + m_Imgbasic->GetHeight())
		{
			return true;
		}
		return false;
}

VOID CUIButton::Draw()
{
	if(!m_hide)
	{
		if (m_Img)
		{
			m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
			m_pSprite->Draw(m_Img->GetTexture(), NULL, NULL, &D3DXVECTOR3(nX, nY, 0), D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
			m_pSprite->End();
		}
	}
}

bool CUIButton::IsButtonDown()
{
	return m_bButtonDown;
}