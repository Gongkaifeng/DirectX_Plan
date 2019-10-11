#pragma once
#include "Picture.h"
class CPlayer
{
public:
	CPlayer();
	~CPlayer();

public:
	void Init(RECT _clientRC, TSTRING _Name, TSTRING _Path, IDirect3DDevice9* _g_pDevice, DWORD _xnum, DWORD _ynum, int _Speed, float _Rote);
	void PlayerMove();
	void ImgChange();
	void TowerPlayerLogic();
	void TowerImgChangeLogic();
	void Upde();
	//D3DXVECTOR3 Getplayer_midpoint();		//牛头图片中心
	//void Setplayer_midpoint(D3DXVECTOR3 tempvector3);

	int dir1;								//上下
	int dir2;								//左右
	RECT m_clientRC;
	CPicture Pic1;
	//D3DXVECTOR3 Player_midpoint;
};

