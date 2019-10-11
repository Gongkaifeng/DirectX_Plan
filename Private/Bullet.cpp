#pragma once
#include "stdafx.h"

CBullet::CBullet(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect)
{
	m_Texture	= _Texture;
	m_Pos		= _Pos;
	m_angle		= 0;
	m_center	= _center;
	m_rect		= _rect;
	m_vSpeed	= D3DXVECTOR3(0, 0, 0);
	m_Speed		= 4;
	//Isshow = false;
	D3DXCreateSprite(CGameManager::GetGameInstance()->D3DDevice, &m_pSprite);
}
CBullet::CBullet()
{
}
CBullet::~CBullet()
{
}

void CBullet::Update()
{	
	BulletMove();
}

void CBullet::BulletMove()
{
	m_Pos.y -= m_Speed*2;
}

void CBullet::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX scaleMat, roteMat, transMat;
	D3DXMatrixScaling(&scaleMat, 0.5, 0.5, 0);									// Ëõ·Å
	D3DXMatrixRotationZ(&roteMat, m_angle);										// Ğı×ª
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
