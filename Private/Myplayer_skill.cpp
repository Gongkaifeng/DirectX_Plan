#pragma once
#include "stdafx.h"

CMyplayer_skill::CMyplayer_skill()
{
}

CMyplayer_skill::~CMyplayer_skill()
{
}

void CMyplayer_skill::Init(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect)
{
	m_Texture = _Texture;
	m_Pos = _Pos;
	m_angle = 0;
	m_center = _center;
	m_rect = _rect;
	m_vSpeed = D3DXVECTOR3(0, -10, 0);		// ����ƶ��ٶ�����
	m_Speed = 0;							// ����ƶ��ٶ�
	pel = 195;
	scaleX = 4;
	scaleY = 4;
	D3DXCreateSprite(CGameManager::GetGameInstance()->D3DDevice, &m_pSprite);	// �����ʼ��
}

void CMyplayer_skill::Update()
{
	Move();
}

void CMyplayer_skill::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMatrixScaling(&scaleMat, scaleX, scaleY, 0);			// ����
	D3DXMatrixRotationZ(&roteMat, m_angle);						// ��ת
	D3DXMatrixTranslation(&transMat, m_Pos.x, m_Pos.y, 0);		// ƽ��
	matMatrix = scaleMat*roteMat*transMat;
	m_pSprite->SetTransform(&matMatrix);
	m_pSprite->Draw(m_Texture,
		&m_rect,
		&m_center,
		NULL,
		D3DCOLOR_ARGB(pel, 0xff, 0xff, 0xff));
	m_pSprite->End();
}

void CMyplayer_skill::Move()
{
	m_Pos += m_vSpeed;
}
