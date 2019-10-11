#pragma  once
#include "stdafx.h"
#include "Player.h"



CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init(RECT _clientRC,TSTRING _Name, TSTRING _Path, IDirect3DDevice9* _g_pDevice, DWORD _xnum, DWORD _ynum, int _Speed,float _Rote)
{
	m_clientRC = _clientRC;
	dir1 = DIR_NONE;
	dir2 = DIR_NONE;
	Pic1.Init(_Name, _Path, _g_pDevice, _xnum, _ynum, _Speed, _Rote);
}

void CPlayer::PlayerMove()
{
	//dir1 = DIR_NONE; dir2 = DIR_NONE;
	//Pic1.m_vSpeed = D3DXVECTOR3(0,0,0);
	//g_DXInput.GetInput();				//获取输入事件
    //根据按键修改8个方向
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

	int TempSpeed = Pic1.m_Speed;
	if (dir1 != DIR_NONE || dir2 != DIR_NONE)
	{
		if (dir1 == DIR_UP)
		{
			Pic1.m_vSpeed += D3DXVECTOR3(0, -TempSpeed, 0);
		}
		else if (dir1 == DIR_DOWN)
		{
			Pic1.m_vSpeed += D3DXVECTOR3(0, +TempSpeed, 0);
		}
		if (dir2 == DIR_LEFT)
		{
			Pic1.m_vSpeed += D3DXVECTOR3(-TempSpeed, 0, 0);
		}
		else if (dir2 == DIR_RIGHT)
		{
			Pic1.m_vSpeed += D3DXVECTOR3(+TempSpeed, 0, 0);
		}
	}
	
	D3DXVec3Normalize(&Pic1.m_vSpeed, &Pic1.m_vSpeed);
	Pic1.m_vSpeed *= Pic1.m_Speed;
	Pic1.m_Pos += Pic1.m_vSpeed;
}

void CPlayer::ImgChange()
{
	if (dir1 != DIR_NONE || dir2 != DIR_NONE)
	{
		Pic1.m_imgX += Pic1.m_Width ;
		if (Pic1.m_imgX >= Pic1.m_Width*Pic1.m_xnum)
		{
			Pic1.m_imgX = 0;
		}
	}
	if (dir1 == DIR_UP)
	{ 		
		Pic1.m_imgY = Pic1.m_Height * 3;
	}
	else if (dir1 == DIR_DOWN)
	{
		Pic1.m_imgY = Pic1.m_Height  * 0;
	}
	if (dir2 == DIR_LEFT) 
	{ 
		Pic1.m_imgY = Pic1.m_Height;
	}
	else if(dir2 == DIR_RIGHT) 
	{ 
		Pic1.m_imgY = Pic1.m_Height * 2;
	}

	if (dir1 == DIR_UP&&dir2 == DIR_LEFT)
	{
		Pic1.m_imgY = Pic1.m_Height * 6;
	}
	else if (dir1 == DIR_UP && dir2 == DIR_RIGHT)
	{
		Pic1.m_imgY = Pic1.m_Height  * 7;
	}
	if (dir1 == DIR_DOWN && dir2 == DIR_LEFT)
	{
		Pic1.m_imgY = Pic1.m_Height * 4;
	}
	else if (dir1 == DIR_DOWN && dir2==DIR_RIGHT)
	{
		Pic1.m_imgY = Pic1.m_Height * 5;
	}
}

void CPlayer::TowerPlayerLogic()
{
	int tempSpeed = Pic1.m_Speed;
	if ((int)Pic1.m_Pos.x == 0 && (int)Pic1.m_Pos.y == 390)
	{
		dir2 = DIR_RIGHT; dir1 = DIR_NONE;
		Pic1.m_vSpeed = D3DXVECTOR3(+tempSpeed, 0, 0);
	}
	else if (Pic1.m_Pos.x > 238 && Pic1.m_Pos.x < 242 && Pic1.m_Pos.y > 388 && Pic1.m_Pos.y < 392)
	{
		dir1 = DIR_UP; dir2 = DIR_NONE;
		Pic1.m_vSpeed = D3DXVECTOR3(0, -tempSpeed, 0);
	}
	else if (Pic1.m_Pos.x > 238 && Pic1.m_Pos.x < 242 && Pic1.m_Pos.y > 108 && Pic1.m_Pos.y < 112)
	{
		dir2 = DIR_RIGHT; dir1 = DIR_NONE;
		Pic1.m_vSpeed = D3DXVECTOR3(+tempSpeed, 0, 0);
	}
	else if (Pic1.m_Pos.x > 768 && Pic1.m_Pos.x < 772 && Pic1.m_Pos.y > 108 && Pic1.m_Pos.y < 112)
	{
		dir1 = DIR_DOWN; dir2 = DIR_NONE;
		Pic1.m_vSpeed = D3DXVECTOR3(0, +tempSpeed, 0);
	}
	else if (Pic1.m_Pos.x > 768 && Pic1.m_Pos.x < 772 && Pic1.m_Pos.y > 388 && Pic1.m_Pos.y < 392)
	{
		dir2 = DIR_RIGHT; dir1 = DIR_NONE;
		Pic1.m_vSpeed = D3DXVECTOR3(+tempSpeed, 0, 0);
	}
	else if (Pic1.m_Pos.x > 938 && Pic1.m_Pos.x < 942 && Pic1.m_Pos.y > 388 && Pic1.m_Pos.y < 392)
	{
		dir1 = DIR_NONE;
		dir2 = DIR_NONE;
		Pic1.m_vSpeed = D3DXVECTOR3(0, 0, 0);
	}
	D3DXVec3Normalize(&Pic1.m_vSpeed, &Pic1.m_vSpeed);
	Pic1.m_vSpeed *= Pic1.m_Speed;
	Pic1.m_Pos += Pic1.m_vSpeed;
}

void CPlayer::TowerImgChangeLogic()
{
	if (dir1 != DIR_NONE || dir2 != DIR_NONE)
	{
		Pic1.m_imgX += Pic1.m_Width;
		if (Pic1.m_imgX >= Pic1.m_Width*Pic1.m_xnum)
		{
			Pic1.m_imgX = 0;
		}
	}
	if (dir1 == DIR_UP)
	{
		Pic1.m_imgY = Pic1.m_Height * 3;
	}
	if (dir1 == DIR_DOWN)
	{
		Pic1.m_imgY = Pic1.m_Height * 4;
	}
	if (dir2 == DIR_LEFT)
	{
		Pic1.m_imgY = Pic1.m_Height  * 1;
	}
	if (dir2 == DIR_RIGHT)
	{
		Pic1.m_imgY = Pic1.m_Height  * 8;
	}
}

void CPlayer::Upde()
{
	TowerPlayerLogic();	
	TowerImgChangeLogic();
	Sleep(30);
}
