#pragma once
#include "stdafx.h"

CMyplayer::CMyplayer()
{
}
CMyplayer::~CMyplayer()
{
}

void CMyplayer::Init(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect)
{
	m_Texture		= _Texture;
	m_Pos			= _Pos;
	m_angle			= 0;
	m_center		= _center;
	m_rect			= _rect;
	m_vSpeed		= D3DXVECTOR3(0, 0, 0);
	m_Speed			= 6;						// 玩家移动速度
	m_mState		= eMS_Normal;
	m_hp_myplayer	= MAXHP_PLAYER;
	pel				= 255;
	scaleX			= 0.5;
	scaleY			= 0.5;
	D3DXCreateSprite(CGameManager::GetGameInstance()->D3DDevice, &m_pSprite);	// 精灵初始化
}

void CMyplayer::Update()
{
	switch (m_mState)
	{
	case eMS_Normal:
	{
		PlayerMove();
		// 通过计时器来生成子弹(区分激光与其他子弹的生成时间)
		static DWORD preTime = GetTickCount();
		DWORD curTime = GetTickCount();
		float elapsedTime = (curTime - preTime)*0.001f;//换算成秒
		switch (style_fire)
		{
		case FIRE_01:
		case FIRE_02:
		case FIRE_03:
		case FIRE_04:
		{
			if (elapsedTime >= 1.0f / 8)
			{
				PlayerFire();
				preTime = curTime;
			}
		}
			break;
		case FIRE_05:
		{
			if (elapsedTime >= 1.0f / 25)
			{
				PlayerFire();
				preTime = curTime;
			}
		}
			break;
		default:
			break;
		}
		
		// 如果我机攻击方式为FIRE_04，则将我机纹理图更换为player02
		if (style_fire == FIRE_04)
		{
			m_Texture = CGameManager::GetGameInstance()->pic[_T("player02")]->GetTexture();
		}
		else
		{
			m_Texture = CGameManager::GetGameInstance()->pic[_T("player01")]->GetTexture();
		}
		// 我机与敌机子弹碰撞检测,血量减少、如果为零则更换我机状态m_mState。
		if (IsHit())
		{
			SoundManager::getSingletonPtr()->PlaySound(7, 0, NULL);			// 播放被击中音乐
			m_hp_myplayer -= 1;
			if (m_hp_myplayer <=0)
			{
				m_mState = eMS_Boom;
				MyBoom();
			}
		}
	}
		break;
	
	case eMS_Skill:
	{
		CGameManager::GetGameInstance()->skill_Sprite.Update();
		list<CMyplayBullet4*>::iterator iter_mybullet4 = CBulletManager::GetBulletInstance()->Mybulletlist4.begin();
		if ((*iter_mybullet4)->m_Pos.y <= -100)
		{
			m_mState = eMS_Normal;
			CGameManager::GetGameInstance()->skill_Sprite.m_Pos.y = 1300;
		}
	}
	break;

	case eMS_Boom:
	{
		//PlayerMove();
		CGameManager::GetGameInstance()->myplaybullet3.ishide = true;
		pel -= 5;
		
		DWORD m_curTime = GetTickCount();
		float elapsedTime = (m_curTime - m_preTime)*0.001f;//换算成秒
		
		if (elapsedTime >= 1.0f * 4)
		{
			m_mState = eMS_Normal;
			pel = 255;
			m_hp_myplayer = 50;
			m_preTime = m_curTime;
		}
	}
		break;

	case eMS_Dead:
	{

	}
		break;
	default:
		break;
	}
}

void CMyplayer::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMatrixScaling(&scaleMat, scaleX, scaleY, 0);					// 缩放
	D3DXMatrixRotationZ(&roteMat, m_angle);						// 旋转
	D3DXMatrixTranslation(&transMat, m_Pos.x, m_Pos.y, 0);		// 平移
	matMatrix = scaleMat*roteMat*transMat;
	m_pSprite->SetTransform(&matMatrix);
	m_pSprite->Draw(m_Texture,
		&m_rect,
		&m_center,
		NULL,
		D3DCOLOR_ARGB(pel, 0xff, 0xff, 0xff));
	m_pSprite->End();

	if (m_mState == eMS_Skill)
	{
		CGameManager::GetGameInstance()->skill_Sprite.Render();
	}
	if (m_mState == eMS_Boom)
	{
		CGameManager::GetGameInstance()->gameover.Render();
		CGameManager::GetGameInstance()->gameover.pel--;
	}
}

