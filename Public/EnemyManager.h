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
	int				m_number_enemy3 = 0;			// 敌机3数量
	list<CEnemy*>	enemylist;						// 敌机链
	list<CEnemy2*>	enemylist2;						// 敌机2链
	list<CEnemy3*>	enemylist3;						// 敌机3链

	static CEnemyManager*	m_pEnemyInstance;		// 敌机管理单例
};

