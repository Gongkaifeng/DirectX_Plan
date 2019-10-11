#pragma once
#include "stdafx.h"

CEnemyBullet::CEnemyBullet()
{
}
CEnemyBullet::~CEnemyBullet()
{
}
CEnemyBullet::CEnemyBullet(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect)
{
	m_Texture = _Texture;
	m_Pos = _Pos;
	m_angle = 0;
	m_center = _center;
	m_rect = _rect;
	m_vSpeed = D3DXVECTOR3(0, 0, 0);
	m_Speed = 4;
	scaleX = 0.4;
	scaleY = 0.4;
	D3DXCreateSprite(CGameManager::GetGameInstance()->D3DDevice, &m_pSprite);
}
void CEnemyBullet::Update()
{
	BulletMove();
}
void CEnemyBullet::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//D3DXMATRIX scaleMat, roteMat, transMat;
	D3DXMatrixScaling(&scaleMat, scaleX, scaleY, 0);									// 缩放
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
void CEnemyBullet::BulletMove()
{
	m_Pos.y += m_Speed;
}

void CEnemyBullet::GetRc()
{
	int k = 10;									//k值决定碰撞区域大小
	rc_enemybullet = {
		(LONG)(m_Pos.x - m_rect.right / k),
		(LONG)(m_Pos.y - m_rect.bottom / k),
		(LONG)(m_Pos.x + m_rect.right / k),
		(LONG)(m_Pos.y + m_rect.bottom / k) };
}

bool CEnemyBullet::IsHit()
{
	// 敌机子弹1、我机激光碰撞
	GetRc();
	CGameManager::GetGameInstance()->myplaybullet3.GetRC();
	if (HitTest(rc_enemybullet, CGameManager::GetGameInstance()->myplaybullet3.rc_mybullet3)&& CGameManager::GetGameInstance()->myplaybullet3.ishide==false)
	{	
		
		return true;
	}

	// 敌机子弹1、我机子弹4碰撞检测
	list<CMyplayBullet4*>::iterator iter_mybullet4;
	for (iter_mybullet4 = CBulletManager::GetBulletInstance()->Mybulletlist4.begin(); iter_mybullet4 != CBulletManager::GetBulletInstance()->Mybulletlist4.end();)
	{
		GetRc();
		(*iter_mybullet4)->GetRC();
		if (HitTest(rc_enemybullet, (*iter_mybullet4)->rc_mybullet4))
		{
			return true;
		}
		else
		{
			iter_mybullet4++;
		}
	}
	return false;
}