void CMyplayer::PlayerMove()
{
	dir1 = DIR_NONE; dir2 = DIR_NONE; style_fire = FIRE_NONE;
	CGameManager::GetGameInstance()->myplaybullet3.ishide = true;
	g_DXInput.GetInput();				//获取输入事件
	// 根据按键修改8个方向
	if (g_DXInput.IsKeyHold(DIK_W) || g_DXInput.IsKeyCurrentDown(DIK_W))
	{
		dir1 = DIR_UP;
	}
	else if (g_DXInput.IsKeyHold(DIK_S) || g_DXInput.IsKeyCurrentDown(DIK_S))
	{
		dir1 = DIR_DOWN;
	}
	if (g_DXInput.IsKeyHold(DIK_A) || g_DXInput.IsKeyCurrentDown(DIK_A))
	{
		dir2 = DIR_LEFT;
	}
	else if (g_DXInput.IsKeyHold(DIK_D) || g_DXInput.IsKeyCurrentDown(DIK_D))
	{
		dir2 = DIR_RIGHT;
	}

	if (g_DXInput.IsKeyHold(DIK_J) || g_DXInput.IsKeyCurrentDown(DIK_J))
	{
		style_fire = FIRE_01;
	}
	if (g_DXInput.IsKeyHold(DIK_K) || g_DXInput.IsKeyCurrentDown(DIK_K))
	{
		style_fire = FIRE_05;
	}
	if (g_DXInput.IsKeyHold(DIK_L) || g_DXInput.IsKeyCurrentDown(DIK_L))
	{
		style_fire = FIRE_04;
	}
	if (g_DXInput.IsKeyHold(DIK_T) || g_DXInput.IsKeyCurrentDown(DIK_T))
	{
		style_fire = FIRE_06;	// 放大招
		D3DXVECTOR3 _Pos10 = { 80 ,m_Pos.y + 200 ,0 };
		D3DXVECTOR3 _center10 = { (float)CGameManager::GetGameInstance()->pic[_T("skill01")]->GetWidth() / 2, (float)CGameManager::GetGameInstance()->pic[_T("skill01")]->GetHeight() / 2 ,0 };
		D3DXVECTOR3 _vSpeed10 = { 0,-15,0 };
		RECT _rect10 = { 0,0, CGameManager::GetGameInstance()->pic[_T("skill01")]->GetWidth(), CGameManager::GetGameInstance()->pic[_T("skill01")]->GetHeight() };
		CBulletManager::GetBulletInstance()->Mybulletlist4.push_back(new CMyplayBullet4(CGameManager::GetGameInstance()->pic[_T("skill01")]->GetTexture(), _Pos10, _center10, _rect10, _vSpeed10));

		D3DXVECTOR3 _Pos11 = { 220 ,m_Pos.y + 200 ,0 };
		D3DXVECTOR3 _center11 = { (float)CGameManager::GetGameInstance()->pic[_T("skill01")]->GetWidth() / 2, (float)CGameManager::GetGameInstance()->pic[_T("skill01")]->GetHeight() / 2 ,0 };
		D3DXVECTOR3 _vSpeed11 = { 0,-15,0 };
		RECT _rect11 = { 0,0, CGameManager::GetGameInstance()->pic[_T("skill01")]->GetWidth(), CGameManager::GetGameInstance()->pic[_T("skill01")]->GetHeight() };
		CBulletManager::GetBulletInstance()->Mybulletlist4.push_back(new CMyplayBullet4(CGameManager::GetGameInstance()->pic[_T("skill01")]->GetTexture(), _Pos11, _center11, _rect11, _vSpeed11));

		D3DXVECTOR3 _Pos12 = { 380 ,m_Pos.y + 200 ,0 };
		D3DXVECTOR3 _center12 = { (float)CGameManager::GetGameInstance()->pic[_T("skill01")]->GetWidth() / 2, (float)CGameManager::GetGameInstance()->pic[_T("skill01")]->GetHeight() / 2 ,0 };
		D3DXVECTOR3 _vSpeed12 = { 0,-15,0 };
		RECT _rect12 = { 0,0, CGameManager::GetGameInstance()->pic[_T("skill01")]->GetWidth(), CGameManager::GetGameInstance()->pic[_T("skill01")]->GetHeight() };
		CBulletManager::GetBulletInstance()->Mybulletlist4.push_back(new CMyplayBullet4(CGameManager::GetGameInstance()->pic[_T("skill01")]->GetTexture(), _Pos12, _center12, _rect12, _vSpeed12));

		D3DXVECTOR3 _Pos13 = { 520 ,m_Pos.y + 200 ,0 };
		D3DXVECTOR3 _center13 = { (float)CGameManager::GetGameInstance()->pic[_T("skill01")]->GetWidth() / 2, (float)CGameManager::GetGameInstance()->pic[_T("skill01")]->GetHeight() / 2 ,0 };
		D3DXVECTOR3 _vSpeed13 = { 0,-15,0 };
		RECT _rect13 = { 0,0, CGameManager::GetGameInstance()->pic[_T("skill01")]->GetWidth(), CGameManager::GetGameInstance()->pic[_T("skill01")]->GetHeight() };
		CBulletManager::GetBulletInstance()->Mybulletlist4.push_back(new CMyplayBullet4(CGameManager::GetGameInstance()->pic[_T("skill01")]->GetTexture(), _Pos13, _center13, _rect13, _vSpeed13));
		m_mState = eMS_Skill;
	}

	int TempSpeed = m_Speed;
	if (dir1 != DIR_NONE || dir2 != DIR_NONE)
	{
		if (dir1 == DIR_UP)
		{
			m_vSpeed += D3DXVECTOR3(0, -TempSpeed, 0);
		}
		else if (dir1 == DIR_DOWN)
		{
			m_vSpeed += D3DXVECTOR3(0, +TempSpeed, 0);
		}
		if (dir2 == DIR_LEFT)
		{
			m_vSpeed += D3DXVECTOR3(-TempSpeed, 0, 0);
		}
		else if (dir2 == DIR_RIGHT)
		{
			m_vSpeed += D3DXVECTOR3(+TempSpeed, 0, 0);
		}
		D3DXVec3Normalize(&m_vSpeed, &m_vSpeed);
		m_vSpeed *= m_Speed;
		m_Pos += m_vSpeed;
		if (m_Pos.x<=0)
			m_Pos.x = 0;
		if (m_Pos.x >= 600)
			m_Pos.x = 600;
		if (m_Pos.y<=0)
			m_Pos.y = 0;
		if (m_Pos.y >= 900)
			m_Pos.y = 900;
	}
}

