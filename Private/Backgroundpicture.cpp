#pragma once
#include "stdafx.h"
CBackgroundpicture::CBackgroundpicture()
{
}
CBackgroundpicture::~CBackgroundpicture()
{
}

void CBackgroundpicture::Init(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect)
{
	m_Texture = _Texture;
	m_Pos = _Pos;
	m_angle = 0;
	m_center = _center;
	m_rect = _rect;
	m_vSpeed = D3DXVECTOR3(0, 0, 0);
	m_Speed = 3;
	D3DXCreateSprite(CGameManager::GetGameInstance()->D3DDevice, &m_pSprite);	// 精灵初始化
																				//LoadCollisionImage();
}

void CBackgroundpicture::Update()
{
	m_center.y -= m_Speed;
	if (m_center.y <= 450)
	{
		m_center.y = 2250;
	}
}
void CBackgroundpicture::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX scaleMat, roteMat, transMat;
	D3DXMatrixScaling(&scaleMat, 1, 1, 0);										// 缩放
	D3DXMatrixRotationZ(&roteMat, m_angle);										// 旋转
	D3DXMatrixTranslation(&transMat, m_Pos.x, m_Pos.y, 0);						// 平移
	mat = scaleMat*roteMat*transMat;
	m_pSprite->SetTransform(&mat);
	m_pSprite->Draw(m_Texture,
		&m_rect,
		&m_center,
		NULL,
		D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	m_pSprite->End();

}