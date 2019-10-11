#pragma once
#include "stdafx.h"

CMyplayBullet3::CMyplayBullet3()
{
}

CMyplayBullet3::~CMyplayBullet3()
{
}

void CMyplayBullet3::Init(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect, D3DXVECTOR3 _vSpeed)
{
	m_Texture = _Texture;
	m_Pos = _Pos;
	m_angle = 0;
	m_center = _center;
	m_rect = _rect;
	m_vSpeed = _vSpeed;
	m_Speed = 4;
	pel = 255;
	D3DXCreateSprite(CGameManager::GetGameInstance()->D3DDevice, &m_pSprite);
	ishide = true;
}

void CMyplayBullet3::GetRC()
{
	int k = 10;
	rc_mybullet3 = {
		(LONG)(m_Pos.x - m_rect.right / k),
		(LONG)(m_Pos.y - m_rect.bottom ),
		(LONG)(m_Pos.x + m_rect.right / k),
		(LONG)(m_Pos.y ) };
}
void CMyplayBullet3::Update()
{
	BulletMove();
}
void CMyplayBullet3::Render()
{
	if (ishide)
		return;
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX scaleMat, roteMat, transMat;
	D3DXMatrixScaling(&scaleMat, 1, 1, 0);										// Ëõ·Å
	D3DXMatrixRotationZ(&roteMat, m_angle);										// Ðý×ª
	D3DXMatrixTranslation(&transMat, m_Pos.x, m_Pos.y, 0);						// Æ½ÒÆ
	matMatrix = scaleMat*roteMat*transMat;
	m_pSprite->SetTransform(&matMatrix);

	m_pSprite->Draw(m_Texture,
		&m_rect,
		&m_center,
		NULL,
		D3DCOLOR_ARGB(pel, 0xff, 0xff, 0xff));

	m_pSprite->End();
}

void CMyplayBullet3::BulletMove()
{
	m_Pos = CGameManager::GetGameInstance()->player01_Sprite.m_Pos;
}

