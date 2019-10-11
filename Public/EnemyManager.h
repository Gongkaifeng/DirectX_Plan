#pragma once

class CEnemyManager
{
public:
	CEnemyManager();
	~CEnemyManager();
	static CEnemyManager*   GetEnemyInstance()
	{
		if (!m_pEnemyInstance)
			m_pEnemyInstance = new CEnemyManager;
		return m_pEnemyInstance;
	}
	void			Update();
	void			Render();
	void			CreateEnemy(); 
	void			CreateEnemy2();
	void			CreateEnemy3();

public:
	int				m_number_enemy3 = 0;			// �л�3����
	list<CEnemy*>	enemylist;						// �л���
	list<CEnemy2*>	enemylist2;						// �л�2��
	list<CEnemy3*>	enemylist3;						// �л�3��

	static CEnemyManager*	m_pEnemyInstance;		// �л�������
};

