#pragma once
#include "stdafx.h"

CEnemy::CEnemy()
{
}
CEnemy::~CEnemy()
{
}
CEnemy::CEnemy(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect)
{
	m_Texture	= _Texture;
	m_Pos		= _Pos;
	m_angle		= 0;
	m_center	= _center;
	m_rect		= _rect;
	m_vSpeed	= D3DXVECTOR3(0, 2, 0);
	m_vSpeed2	= D3DXVECTOR3(4, -6, 0);
	m_vSpeed3	= D3DXVECTOR3(-4, -6, 0);
	m_Speed		= 3;
	preTime		= GetTickCount();
	m_bBoom		= false;
	m_curFrame  = 0;
	scaleX		= 0.5;
	scaleY		= 0.5;
	m_hp_enemy  = 3;
	D3DXCreateSprite(CGameManager::GetGameInstance()->D3DDevice, &m_pSprite);
	m_eState = eES_Normal;
}

void CEnemy::GetRc()
{
	rc_enemy = {
		(LONG)(m_Pos.x - m_rect.right / 8),
		(LONG)(m_Pos.y - m_rect.bottom / 8),
		(LONG)(m_Pos.x + m_rect.right / 8),
		(LONG)(m_Pos.y + m_rect.bottom / 8) };
}

bool CEnemy::IsHit()
{
	// 敌机1、我机子弹1碰撞检测
	list<CMyplayBullet*>::iterator iter_mybullet;
	for (iter_mybullet = CBulletManager::GetBulletInstance()->Mybulletlist.begin(); iter_mybullet != CBulletManager::GetBulletInstance()->Mybulletlist.end();)
	{
		GetRc();
		(*iter_mybullet)->GetRC();
		if (HitTest(rc_enemy, (*iter_mybullet)->rc_mybullet))
		{
			
			delete *iter_mybullet;//删除我机子弹
			iter_mybullet = CBulletManager::GetBulletInstance()->Mybulletlist.erase(iter_mybullet);
			return true;
		}
		else
		{
			iter_mybullet++;
		}
	}
	// 敌机1、我机子弹2碰撞检测
	list<CMyplayBullet2*>::iterator iter_mybullet2;
	for (iter_mybullet2 = CBulletManager::GetBulletInstance()->Mybulletlist2.begin(); iter_mybullet2 != CBulletManager::GetBulletInstance()->Mybulletlist2.end();)
	{
		GetRc();
		(*iter_mybullet2)->GetRC();
		if (HitTest(rc_enemy, (*iter_mybullet2)->rc_mybullet2))
		{
			delete *iter_mybullet2;//删除我机子弹
			iter_mybullet2 = CBulletManager::GetBulletInstance()->Mybulletlist2.erase(iter_mybullet2);
			return true;
		}
		else
		{
			iter_mybullet2++;
		}
	}
	// 敌机1、我机子弹3_激光碰撞检测
	GetRc();
	CGameManager::GetGameInstance()->myplaybullet3.GetRC();
	if (HitTest(rc_enemy, CGameManager::GetGameInstance()->myplaybullet3.rc_mybullet3) && CGameManager::GetGameInstance()->myplaybullet3.ishide == false)
	{
		return true;
	}

	// 敌机1、我机子弹4碰撞检测
	list<CMyplayBullet4*>::iterator iter_mybullet4;
	for (iter_mybullet4 = CBulletManager::GetBulletInstance()->Mybulletlist4.begin(); iter_mybullet4 != CBulletManager::GetBulletInstance()->Mybulletlist4.end();)
	{
		GetRc();
		(*iter_mybullet4)->GetRC();
		if (HitTest(rc_enemy, (*iter_mybullet4)->rc_mybullet4))
		{
			m_hp_enemy -= 100;
			return true;
		}
		else
		{
			iter_mybullet4++;
		}
	}

	return false;
}
void CEnemy::Boom()
{
	m_PreTime   = GetTickCount();
	m_curFrame  = 0;
	m_bBoom		= true;
}

void CEnemy::Update()
{
	switch (m_eState)
	{
	case eES_Normal:
	{
		// 通过计时器将爆破纹理换回来
		DWORD curTime_star = GetTickCount();
		float elapsedTime_star = (curTime_star - preTime_star)*0.001f;//换算成秒
		if (elapsedTime_star >= 0.03f * 1)
		{
			m_Texture = CGameManager::GetGameInstance()->pic[_T("enemy01")]->GetTexture();
			preTime_star = curTime_star;
		}
		// 敌机移动
		EnemyMove();
		// 通过计时器开火生成子弹
		DWORD curTime = GetTickCount();
		float elapsedTime = (curTime - preTime)*0.001f;//换算成秒
		if (elapsedTime >= 1.6f * 1)
		{
			EnemyFire();
			preTime = curTime;
		}
		if (IsHit())
		{
			m_Texture = CGameManager::GetGameInstance()->pic[_T("enemy01_boom")]->GetTexture();
			preTime_star = GetTickCount();
			m_hp_enemy -= 1;
			if (m_hp_enemy<=0)
			{
				CGameManager::GetGameInstance()->num_small++;
				m_eState = eES_Boom;
				Boom();
			}		
		};
	}
		break;
	case eES_Boom:
	{
		scaleX = 0.3;
		scaleY = 0.3;
		DWORD m_curTime = GetTickCount();
		float boomtime = (m_curTime - m_PreTime)*0.001f;//换算成秒
		if (boomtime >= 0.1f)
		{
			m_curFrame++;
		}
		TSTRING name;
		switch (m_curFrame%4)
		{
		case 0:
			name = _T("boom01");
				break;
		case 1:
			name = _T("boom02");
			break;
		case 2:
			name = _T("boom03");
			break;
		case 3:
			name = _T("boom04");
			break;
		default:  
			break;
		}
		m_Texture = CGameManager::GetGameInstance()->pic[name]->GetTexture();
		if (m_curFrame >= 8)
			m_eState = eES_Dead;
	}
		break;
	case eES_Dead:
	{

	}
		break;
	}
}

void CEnemy::Render()
{
	// 如果死亡状态，不渲染。
	if (m_eState == eES_Dead)
		return;

	// 单架敌机的渲染
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

void CEnemy::EnemyMove()
{
	m_Pos += m_vSpeed;
	if (m_Pos.y == 100)
	{
		m_vSpeed2 = CGameManager::GetGameInstance()->player01_Sprite.m_Pos - m_Pos;
		D3DXVec3Normalize(&m_vSpeed2, &m_vSpeed2);
		m_vSpeed = m_vSpeed2 * 2;
	}	
}

// 单架敌机发射子弹
void CEnemy::EnemyFire()
{
	D3DXVECTOR3 _Pos = { m_Pos.x ,m_Pos.y + 30 ,0 };
	D3DXVECTOR3 _center = { (float)CGameManager::GetGameInstance()->pic[_T("bullet06")]->GetWidth() / 2, (float)CGameManager::GetGameInstance()->pic[_T("bullet06")]->GetHeight() / 2 ,0 };
	RECT _rect = { 0,0, CGameManager::GetGameInstance()->pic[_T("bullet06")]->GetWidth(), CGameManager::GetGameInstance()->pic[_T("bullet06")]->GetHeight() };

	CBulletManager::GetBulletInstance()->Enbulletlist.push_back(new CEnemyBullet(CGameManager::GetGameInstance()->pic[_T("bullet06")]->GetTexture(), _Pos, _center, _rect));

}