#pragma once
#include "stdafx.h"

CEnemy2::CEnemy2()
{
}

CEnemy2::~CEnemy2()
{
}

CEnemy2::CEnemy2(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect)
{
	m_Texture   = _Texture;
	m_Pos		= _Pos;
	m_angle		= 0;
	m_center	= _center;
	m_rect		= _rect;
	m_vSpeed	= D3DXVECTOR3(0, 1, 0);
	m_vSpeed2	= D3DXVECTOR3(4, -6, 0);
	m_vSpeed3	= D3DXVECTOR3(-4, -6, 0);
	m_Speed		= 3;
	preTime		= GetTickCount();
	m_bBoom		= false;
	m_curFrame	= 0;
	scaleX		= 0.5;
	scaleY		= 0.5;
	m_hp_enemy2 = 30;
	D3DXCreateSprite(CGameManager::GetGameInstance()->D3DDevice, &m_pSprite);
	m_eState2 = eES_Normal;
}

void CEnemy2::GetRc()
{
	int k = 5;									//kֵ������ײ�����С
	rc_enemy2 = {
		(LONG)(m_Pos.x - m_rect.right / k),
		(LONG)(m_Pos.y - m_rect.bottom / k),
		(LONG)(m_Pos.x + m_rect.right / k),
		(LONG)(m_Pos.y + m_rect.bottom / k) };
}

bool CEnemy2::IsHit()
{
	list<CMyplayBullet*>::iterator iter_mybullet;
	for (iter_mybullet = CBulletManager::GetBulletInstance()->Mybulletlist.begin(); iter_mybullet != CBulletManager::GetBulletInstance()->Mybulletlist.end();)
	{
		GetRc();
		(*iter_mybullet)->GetRC();
		if (HitTest(rc_enemy2, (*iter_mybullet)->rc_mybullet))
		{

			delete *iter_mybullet;//ɾ���һ��ӵ�
			iter_mybullet = CBulletManager::GetBulletInstance()->Mybulletlist.erase(iter_mybullet);
			return true;
		}
		else
		{
			iter_mybullet++;
		}
	}
	// �л�2���һ��ӵ�2��ײ���
	list<CMyplayBullet2*>::iterator iter_mybullet2;
	for (iter_mybullet2 = CBulletManager::GetBulletInstance()->Mybulletlist2.begin(); iter_mybullet2 != CBulletManager::GetBulletInstance()->Mybulletlist2.end();)
	{
		GetRc();
		(*iter_mybullet2)->GetRC();
		if (HitTest(rc_enemy2, (*iter_mybullet2)->rc_mybullet2))
		{

			delete *iter_mybullet2;//ɾ���һ��ӵ�
			iter_mybullet2 = CBulletManager::GetBulletInstance()->Mybulletlist2.erase(iter_mybullet2);
			return true;
		}
		else
		{
			iter_mybullet2++;
		}
	}
	// �л�2���һ��ӵ�3_������ײ���
	GetRc();
	CGameManager::GetGameInstance()->myplaybullet3.GetRC();
	if (HitTest(rc_enemy2, CGameManager::GetGameInstance()->myplaybullet3.rc_mybullet3) && CGameManager::GetGameInstance()->myplaybullet3.ishide == false)
	{
		return true;
	}
	// �л�2���һ��ӵ�4��ײ���
	list<CMyplayBullet4*>::iterator iter_mybullet4;
	for (iter_mybullet4 = CBulletManager::GetBulletInstance()->Mybulletlist4.begin(); iter_mybullet4 != CBulletManager::GetBulletInstance()->Mybulletlist4.end();)
	{
		GetRc();
		(*iter_mybullet4)->GetRC();
		if (HitTest(rc_enemy2, (*iter_mybullet4)->rc_mybullet4))
		{
			m_hp_enemy2 -= 100;
			return true;
		}
		else
		{
			iter_mybullet4++;
		}
	}

	return false;
}

