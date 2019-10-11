#pragma once
#include "stdafx.h"

CBulletManager* CBulletManager::m_pBulletInstance = nullptr;

CBulletManager::CBulletManager()
{
	Ishit = false;
}
CBulletManager::~CBulletManager()
{
	Mybulletlist.clear();
	Mybulletlist2.clear();
	Mybulletlist4.clear();

	Enbulletlist.clear();
	Enbulletlist2.clear();
	Enbulletlist3.clear();
}

void CBulletManager::Update()
{
	// 遍历我机子弹，超出边界删除我机子弹
	list<CMyplayBullet*>::iterator iter_mybullet;
	for (iter_mybullet = Mybulletlist.begin(); iter_mybullet != Mybulletlist.end();)
	{	
		if ((*iter_mybullet)->m_Pos.y <= 0 )
		{
			delete *iter_mybullet;
			iter_mybullet = CBulletManager::GetBulletInstance()->Mybulletlist.erase(iter_mybullet);
		}
		else
		{
			(*iter_mybullet)->Update();
			iter_mybullet++;
		}
	}

	// 遍历我机子弹2，超出边界删除我机子弹
	list<CMyplayBullet2*>::iterator iter_mybullet2;
	for (iter_mybullet2 = Mybulletlist2.begin(); iter_mybullet2 != Mybulletlist2.end();)
	{
		if ((*iter_mybullet2)->m_Pos.y <= 0 || (*iter_mybullet2)->m_Pos.x < 0 || (*iter_mybullet2)->m_Pos.x>600)
		{
			delete *iter_mybullet2;
			iter_mybullet2 = CBulletManager::GetBulletInstance()->Mybulletlist2.erase(iter_mybullet2);
		}
		else
		{
			(*iter_mybullet2)->Update();
			iter_mybullet2++;
		}
	}
	// 遍历我机子弹4，超出边界删除我机子弹
	list<CMyplayBullet4*>::iterator iter_mybullet4;
	for (iter_mybullet4 = Mybulletlist4.begin(); iter_mybullet4 != Mybulletlist4.end();)
	{
		if ((*iter_mybullet4)->m_Pos.y <= -100 )
		{
			delete *iter_mybullet4;
			iter_mybullet4 = CBulletManager::GetBulletInstance()->Mybulletlist4.erase(iter_mybullet4);
		}
		else
		{
			(*iter_mybullet4)->Update();
			iter_mybullet4++;
		}
	}

	// 遍历敌机1子弹，超出边界、或者被我机激光攻击到，则删除敌机子弹
	list<CEnemyBullet*>::iterator iter_enemybullet;
	for (iter_enemybullet = CBulletManager::GetBulletInstance()->Enbulletlist.begin(); iter_enemybullet != CBulletManager::GetBulletInstance()->Enbulletlist.end();)
	{
		if ((*iter_enemybullet)->m_Pos.x <= 0 || (*iter_enemybullet)->m_Pos.x >= 600 || (*iter_enemybullet)->m_Pos.y >= 900 || (*iter_enemybullet)->IsHit()==true)
		{
			delete *iter_enemybullet;
			iter_enemybullet = CBulletManager::GetBulletInstance()->Enbulletlist.erase(iter_enemybullet);
		}
		else
		{
			(*iter_enemybullet)->Update();
			iter_enemybullet++;
		}
	}

	// 敌机2子弹2，超出边界、或者被我机激光攻击到，删除
	list<CEnemyBullet2*>::iterator iter_enemybullet2;
	for (iter_enemybullet2 = CBulletManager::GetBulletInstance()->Enbulletlist2.begin(); iter_enemybullet2 != CBulletManager::GetBulletInstance()->Enbulletlist2.end();)
	{
		if ((*iter_enemybullet2)->m_Pos.x <= 0 || (*iter_enemybullet2)->m_Pos.x >= 600 || (*iter_enemybullet2)->m_Pos.y >= 900 || (*iter_enemybullet2)->IsHit() == true)
		{
			delete *iter_enemybullet2;
			iter_enemybullet2 = CBulletManager::GetBulletInstance()->Enbulletlist2.erase(iter_enemybullet2);
		}
		else
		{
			(*iter_enemybullet2)->Update();
			iter_enemybullet2++;
		}
	}

	// 敌机3子弹3，超出边界、或者被我机激光攻击到，删除
	list<CEnemyBullet3*>::iterator iter_enemybullet3;
	for (iter_enemybullet3 = CBulletManager::GetBulletInstance()->Enbulletlist3.begin(); iter_enemybullet3 != CBulletManager::GetBulletInstance()->Enbulletlist3.end();)
	{
		if ((*iter_enemybullet3)->m_Pos.x <= 0 || (*iter_enemybullet3)->m_Pos.x >= 600 || (*iter_enemybullet3)->m_Pos.y >= 900 || (*iter_enemybullet3)->IsHit() == true)
		{
			delete *iter_enemybullet3;
			iter_enemybullet3 = CBulletManager::GetBulletInstance()->Enbulletlist3.erase(iter_enemybullet3);
		}
		else
		{
			(*iter_enemybullet3)->Update();
			iter_enemybullet3++;
		}
	}
}

void CBulletManager::Render()
{
	// 我机子弹渲染更新
	list<CMyplayBullet*>::iterator iter_my;
	for (iter_my = Mybulletlist.begin(); iter_my != Mybulletlist.end(); iter_my++)
	{
		(*iter_my)->Render();
	}
	// 我机子弹2渲染更新
	list<CMyplayBullet2*>::iterator iter_my2;
	for (iter_my2 = Mybulletlist2.begin(); iter_my2 != Mybulletlist2.end(); iter_my2++)
	{
		(*iter_my2)->Render();
	}
	// 我机子弹4渲染更新
	list<CMyplayBullet4*>::iterator iter_my4;
	for (iter_my4 = Mybulletlist4.begin(); iter_my4 != Mybulletlist4.end(); iter_my4++)
	{
		(*iter_my4)->Render();
	}

	// 敌机子弹1渲染更新
	list<CEnemyBullet*>::iterator iter_enemy;
	for (iter_enemy = Enbulletlist.begin(); iter_enemy != Enbulletlist.end(); iter_enemy++)
	{
		(*iter_enemy)->Render();
	}
	// 敌机子弹2渲染更新
	list<CEnemyBullet2*>::iterator iter_enemy2;
	for (iter_enemy2 = Enbulletlist2.begin(); iter_enemy2 != Enbulletlist2.end(); iter_enemy2++)
	{
		(*iter_enemy2)->Render();
	}
	// 敌机子弹3渲染更新
	list<CEnemyBullet3*>::iterator iter_enemy3;
	for (iter_enemy3 = Enbulletlist3.begin(); iter_enemy3 != Enbulletlist3.end(); iter_enemy3++)
	{
		(*iter_enemy3)->Render();
	}
}
