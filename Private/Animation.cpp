#pragma once
#include "stdafx.h"
DWORD CAnimation::m_PreTime = 0;
CAnimation::CAnimation(TSTRING _Name, int _Frame)
{
	Name = _Name;
	Frame = _Frame;
	m_bIsplaying = true;
	m_bLoop = false;
}

CAnimation::~CAnimation()
{
}

void CAnimation::PlayAnimation()
{
	m_PreTime	  = GetTickCount();
	m_bIsplaying  = true;
	m_curFrame	  = 0;
	//m_bLoop = true;
}

void CAnimation::Update()
{
	if (!m_bIsplaying)
		return;
	DWORD curTime = GetTickCount();
	if ((curTime - m_PreTime)*0.001f < m_fTime)
		return;
	m_PreTime = GetTickCount();
	++m_curFrame;
	if (m_bLoop)
		m_curFrame %= Frame;
	else if (m_curFrame>=Frame)
	{
		//Í£Ö¹²¥·Å¶¯»­
		m_bIsplaying = false;
	}
}