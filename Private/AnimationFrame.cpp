#pragma once
#include "stdafx.h"

CAnimationFrame::CAnimationFrame(TSTRING _Name, LPDIRECT3DTEXTURE9 _Texture, RECT _Rect)
{
	m_Name = _Name;
	m_Texture = _Texture;
	m_Rect = _Rect;
}


CAnimationFrame::~CAnimationFrame()
{
}
