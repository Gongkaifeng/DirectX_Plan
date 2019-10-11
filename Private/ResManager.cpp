#pragma once
#include "stdafx.h"
CResManager* CResManager::m_pResInstance = nullptr;

CResManager::CResManager()
{
}
CResManager::~CResManager()
{
	map<TSTRING, CPicture*>::iterator it1 = picture.begin();
	for (; it1 != picture.end();it1++)
	{
		delete it1->second;
	}
	picture.clear();

	map<TSTRING, CAnimationFrame*>::iterator it2 = frame.begin();
	for (; it2 != frame.end(); it2++)
	{
		delete it2->second;
	}
	frame.clear();

	map<TSTRING, CAnimation*>::iterator it3 = animation.begin();
	for (; it3 != animation.end(); it3++)
	{
		delete it3->second;
	}
	animation.clear();
}

void CResManager::LoadPictureInit()
{
	AddPicture(_T("map"), new CPicture(_T("map"), _T("..bin/")));				// ±≥æ∞Õº∆¨
	AddPicture(_T("player01"), new CPicture(_T("player01"), _T("..bin/")));		// ’Ω∂∑ª˙

	AddPicture(_T("bullet01"), new CPicture(_T("bullet01"), _T("..bin/")));		// Œ“◊”µØ01
	AddPicture(_T("bullet02"), new CPicture(_T("bullet02"), _T("..bin/")));		// Œ“◊”µØ02
	AddPicture(_T("bullet03"), new CPicture(_T("bullet03"), _T("..bin/")));		// Œ“◊”µØ03
	AddPicture(_T("bullet05"), new CPicture(_T("bullet05"), _T("..bin/")));		// Œ“◊”µØ05

	AddPicture(_T("bullet06"), new CPicture(_T("bullet06"), _T("..bin/")));		// µ–◊”µØ06

	AddPicture(_T("enemy01"), new CPicture(_T("enemy01"), _T("..bin/")));		// µ–∑…ª˙01
	AddPicture(_T("enemy02"), new CPicture(_T("enemy02"), _T("..bin/")));		// µ–∑…ª˙02
	AddPicture(_T("enemy03"), new CPicture(_T("enemy03"), _T("..bin/")));		// µ–∑…ª˙03

	AddPicture(_T("boom01"), new CPicture(_T("boom01"), _T("..bin/")));			// ±¨’®01
	AddPicture(_T("boom02"), new CPicture(_T("boom02"), _T("..bin/")));			// ±¨’®02
	AddPicture(_T("boom03"), new CPicture(_T("boom03"), _T("..bin/")));			// ±¨’®03
	AddPicture(_T("boom04"), new CPicture(_T("boom04"), _T("..bin/")));			// ±¨’®04
}

void CResManager::LoadAnimationFrameInit()
{
	// ±¨’®÷°Õº∆¨
	RECT rc_boom1 = {0,0,picture[_T("boom01")]->GetWidth(),picture[_T("boom01")]->GetHeight() };
	AddAnimationFrame(_T("boom01"), new CAnimationFrame(_T("boom01"), picture[_T("boom01")]->GetTexture(), rc_boom1));
	RECT rc_boom2 = { 0,0,picture[_T("boom02")]->GetWidth(),picture[_T("boom02")]->GetHeight() };
	AddAnimationFrame(_T("boom02"), new CAnimationFrame(_T("boom02"), picture[_T("boom02")]->GetTexture(), rc_boom1));
	RECT rc_boom3 = { 0,0,picture[_T("boom03")]->GetWidth(),picture[_T("boom03")]->GetHeight() };
	AddAnimationFrame(_T("boom03"), new CAnimationFrame(_T("boom03"), picture[_T("boom03")]->GetTexture(), rc_boom1));
	RECT rc_boom4 = { 0,0,picture[_T("boom04")]->GetWidth(),picture[_T("boom04")]->GetHeight() };
	AddAnimationFrame(_T("boom04"), new CAnimationFrame(_T("boom04"), picture[_T("boom04")]->GetTexture(), rc_boom1));
}

void CResManager::LoadAnimationInit()
{
	// Ω´±¨’®4’≈Õº∆¨—π»Î÷°∂Øª≠÷–
	animation.insert(pair<TSTRING, CAnimation*>(_T("boom"), new CAnimation(_T("boom"),4)));
	{
		animation[_T("boom")]->FrameList.push_back(GetAnimationFrame(_T("boom01")));
		animation[_T("boom")]->FrameList.push_back(GetAnimationFrame(_T("boom02")));
		animation[_T("boom")]->FrameList.push_back(GetAnimationFrame(_T("boom03")));
		animation[_T("boom")]->FrameList.push_back(GetAnimationFrame(_T("boom04")));
	}
}

void CResManager::AddPicture(TSTRING name, CPicture* pic)
{
	picture[name] = pic;
}

void CResManager::AddAnimationFrame(TSTRING framename, CAnimationFrame* animationframe)
{
	frame[framename] = animationframe;
}

void CResManager::AddAnimation(TSTRING animationName, CAnimation* ani)
{
	animation[animationName] = ani;
}

CPicture* CResManager::GetPicture(TSTRING name)
{
	map<TSTRING, CPicture*>::iterator it = picture.find(name);
	if (it != picture.end())
		return it->second;
}

CAnimationFrame* CResManager::GetAnimationFrame(TSTRING animationName)
{
	map<TSTRING, CAnimationFrame*>::iterator iter = frame.find(animationName);
	if (iter != frame.end())
		return iter->second;
}

CAnimation * CResManager::GetAnimation(TSTRING animationName)
{
	map<TSTRING, CAnimation*>::iterator iter = animation.find(animationName);
	if (iter != animation.end())
		return iter->second;
}

void CResManager::Update()
{

}

void CResManager::Render()
{

}