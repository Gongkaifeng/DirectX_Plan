#pragma once
#include "stdafx.h"

CSceneManager::CSceneManager()
{
	NeedInit = false;//开始时不需初始化
}


CSceneManager::~CSceneManager()
{
}

void CSceneManager::AddScene(TSTRING name, CScene* scene)
{
	SceneList[name] = scene;
}

CScene* CSceneManager::GetCurScene()
{
	map<TSTRING, CScene*>::iterator it = SceneList.find(CurSceneName);
	return it->second;
}

void CSceneManager::SetCurSceneName(TSTRING name)
{
	CurSceneName = name;
}

TSTRING CSceneManager::GetCurSceneName()
{
	return CurSceneName;
}