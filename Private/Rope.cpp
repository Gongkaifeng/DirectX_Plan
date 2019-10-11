#pragma once
#include "stdafx.h"

CRope::CRope()
{
}


CRope::~CRope()
{
}

void CRope::Init(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect)
{
	m_Texture = _Texture;
	m_Pos = _Pos;
	m_center = _center;
	m_rect = _rect;	
	m_angle = 0;
	tempRope = 0.01;
	scalex = 1;
	scaley = 1;
	ropespeed = 0.067;
	D3DXCreateSprite(CGameManager::GetGameInstance()->D3DDevice, &m_pSprite);	// 精灵初始化
}

void CRope::Update()
{
	//问题：如何得出钩子伸长量/绳子长度。每次绳子缩放量*=这个倍率
	m_angle = CGameManager::GetGameInstance()->hook_Sprite.m_angle;
	D3DXVECTOR3 tempdistance = CGameManager::GetGameInstance()->hook_Sprite.m_Pos - CGameManager::GetGameInstance()->Index_hookpos;
	//D3DXVec3Normalize(&Distance, &Distance);
	int Distance = D3DXVec3Length(&tempdistance);
	int temp = Distance / (int)CGameManager::GetGameInstance()->pic[_T("rope")]->GetHeight();

	if (CGameManager::GetGameInstance()->dir == DIR_DOWN)
	{
		//scaley *= temp;
		scaley += ropespeed;
	}
}

void CRope::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMATRIX scaleMat, roteMat, transMat;
	D3DXMatrixScaling(&scaleMat, scalex, scaley, 0);												// 缩放
	D3DXMatrixRotationZ(&roteMat, m_angle);												// 旋转
	D3DXMatrixTranslation(&transMat, m_Pos.x, m_Pos.y, 0);								// 平移
	D3DXMATRIX mat = scaleMat*roteMat*transMat;
	m_pSprite->SetTransform(&mat);

	m_pSprite->Draw(m_Texture,
		&m_rect,
		&m_center,
		NULL,
		D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	m_pSprite->End();
}