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
	D3DXCreateSprite(CGameManager::GetGameInstance()->D3DDevice, &m_pSprite);	// �����ʼ��
}

void CRope::Update()
{
	//���⣺��εó������쳤��/���ӳ��ȡ�ÿ������������*=�������
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
	D3DXMatrixScaling(&scaleMat, scalex, scaley, 0);												// ����
	D3DXMatrixRotationZ(&roteMat, m_angle);												// ��ת
	D3DXMatrixTranslation(&transMat, m_Pos.x, m_Pos.y, 0);								// ƽ��
	D3DXMATRIX mat = scaleMat*roteMat*transMat;
	m_pSprite->SetTransform(&mat);

	m_pSprite->Draw(m_Texture,
		&m_rect,
		&m_center,
		NULL,
		D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	m_pSprite->End();
}