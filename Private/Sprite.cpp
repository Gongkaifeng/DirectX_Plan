#pragma once
#include "stdafx.h"

CSprite::CSprite()
{
}

CSprite::~CSprite()
{
	if (m_pSprite != nullptr)
		m_pSprite->Release();

}
//精灵初始化(传入纹理，图片显示位置）
void CSprite::Init(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect)
{
	m_Texture = _Texture;
	m_Pos     = _Pos;
	m_center  = _center;
	m_rect	  = _rect;	
	D3DXCreateSprite(CGameManager::GetGameInstance()->D3DDevice, &m_pSprite);	// 精灵初始化	
	
}

void CSprite::Update()		// 更新 虚函数
{

}
void CSprite::Render()		// 绘制 虚函数
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMATRIX scaleMat, roteMat, transMat;
	D3DXMatrixScaling(&scaleMat, 1, 1, 0);												// 缩放
	D3DXMatrixRotationZ(&roteMat, m_angle);												// 旋转
	D3DXMatrixTranslation(&transMat, m_Pos.x, m_Pos.y, 0);								// 平移
	D3DXMATRIX mat = scaleMat*roteMat*transMat;
	m_pSprite->SetTransform(&mat);

	m_pSprite->Draw(m_Texture,
		&m_rect,
		&m_center,
		NULL,
		D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	m_pSprite->End();
}

bool CSprite::HitTest(RECT rc1, RECT rc2)
{
	RECT tmpRC;
	// 横向检测
	HITSTRUCT hsH[4] = { rc1.left,1,rc1.right,1,rc2.left,2,rc2.right,2 };
	Sort4(hsH);
	if (hsH[0].Flag == hsH[1].Flag) return false;
	// 纵向检测
	HITSTRUCT hsV[4] = { rc1.top,1,rc1.bottom,1,rc2.top,2,rc2.bottom,2 };
	Sort4(hsV);
	if (hsV[0].Flag == hsV[1].Flag) return false;
	// 保存碰撞的重合区域

	return true;
}

void CSprite::Sort4(HITSTRUCT *List)
{
	HITSTRUCT t;
	if (List[0].Value > List[2].Value) SWAP(0, 2);
	if (List[1].Value > List[3].Value) SWAP(1, 3);
	if (List[0].Value > List[1].Value) SWAP(0, 1);
	if (List[2].Value > List[3].Value) SWAP(2, 3);
	if (List[1].Value > List[2].Value) SWAP(1, 2);
}