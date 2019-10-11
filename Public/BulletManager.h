#pragma once
class CBulletManager:public CBullet
{
public:
	CBulletManager();
	~CBulletManager();
	static CBulletManager* GetBulletInstance()
	{
		if (!m_pBulletInstance)
			m_pBulletInstance = new CBulletManager;
		return m_pBulletInstance;
	}
	void Update();
	void Render();

public:
	static CBulletManager*	m_pBulletInstance;		// 子弹管理单例

	list<CMyplayBullet*>	Mybulletlist;			// 我机子弹链（普通）	
	list<CMyplayBullet2*>   Mybulletlist2;			// 我机子弹链2(跟踪导弹)
	list<CMyplayBullet4*>	Mybulletlist4;			// 我机大招子弹（全屏爆破）

	list<CEnemyBullet*>		Enbulletlist;			// 敌机子弹链（普通)
	list<CEnemyBullet2*>	Enbulletlist2;			// 敌机2子弹链
	list<CEnemyBullet3*>	Enbulletlist3;			// 敌机3子弹链

	bool Ishit;	
};
