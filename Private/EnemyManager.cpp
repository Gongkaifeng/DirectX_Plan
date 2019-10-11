#pragma once
#include "stdafx.h"
CEnemyManager* CEnemyManager::m_pEnemyInstance = nullptr;
CEnemyManager::CEnemyManager()
{
}

CEnemyManager::~CEnemyManager()
{
	enemylist.clear();
	enemylist2.clear();
	enemylist3.clear();
}

void CEnemyManager::Update()
{
	CreateEnemy();				// 生成敌机1
	CreateEnemy2();				// 生成敌机2
	CreateEnemy3();				// 生成敌机3
	list<CEnemy*>::iterator iter;
	for (iter = enemylist.begin(); iter != enemylist.end();)
	{
		if ((*iter)->m_eState == eES_Dead)
		{
			delete *iter;
			iter = CEnemyManager::GetEnemyInstance()->enemylist.erase(iter);
			SoundManager::getSingletonPtr()->PlaySound(6, 0, NULL);			// 播放爆炸音乐
		}
		else if ((*iter)->m_Pos.x < 0 || (*iter)->m_Pos.x>600 || (*iter)->m_Pos.y > 900)
		{
			delete *iter;
			iter = CEnemyManager::GetEnemyInstance()->enemylist.erase(iter);
		}
		else
		{
			(*iter)->Update();
			++iter;
		}	
	}
	list<CEnemy2*>::iterator iter2;
	for (iter2 = enemylist2.begin(); iter2 != enemylist2.end();)
	{
		if ((*iter2)->m_eState2 == eES_Dead)
		{
			delete *iter2;
			iter2 = CEnemyManager::GetEnemyInstance()->enemylist2.erase(iter2);
			SoundManager::getSingletonPtr()->PlaySound(6, 0, NULL);			// 播放爆炸音乐
		}
		else if ((*iter2)->m_Pos.x < 0 || (*iter2)->m_Pos.x>600 || (*iter2)->m_Pos.y > 900)
		{
			delete *iter2;
			iter2 = CEnemyManager::GetEnemyInstance()->enemylist2.erase(iter2);
		}
		else
		{
			(*iter2)->Update();
			++iter2;
		}
	}
	list<CEnemy3*>::iterator iter3;
	for (iter3 = enemylist3.begin(); iter3 != enemylist3.end();)
	{
		if ((*iter3)->m_eState3 == eES_Dead)
		{
			delete *iter3;
			iter3 = CEnemyManager::GetEnemyInstance()->enemylist3.erase(iter3);
			SoundManager::getSingletonPtr()->PlaySound(6, 0, NULL);			// 播放爆炸音乐
			m_number_enemy3--;
		}
		else if ((*iter3)->m_Pos.x < 0 || (*iter3)->m_Pos.x>600 || (*iter3)->m_Pos.y > 900)
		{
			delete *iter3;
			iter3 = CEnemyManager::GetEnemyInstance()->enemylist3.erase(iter3);
			m_number_enemy3--;
		}
		else
		{
			(*iter3)->Update();
			++iter3;
		}
	}
}

void CEnemyManager::Render()
{
	// 敌机1渲染
	list<CEnemy*>::iterator iter5;
	for (iter5 = enemylist.begin(); iter5 != enemylist.end();)
	{
		(*iter5)->Render();
		iter5++;
	}
	// 敌机2渲染
	list<CEnemy2*>::iterator iter6;
	for (iter6 = enemylist2.begin(); iter6 != enemylist2.end();)
	{
		(*iter6)->Render();
		iter6++;
	}
	// 敌机3渲染
	list<CEnemy3*>::iterator iter7;
	for (iter7 = enemylist3.begin(); iter7 != enemylist3.end();)
	{
		(*iter7)->Render();
		iter7++;
	}
}

