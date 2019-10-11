#pragma once
#include "stdafx.h"

CMyplayerhp::CMyplayerhp()
{
}

CMyplayerhp::~CMyplayerhp()
{
}

void CMyplayerhp::Init(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect)
{
	m_Texture	= _Texture;
	m_Pos		= _Pos;
	m_angle		= 0;
	m_center	= _center;
	m_rect		= _rect;
	m_vSpeed	= D3DXVECTOR3(0, 0, 0);
	scaleX		= 0.5;
	scaleY		= 0.8;
	pel			= 255;
	D3DXCreateSprite(CGameManager::GetGameInstance()->D3DDevice, &m_pSprite);	// 精灵初始化
}

void CMyplayerhp::Update()
{
	scaleX = 0.5;
	PlayerhpMove();
}

void CMyplayerhp::Update_front()
{
	scaleX = (CGameManager::GetGameInstance()->player01_Sprite.m_hp_myplayer)*0.01;
	PlayerhpMove();
}
void CMyplayerhp::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMatrixScaling(&scaleMat, scaleX, scaleY, 0);					// 缩放
	D3DXMatrixRotationZ(&roteMat, m_angle);						// 旋转
	D3DXMatrixTranslation(&transMat, m_Pos.x, m_Pos.y, 0);		// 平移
	matMatrix = scaleMat*roteMat*transMat;
	m_pSprite->SetTransform(&matMatrix);
	m_pSprite->Draw(m_Texture,
		&m_rect,
		&m_center,
		NULL,
		D3DCOLOR_ARGB(pel, 0xff, 0xff, 0xff));
	m_pSprite->End();
}

void CMyplayerhp::PlayerhpMove()
{
	m_Pos.x = CGameManager::GetGameInstance()->player01_Sprite.m_Pos.x - 50;
	m_Pos.y = CGameManager::GetGameInstance()->player01_Sprite.m_Pos.y - 50;
}