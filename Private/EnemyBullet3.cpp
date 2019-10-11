#pragma once
#include "stdafx.h"

CEnemyBullet3::CEnemyBullet3()
{
}

CEnemyBullet3::~CEnemyBullet3()
{
}

CEnemyBullet3::CEnemyBullet3(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect, D3DXVECTOR3 _vSpeed,float _angle)
{
	m_Texture	= _Texture;
	m_Pos		= _Pos;
	m_angle		= 0;
	m_center	= _center;
	m_rect		= _rect;
	m_vSpeed	= _vSpeed;
	m_Speed		= 4;
	scaleX		= 0.15;
	scaleY		= 0.15;
	curFrame_b3 = 0;
	m_angle		= _angle;
	pel			= 255;
	m_Pretime	= GetTickCount();
	D3DXCreateSprite(CGameManager::GetGameInstance()->D3DDevice, &m_pSprite);
}
void CEnemyBullet3::Update()
{
	BulletMove();	

	DWORD m_curTime = GetTickCount();
	float temptime = (m_curTime - m_Pretime)*0.001f;//换算成秒
	if (temptime >= 0.015f)
	{
		curFrame_b3++;
		m_Pretime = m_curTime;
	}
	
	TSTRING name;
	switch (curFrame_b3 % 7)
	{
	case 0:
		name = _T("bullet20");
		break;
	case 1:
		name = _T("bullet21");
		break;
	case 2:
		name = _T("bullet22");
		break;
	case 3:
		name = _T("bullet23");
		break;
	case 4:
		name = _T("bullet24");
		break;
	case 5:
		name = _T("bullet25");
		break;
	case 6:
		name = _T("bullet26");
		break;

	default:
		break;
	}
	m_Texture = CGameManager::GetGameInstance()->pic[name]->GetTexture();
	
	
}
void CEnemyBullet3::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//D3DXMATRIX scaleMat, roteMat, transMat;
	D3DXMatrixScaling(&scaleMat, scaleX, scaleY, 0);							// 缩放
	D3DXMatrixRotationZ(&roteMat, m_angle-PI/2);										// 旋转
	D3DXMatrixTranslation(&transMat, m_Pos.x, m_Pos.y, 0);						// 平移
	matMatrix = scaleMat*roteMat*transMat;
	m_pSprite->SetTransform(&matMatrix);

	m_pSprite->Draw(m_Texture,
		&m_rect,
		&m_center,
		NULL,
		D3DCOLOR_ARGB(pel, 0xff, 0xff, 0xff));

	m_pSprite->End();

}
void CEnemyBullet3::BulletMove()
{

	m_Pos += m_vSpeed;
}

void CEnemyBullet3::GetRc()
{
	int k = 15;									//k值决定碰撞区域大小
	rc_enemybullet3 = {
		(LONG)(m_Pos.x - m_rect.right / k),
		(LONG)(m_Pos.y - m_rect.bottom / k),
		(LONG)(m_Pos.x + m_rect.right / k),
		(LONG)(m_Pos.y + m_rect.bottom / k) };
}

bool CEnemyBullet3::IsHit()
{
	// 敌机子弹1、我机激光碰撞
	GetRc();
	CGameManager::GetGameInstance()->myplaybullet3.GetRC();
	if (HitTest(rc_enemybullet3, CGameManager::GetGameInstance()->myplaybullet3.rc_mybullet3) && CGameManager::GetGameInstance()->myplaybullet3.ishide == false)
	{
		return true;
	}

	// 敌机子弹1、我机子弹4碰撞检测
	list<CMyplayBullet4*>::iterator iter_mybullet4;
	for (iter_mybullet4 = CBulletManager::GetBulletInstance()->Mybulletlist4.begin(); iter_mybullet4 != CBulletManager::GetBulletInstance()->Mybulletlist4.end();)
	{
		GetRc();
		(*iter_mybullet4)->GetRC();
		if (HitTest(rc_enemybullet3, (*iter_mybullet4)->rc_mybullet4))
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