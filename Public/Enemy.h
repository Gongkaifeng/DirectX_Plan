#pragma once

class CEnemy :public CSprite
{
public:
	CEnemy();
	~CEnemy();
	CEnemy(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect);

public:
	void	Update();
	void	Render();
	void	EnemyMove();
	void	EnemyFire();
	bool	IsHit();
	void	Boom();
	void	GetRc();			//��ȡ�л�ʵʱ���ο���ײ����ã�

public: 
	D3DXVECTOR3		m_vSpeed2;
	D3DXVECTOR3		m_vSpeed3;
	DWORD			preTime;
	eEnemyState		m_eState;
	bool			m_bBoom;
	bool			m_bDead;
	int				m_curFrame;
	DWORD			m_PreTime;
	RECT			rc_enemy;
	int				m_hp_enemy;
	DWORD			preTime_star;	// �л���ײ״̬�¼�ʱ������ըͼƬ��ʾʱ�䣩
};

