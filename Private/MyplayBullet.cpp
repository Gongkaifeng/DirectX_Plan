#pragma once
#include "stdafx.h"
CMyplayBullet::CMyplayBullet()
{
}
CMyplayBullet::~CMyplayBullet()
{
}
CMyplayBullet::CMyplayBullet(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect, D3DXVECTOR3 _vSpeed)
{
	m_Texture   = _Texture;
	m_Pos       = _Pos;
	m_angle		= 0;
	m_center	= _center;
	m_rect		= _rect;
	m_vSpeed	= _vSpeed;
	m_Speed		= 4;
	D3DXCreateSprite(CGameManager::GetGameInstance()->D3DDevice, &m_pSprite);
}
void CMyplayBullet::GetRC()
{
	int k = 10;
	rc_mybullet = {
		(LONG)(m_Pos.x - m_rect.right / k),
		(LONG)(m_Pos.y - m_rect.bottom / k),
		(LONG)(m_Pos.x + m_rect.right / k),
		(LONG)(m_Pos.y + m_rect.bottom / k) };
}
void CMyplayBullet::Update()
{
	BulletMove();	
}
void CMyplayBullet::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX scaleMat, roteMat, transMat;
	D3DXMatrixScaling(&scaleMat, 0.5, 0.5, 0);									// Ëõ·Å
	D3DXMatrixRotationZ(&roteMat, m_angle);										// Ðý×ª
	D3DXMatrixTranslation(&transMat, m_Pos.x, m_Pos.y, 0);						// Æ½ÒÆ
	matMatrix = scaleMat*roteMat*transMat;
	m_pSprite->SetTransform(&matMatrix);

	m_pSprite->Draw(m_Texture,
		&m_rect,
		&m_center,
		NULL,
		D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	m_pSprite->End();
}
void CMyplayBullet::BulletMove()
{
	m_Pos += m_vSpeed;
}