void CMyplayer::PlayerFire()
{
	switch (style_fire)
	{
		// 攻击模式：单发
	case FIRE_01:
	{
		D3DXVECTOR3 _Pos = { m_Pos.x ,m_Pos.y - 20 ,0 };
		D3DXVECTOR3 _center = { (float)CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetWidth() / 2, (float)CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetHeight() / 2 ,0 };
		D3DXVECTOR3 _vSpeed = { 0,-8,0 };
		RECT _rect = { 0,0, CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetWidth(), CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetHeight() };

		CBulletManager::GetBulletInstance()->Mybulletlist.push_back(new CMyplayBullet(CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetTexture(), _Pos, _center, _rect, _vSpeed));
		
		SoundManager::getSingletonPtr()->PlaySound(3, 0, NULL);			// 播放开火音乐
	}
	break;
	// 攻击模式：两发
	case FIRE_02:
	{
		D3DXVECTOR3 _Pos = { m_Pos.x - 15 ,m_Pos.y - 20 ,0 };
		D3DXVECTOR3 _Pos2 = { m_Pos.x + 15 ,m_Pos.y - 20 ,0 };
		D3DXVECTOR3 _center = { (float)CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetWidth() / 2, (float)CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetHeight() / 2 ,0 };
		D3DXVECTOR3 _vSpeed = { 0,-8,0 };
		RECT _rect = { 0,0, CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetWidth(), CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetHeight() };
		CBulletManager::GetBulletInstance()->Mybulletlist.push_back(new CMyplayBullet(CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetTexture(), _Pos, _center, _rect, _vSpeed));
		CBulletManager::GetBulletInstance()->Mybulletlist.push_back(new CMyplayBullet(CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetTexture(), _Pos2, _center, _rect,_vSpeed));
	}
	break;
	// 攻击模式：三发
	case FIRE_03:
	{
		D3DXVECTOR3 _Pos ={ m_Pos.x,m_Pos.y - 20 ,0 };
		D3DXVECTOR3 _Pos2 = { m_Pos.x - 20 ,m_Pos.y - 20 ,0 };
		D3DXVECTOR3 _Pos3 = { m_Pos.x + 20 ,m_Pos.y - 20 ,0 };
		D3DXVECTOR3 _center = { (float)CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetWidth() / 2, (float)CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetHeight() / 2 ,0 };
		D3DXVECTOR3 _vSpeed = { 0,-8,0 };
		RECT _rect = { 0,0, CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetWidth(), CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetHeight() };
		CBulletManager::GetBulletInstance()->Mybulletlist.push_back(new CMyplayBullet(CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetTexture(), _Pos, _center, _rect, _vSpeed));
		CBulletManager::GetBulletInstance()->Mybulletlist.push_back(new CMyplayBullet(CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetTexture(), _Pos2, _center, _rect, _vSpeed));
		CBulletManager::GetBulletInstance()->Mybulletlist.push_back(new CMyplayBullet(CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetTexture(), _Pos3, _center, _rect, _vSpeed));
	}
	break;
	// 攻击模式：三发+跟踪导弹
	case FIRE_04:
	{
		// 跟踪导弹攻击顺序：BOSS、小boss、小敌机
		D3DXVECTOR3 _Pos = { m_Pos.x - 40 ,m_Pos.y ,0 };
		D3DXVECTOR3 _Pos2 = { m_Pos.x + 40 ,m_Pos.y ,0 };
		D3DXVECTOR3 _vSpeed;
		D3DXVECTOR3 _vSpeed2;
		list<CEnemy*>::iterator iter_enemy = CEnemyManager::GetEnemyInstance()->enemylist.begin();
		list<CEnemy2*>::iterator iter_enemy2 = CEnemyManager::GetEnemyInstance()->enemylist2.begin();		
		list<CEnemy3*>::iterator iter_enemy3 = CEnemyManager::GetEnemyInstance()->enemylist3.begin();	
		if (iter_enemy3 != CEnemyManager::GetEnemyInstance()->enemylist3.end())
		{
			_vSpeed = (*iter_enemy3)->m_Pos - _Pos;
			_vSpeed2 = (*iter_enemy3)->m_Pos - _Pos2;
		}
		else if (iter_enemy2!= CEnemyManager::GetEnemyInstance()->enemylist2.end())
		{
			_vSpeed = (*iter_enemy2)->m_Pos - _Pos;
			_vSpeed2 = (*iter_enemy2)->m_Pos - _Pos2;
		}
		else if (iter_enemy != CEnemyManager::GetEnemyInstance()->enemylist.end())
		{
			_vSpeed = (*iter_enemy)->m_Pos - _Pos;
			_vSpeed2 = (*iter_enemy)->m_Pos - _Pos2;
		}
		else
		{
			_vSpeed = { 0,-1,0 };
			_vSpeed2 = { 0,-1,0 };
		}
		D3DXVec3Normalize(&_vSpeed, &_vSpeed);
		D3DXVec3Normalize(&_vSpeed2, &_vSpeed2); 
		D3DXVECTOR3 _center = { (float)CGameManager::GetGameInstance()->pic[_T("bullet05")]->GetWidth() / 2, (float)CGameManager::GetGameInstance()->pic[_T("bullet05")]->GetHeight() / 2 ,0 };
		RECT _rect = { 0,0, CGameManager::GetGameInstance()->pic[_T("bullet05")]->GetWidth(), CGameManager::GetGameInstance()->pic[_T("bullet05")]->GetHeight() };
		CBulletManager::GetBulletInstance()->Mybulletlist2.push_back(new CMyplayBullet2(CGameManager::GetGameInstance()->pic[_T("bullet05")]->GetTexture(), _Pos, _center, _rect, _vSpeed));
		CBulletManager::GetBulletInstance()->Mybulletlist2.push_back(new CMyplayBullet2(CGameManager::GetGameInstance()->pic[_T("bullet05")]->GetTexture(), _Pos2, _center, _rect, _vSpeed2));
	
		D3DXVECTOR3 _Pos3 = { m_Pos.x,m_Pos.y - 20 ,0 };
		D3DXVECTOR3 _Pos4 = { m_Pos.x - 20 ,m_Pos.y - 20 ,0 };
		D3DXVECTOR3 _Pos5 = { m_Pos.x + 20 ,m_Pos.y - 20 ,0 };
		D3DXVECTOR3 _center2 = { (float)CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetWidth() / 2, (float)CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetHeight() / 2 ,0 };
		D3DXVECTOR3 _vSpeed3 = { 0,-8,0 };
		RECT _rect3 = { 0,0, CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetWidth(), CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetHeight() };
		CBulletManager::GetBulletInstance()->Mybulletlist.push_back(new CMyplayBullet(CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetTexture(), _Pos3, _center2, _rect3, _vSpeed3));
		CBulletManager::GetBulletInstance()->Mybulletlist.push_back(new CMyplayBullet(CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetTexture(), _Pos4, _center2, _rect3, _vSpeed3));
		CBulletManager::GetBulletInstance()->Mybulletlist.push_back(new CMyplayBullet(CGameManager::GetGameInstance()->pic[_T("bullet01")]->GetTexture(), _Pos5, _center2, _rect3, _vSpeed3));
	
		SoundManager::getSingletonPtr()->PlaySound(5, 0, NULL);			// 播放开火音乐
	}
	break;
	// 攻击模式：激光
	case FIRE_05:
	{
		CGameManager::GetGameInstance()->myplaybullet3.ishide = false;
		SoundManager::getSingletonPtr()->PlaySound(4, 0, NULL);			// 播放极光音乐
	}
	break;
	// 攻击模式：技能战机变大
	case FIRE_06:
	{

		
	}
	break;
	default:
		break;
	}
}

