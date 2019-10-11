#pragma once
class CResManager//:public CSingleton<CResManager>	 //�̳е���
{
public:
	CResManager();
	~CResManager();
	static CResManager* GetResInstance()
	{
		if (!m_pResInstance)
			m_pResInstance = new CResManager;
		return m_pResInstance;
	}

	void LoadPictureInit();
	void LoadAnimationFrameInit();
	void LoadAnimationInit();
	void Update();
	void Render();
	//void LoadPicture(TSTRING);									    // ����ͼƬ��ͬʱ����֡��Ϣ
	//void LoadAnimation(TSTRING);								        // ���붯�����ŷ�ʽ

	void AddPicture(TSTRING name, CPicture* pic);						// ���ͼƬ
	CPicture* GetPicture(TSTRING name);									// ��ȡͼƬ����

	void AddAnimation(TSTRING animationName, CAnimation* animation);	// ��Ӷ���
	CAnimation* GetAnimation(TSTRING animationName);					// ��ȡ��������

	void AddAnimationFrame(TSTRING, CAnimationFrame*);					// ���֡
	CAnimationFrame* GetAnimationFrame(TSTRING animationName);			// ��ȡ֡����

public:
	map<TSTRING, CPicture*>			picture;							// �洢ͼƬ
	map<TSTRING, CAnimationFrame*>  frame;								// �洢����֡
	map<TSTRING, CAnimation*>		animation;							// �洢����

	static CResManager*				m_pResInstance;						// ����

};

