#pragma once
#include "stdafx.h"

CUIObject::CUIObject(void)
{
}
CUIObject::~CUIObject(void)
{
}

D3DXVECTOR3 CUIObject::GetPos()
{
	return m_vPos;
}