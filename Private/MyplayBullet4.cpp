#pragma once
#include "stdafx.h"

CMyplayBullet4::CMyplayBullet4()
{
}

CMyplayBullet4::~CMyplayBullet4()
{
}

CMyplayBullet4::CMyplayBullet4(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect, D3DXVECTOR3 _vSpeed)
{
	m_Texture = _Texture;
	m_Pos = _Pos;
	m_angle = 0;
	m_center = _center;
	m_rect = _rect;
	m_vSpeed = { 0,-4,0 };
	scaleX = 1;
	scaleY = 1;
	D3DXCreateSprite(CGameManager::GetGameInstance()->D3DDevice, &m_pSprite);
}
void CMyplayBullet4::GetRC()
{
	int k = 2;
	rc_mybullet4 = {
		(LONG)(m_Pos.x - m_rect.right / k),
		(LONG)(m_Pos.y - m_rect.bottom / k),
		(LONG)(m_Pos.x + m_rect.right / k),
		(LONG)(m_Pos.y + m_rect.bottom / k) };
}
void CMyplayBullet4::Update()
{
	BulletMove();

	DWORD m_curTime = GetTickCount();
	float temptime = (m_curTime - m_Pretime)*0.001f;//换算成秒
	if (temptime >= 0.02f)
	{
		curFrame_b4++;
		m_Pretime = m_curTime;
	}
	TSTRING name;
	switch (curFrame_b4 % 9)
	{
	case 0:
		name = _T("skill01");
		break;
	case 1:
		name = _T("skill02");
		break;
	case 2:
		name = _T("skill03");
		break;
	case 3:
		name = _T("skill04");
		break;
	case 4:
		name = _T("skill05");
		break;
	case 5:
		name = _T("skill06");
		break;
	case 6:
		name = _T("skill07");
		break;
	case 7:
		name = _T("skill08");
		break;
	case 8:
		name = _T("skill09");
		break;

	default:
		break;
	}
	m_Texture = CGameManager::GetGameInstance()->pic[name]->GetTexture();
}
void CMyplayBullet4::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX scaleMat, roteMat, transMat;
	D3DXMatrixScaling(&scaleMat, scaleX, scaleY, 0);							// 缩放
	D3DXMatrixRotationZ(&roteMat, m_angle);										// 旋转
	D3DXMatrixTranslation(&transMat, m_Pos.x, m_Pos.y, 0);						// 平移
	matMatrix = scaleMat*roteMat*transMat;
	m_pSprite->SetTransform(&matMatrix);

	m_pSprite->Draw(m_Texture,
		&m_rect,
		&m_center,
		NULL,
		D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	m_pSprite->End();
}
void CMyplayBullet4::BulletMove()
{
	m_Pos += m_vSpeed;
}