bool CMyplayer::IsHit()
{
	// 我机、敌方子弹1碰撞检测
	list<CEnemyBullet*>::iterator iter_enemybullet;
	for (iter_enemybullet = CBulletManager::GetBulletInstance()->Enbulletlist.begin(); iter_enemybullet != CBulletManager::GetBulletInstance()->Enbulletlist.end();)
	{
		GetRc();
		(*iter_enemybullet)->GetRc();
		if (HitTest(rc_myplayer, (*iter_enemybullet)->rc_enemybullet))
		{
			//删除敌机子弹
			delete *iter_enemybullet;
			iter_enemybullet = CBulletManager::GetBulletInstance()->Enbulletlist.erase(iter_enemybullet);
			return true;
		}
		else
		{
			iter_enemybullet++;
		}
	}
	// 我机、敌方子弹2碰撞检测
	list<CEnemyBullet2*>::iterator iter_enemybullet2;
	for (iter_enemybullet2 = CBulletManager::GetBulletInstance()->Enbulletlist2.begin(); iter_enemybullet2 != CBulletManager::GetBulletInstance()->Enbulletlist2.end();)
	{
		GetRc();
		(*iter_enemybullet2)->GetRc();
		if (HitTest(rc_myplayer, (*iter_enemybullet2)->rc_enemybullet2))
		{
			//删除敌机子弹
			delete *iter_enemybullet2;
			iter_enemybullet2 = CBulletManager::GetBulletInstance()->Enbulletlist2.erase(iter_enemybullet2);
			return true;
		}
		else
		{
			iter_enemybullet2++;
		}
	}
	// 我机、敌方子弹3碰撞检测
	list<CEnemyBullet3*>::iterator iter_enemybullet3;
	for (iter_enemybullet3 = CBulletManager::GetBulletInstance()->Enbulletlist3.begin(); iter_enemybullet3 != CBulletManager::GetBulletInstance()->Enbulletlist3.end();)
	{
		GetRc();
		(*iter_enemybullet3)->GetRc();
		if (HitTest(rc_myplayer, (*iter_enemybullet3)->rc_enemybullet3))
		{
			//删除敌机子弹
			delete *iter_enemybullet3;
			iter_enemybullet3 = CBulletManager::GetBulletInstance()->Enbulletlist3.erase(iter_enemybullet3);
			return true;
		}
		else
		{
			iter_enemybullet3++;
		}
	}
	return false;
}

void CMyplayer::GetRc()
{
	int k = 10;									//k值决定碰撞区域大小
	rc_myplayer = {
		(LONG)(m_Pos.x - m_rect.right / k),
		(LONG)(m_Pos.y - m_rect.bottom / k),
		(LONG)(m_Pos.x + m_rect.right / k),
		(LONG)(m_Pos.y + m_rect.bottom / k) };
}

void CMyplayer::MyBoom()
{
	m_preTime = GetTickCount();
}