void CEnemyManager::CreateEnemy()
{
	// 通过计时器生成敌机
	static DWORD preTime = GetTickCount();
	DWORD curTime = GetTickCount();
	float elapsedTime = (curTime - preTime)*0.001f;			// 换算成秒
	if (elapsedTime >= 1.0f *1)								// 生成/S
	{
		D3DXVECTOR3 _Pos = { (float)(rand()%500+50) ,0 ,0 };
		D3DXVECTOR3 _center = { (float)CGameManager::GetGameInstance()->pic[_T("enemy01")]->GetWidth() / 2, (float)CGameManager::GetGameInstance()->pic[_T("enemy01")]->GetHeight() / 2 ,0 };
		RECT _rect = { 0,0, CGameManager::GetGameInstance()->pic[_T("enemy01")]->GetWidth(), CGameManager::GetGameInstance()->pic[_T("enemy01")]->GetHeight() };
		
		enemylist.push_back(new CEnemy(CGameManager::GetGameInstance()->pic[_T("enemy01")]->GetTexture(),_Pos,_center,_rect));

		preTime = curTime;
	}
}

void CEnemyManager::CreateEnemy2()
{
	// 通过计时器生成敌机
	static DWORD preTime = GetTickCount();
	DWORD curTime = GetTickCount();
	float elapsedTime = (curTime - preTime)*0.001f;				// 换算成秒
	if (elapsedTime >= 1.0f * 6)								// 生成/S
	{
		D3DXVECTOR3 _Pos = { (float)(rand() % 100 + 100) ,0 ,0 };
		D3DXVECTOR3 _center = { (float)CGameManager::GetGameInstance()->pic[_T("enemy02")]->GetWidth() / 2, (float)CGameManager::GetGameInstance()->pic[_T("enemy02")]->GetHeight() / 2 ,0 };
		RECT _rect = { 0,0, CGameManager::GetGameInstance()->pic[_T("enemy02")]->GetWidth(), CGameManager::GetGameInstance()->pic[_T("enemy02")]->GetHeight() };
		enemylist2.push_back(new CEnemy2(CGameManager::GetGameInstance()->pic[_T("enemy02")]->GetTexture(), _Pos, _center, _rect));

		D3DXVECTOR3 _Pos2 = { (float)(rand() % 100 + 400) ,0 ,0 };
		D3DXVECTOR3 _center2 = { (float)CGameManager::GetGameInstance()->pic[_T("enemy02")]->GetWidth() / 2, (float)CGameManager::GetGameInstance()->pic[_T("enemy02")]->GetHeight() / 2 ,0 };
		RECT _rect2 = { 0,0, CGameManager::GetGameInstance()->pic[_T("enemy02")]->GetWidth(), CGameManager::GetGameInstance()->pic[_T("enemy02")]->GetHeight() };
		enemylist2.push_back(new CEnemy2(CGameManager::GetGameInstance()->pic[_T("enemy02")]->GetTexture(), _Pos2, _center2, _rect2));

		preTime = curTime;
	}
}

void CEnemyManager::CreateEnemy3()
{
	// 通过计时器生成敌机
	static DWORD preTime = GetTickCount();
	DWORD curTime = GetTickCount();
	float elapsedTime = (curTime - preTime)*0.001f;				// 换算成秒
	if (elapsedTime >= 1.0f * 10 && m_number_enemy3 < 3)		// 生成/S
	{
		D3DXVECTOR3 _Pos = { (float)(rand() % 200 + 200) ,0 ,0 };
		D3DXVECTOR3 _center = { (float)CGameManager::GetGameInstance()->pic[_T("enemy04")]->GetWidth() / 2, (float)CGameManager::GetGameInstance()->pic[_T("enemy04")]->GetHeight() / 2 ,0 };
		RECT _rect = { 0,0, CGameManager::GetGameInstance()->pic[_T("enemy04")]->GetWidth(), CGameManager::GetGameInstance()->pic[_T("enemy04")]->GetHeight() };
		enemylist3.push_back(new CEnemy3(CGameManager::GetGameInstance()->pic[_T("enemy04")]->GetTexture(), _Pos, _center, _rect));
		preTime = curTime;
		m_number_enemy3++;
	}
}