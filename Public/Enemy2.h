#pragma once

class CEnemy2 :public CSprite
{
public:
	CEnemy2();
	~CEnemy2();
	CEnemy2(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect);

public:
	void	Update();
	void	Render();
	void	Enemy2Move();
	void	Enemy2Fire();
	bool	IsHit();
	void	Boom();
	void	GetRc();				//��ȡ�л�ʵʱ���ο���ײ����ã�

public:
	D3DXVECTOR3		m_vSpeed2;
	D3DXVECTOR3		m_vSpeed3;
	DWORD			preTime;
	eEnemyState		m_eState2;
	bool			m_bBoom;
	bool			m_bDead;
	int				m_curFrame;
	DWORD			m_PreTime;
	RECT			rc_enemy2;
	int				m_hp_enemy2;
	DWORD			preTime_star;	// �л���ײ״̬�¼�ʱ������ըͼƬ��ʾʱ�䣩
};

