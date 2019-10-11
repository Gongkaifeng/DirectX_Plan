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
	static CBulletManager*	m_pBulletInstance;		// �ӵ�������

	list<CMyplayBullet*>	Mybulletlist;			// �һ��ӵ�������ͨ��	
	list<CMyplayBullet2*>   Mybulletlist2;			// �һ��ӵ���2(���ٵ���)
	list<CMyplayBullet4*>	Mybulletlist4;			// �һ������ӵ���ȫ�����ƣ�

	list<CEnemyBullet*>		Enbulletlist;			// �л��ӵ�������ͨ)
	list<CEnemyBullet2*>	Enbulletlist2;			// �л�2�ӵ���
	list<CEnemyBullet3*>	Enbulletlist3;			// �л�3�ӵ���

	bool Ishit;	
};
