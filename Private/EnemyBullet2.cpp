#pragma once
#include "stdafx.h"

CEnemyBullet2::CEnemyBullet2()
{
}

CEnemyBullet2::~CEnemyBullet2()
{
}

CEnemyBullet2::CEnemyBullet2(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect,D3DXVECTOR3 _vSpeed)
{
	m_Texture = _Texture;
	m_Pos = _Pos;
	m_angle = 0;
	m_center = _center;
	m_rect = _rect;
	//m_vSpeed = D3DXVECTOR3(-0.5, 3, 0);
	m_vSpeed = _vSpeed;
	m_Speed = 4;
	scaleX = 0.4;
	scaleY = 0.4;
	D3DXCreateSprite(CGameManager::GetGameInstance()->D3DDevice, &m_pSprite);
}
void CEnemyBullet2::Update()
{
	BulletMove();
}
void CEnemyBullet2::Render()
{
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
void CEnemyBullet2::BulletMove()
{
	
	m_Pos += m_vSpeed;
}

void CEnemyBullet2::GetRc()
{
	int k = 10;									//kֵ������ײ�����С
	rc_enemybullet2 = {
		(LONG)(m_Pos.x - m_rect.right / k),
		(LONG)(m_Pos.y - m_rect.bottom / k),
		(LONG)(m_Pos.x + m_rect.right / k),
		(LONG)(m_Pos.y + m_rect.bottom / k) };
}

bool CEnemyBullet2::IsHit()
{
	// �л��ӵ�1���һ�������ײ
	GetRc();
	CGameManager::GetGameInstance()->myplaybullet3.GetRC();
	if (HitTest(rc_enemybullet2, CGameManager::GetGameInstance()->myplaybullet3.rc_mybullet3) && CGameManager::GetGameInstance()->myplaybullet3.ishide == false)
	{
		return true;
	}

	// �л��ӵ�2���һ��ӵ�4��ײ���
	list<CMyplayBullet4*>::iterator iter_mybullet4;
	for (iter_mybullet4 = CBulletManager::GetBulletInstance()->Mybulletlist4.begin(); iter_mybullet4 != CBulletManager::GetBulletInstance()->Mybulletlist4.end();)
	{
		GetRc();
		(*iter_mybullet4)->GetRC();
		if (HitTest(rc_enemybullet2, (*iter_mybullet4)->rc_mybullet4))
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