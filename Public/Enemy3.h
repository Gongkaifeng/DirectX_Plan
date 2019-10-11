#pragma once

class CEnemy3 :
	public CSprite
{
public:
	CEnemy3();
	~CEnemy3();
	CEnemy3(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect);

public:
	void	Update();
	void	Render();
	void	Enemy3Move();
	void	Enemy3Fire();
	bool	IsHit();
	void	Boom();
	void	GetRc();				//获取敌机实时矩形框（碰撞检测用）

public:
	D3DXVECTOR3		m_vSpeed2;
	D3DXVECTOR3		m_vSpeed3;
	DWORD			preTime;
	eEnemyState		m_eState3;
	bool			m_bBoom;
	bool			m_bDead;
	int				m_curFrame;
	DWORD			m_PreTime;
	RECT			rc_enemy3;
	int				m_hp_enemy3;
	DWORD			preTime_star;	// 敌机碰撞状态下计时（处理爆炸图片显示时间）
};

