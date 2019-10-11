#pragma once
#include "stdafx.h"

CMyplayBullet2::CMyplayBullet2()
{
}
CMyplayBullet2::~CMyplayBullet2()
{
}
CMyplayBullet2::CMyplayBullet2(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect, D3DXVECTOR3 _vSpeed)
{
	m_Texture = _Texture;
	m_Pos = _Pos;
	m_angle = 0;
	m_center = _center;
	m_rect = _rect;
	//m_vSpeed = _vSpeed;
	m_vSpeed = { 0,-3,0 };
	m_Speed = 4;
	D3DXCreateSprite(CGameManager::GetGameInstance()->D3DDevice, &m_pSprite);
}
void CMyplayBullet2::GetRC()
{
	int k = 10;
	rc_mybullet2 = {
		(LONG)(m_Pos.x - m_rect.right / k),
		(LONG)(m_Pos.y - m_rect.bottom / k),
		(LONG)(m_Pos.x + m_rect.right / k),
		(LONG)(m_Pos.y + m_rect.bottom / k) };
}
void CMyplayBullet2::Update()
{
	
	D3DXVECTOR3 _vSpeed;
	list<CEnemy*>::iterator iter_enemy = CEnemyManager::GetEnemyInstance()->enemylist.begin();
	list<CEnemy2*>::iterator iter_enemy2 = CEnemyManager::GetEnemyInstance()->enemylist2.begin();
	list<CEnemy3*>::iterator iter_enemy3 = CEnemyManager::GetEnemyInstance()->enemylist3.begin();	
	if (iter_enemy2 != CEnemyManager::GetEnemyInstance()->enemylist2.end())
	{
		_vSpeed = (*iter_enemy2)->m_Pos - m_Pos;
	}
	else if (iter_enemy3 != CEnemyManager::GetEnemyInstance()->enemylist3.end())
	{
		_vSpeed = (*iter_enemy3)->m_Pos - m_Pos;
	}
	else if (iter_enemy != CEnemyManager::GetEnemyInstance()->enemylist.end())
	{
		_vSpeed = (*iter_enemy)->m_Pos - m_Pos;
	}
	else
	{
		_vSpeed = { 0,-1,0 };
	}	
	D3DXVec3Normalize(&_vSpeed, &_vSpeed);
	m_vSpeed += _vSpeed*0.3;
	
	// 图片角度变换
	D3DXVECTOR3 NorSpeed = D3DXVECTOR3(0, -1, 0);
	D3DXVec3Normalize(&m_vSpeed, &m_vSpeed);
	m_angle = acos(D3DXVec3Dot(&NorSpeed, &m_vSpeed));  // 点乘求角度(无前后顺序)
	if (m_vSpeed.x < 0)
	{
		m_angle *= -1;
	}
	m_vSpeed *= 6;										// 速度的单位向量需要乘于系数
	
	BulletMove();
}
void CMyplayBullet2::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX scaleMat, roteMat, transMat;
	D3DXMatrixScaling(&scaleMat, 0.5, 0.5, 0);									// 缩放
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
void CMyplayBullet2::BulletMove()
{
	m_Pos += m_vSpeed;
}