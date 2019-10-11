#pragma once

class CMyplayer :public CSprite
{
public:
	CMyplayer();
	~CMyplayer();

public:
	void	Init(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect);
	void	Update();
	void	Render();
	void	PlayerMove();
	void	PlayerFire();
	bool	IsHit();
	void	GetRc();
	void	MyBoom();

public:
	int		dir1;
	int		dir2;
	int		style_fire;	
	int		m_hp_myplayer;		// �һ�Ѫ��
	int		pel;				// �һ�͸����ֵ
	RECT	rc_myplayer;		// �һ���ײRC
	DWORD	m_preTime;			

	eMyplayState  m_mState;		// �һ�״̬��

};