void CEnemy2::Boom()
{
	m_PreTime = GetTickCount();
	m_curFrame = 0;
	m_bBoom = true;
}

void CEnemy2::Update()
{
	switch (m_eState2)
	{
	case eES_Normal:
	{
		// ͨ����ʱ����������������
		DWORD curTime_star = GetTickCount();
		float elapsedTime_star = (curTime_star - preTime_star)*0.001f;//�������
		if (elapsedTime_star >= 0.02f * 1)
		{
			m_Texture = CGameManager::GetGameInstance()->pic[_T("enemy02")]->GetTexture();
			preTime_star = curTime_star;
		}
		// �л��ƶ�
		Enemy2Move();
		// ͨ����ʱ�����������ӵ�
		DWORD curTime = GetTickCount();
		float elapsedTime = (curTime - preTime)*0.001f;//�������
		if (elapsedTime >= 0.7f * 1)
		{
			Enemy2Fire();
			preTime = curTime;
		}
		if (IsHit())
		{
			m_Texture = CGameManager::GetGameInstance()->pic[_T("enemy02_boom")]->GetTexture();
			preTime_star = GetTickCount();
			m_hp_enemy2 -= 1;
			if (m_hp_enemy2<=0)
			{
				CGameManager::GetGameInstance()->num_middle++;
				m_eState2 = eES_Boom;
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
		float boomtime = (m_curTime - m_PreTime)*0.001f;//�������
		if (boomtime >= 0.1f)
		{
			m_curFrame++;
		}
		TSTRING name;
		switch (m_curFrame % 4)
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
			m_eState2 = eES_Dead;
	}
	break;
	case eES_Dead:
	{

	}
	break;
	}
}

void CEnemy2::Render()
{
	// �������״̬������Ⱦ��
	if (m_eState2 == eES_Dead)
		return;

	// ���ܵл�����Ⱦ
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//D3DXMATRIX scaleMat, roteMat, transMat;
	D3DXMatrixScaling(&scaleMat, scaleX, scaleY, 0);							// ����
	D3DXMatrixRotationZ(&roteMat, m_angle);										// ��ת
	D3DXMatrixTranslation(&transMat, m_Pos.x, m_Pos.y, 0);						// ƽ��
	matMatrix = scaleMat*roteMat*transMat;
	m_pSprite->SetTransform(&matMatrix);
	m_pSprite->Draw(m_Texture,
		&m_rect,
		&m_center,
		NULL,
		D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	m_pSprite->End();

}

void CEnemy2::Enemy2Move()
{
	m_Pos += m_vSpeed;
}

// ���ܵл������ӵ�
void CEnemy2::Enemy2Fire()
{
	D3DXVECTOR3 _Pos = { m_Pos.x - 15 ,m_Pos.y + 30 ,0 };
	D3DXVECTOR3 _vSpeed = {-0.5,4,0};
	D3DXVECTOR3 _center = { (float)CGameManager::GetGameInstance()->pic[_T("bullet07")]->GetWidth() / 2, (float)CGameManager::GetGameInstance()->pic[_T("bullet07")]->GetHeight() / 2 ,0 };
	RECT _rect = { 0,0, CGameManager::GetGameInstance()->pic[_T("bullet07")]->GetWidth(), CGameManager::GetGameInstance()->pic[_T("bullet07")]->GetHeight() };
	CBulletManager::GetBulletInstance()->Enbulletlist2.push_back(new CEnemyBullet2(CGameManager::GetGameInstance()->pic[_T("bullet07")]->GetTexture(), _Pos, _center, _rect,_vSpeed));
	
	D3DXVECTOR3 _Pos2 = { m_Pos.x + 15 ,m_Pos.y + 30 ,0 };
	D3DXVECTOR3 _vSpeed2 = { 0.5,4,0 };
	CBulletManager::GetBulletInstance()->Enbulletlist2.push_back(new CEnemyBullet2(CGameManager::GetGameInstance()->pic[_T("bullet07")]->GetTexture(), _Pos2, _center, _rect,_vSpeed2));

}