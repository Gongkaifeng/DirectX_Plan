#pragma once

class CAnimation
{
public:
	CAnimation(TSTRING _Name, int _Frame);
	~CAnimation();

	void PlayAnimation();
	void Update();
	CAnimationFrame* GetCurFrame()
	{
		return FrameList.at(m_curFrame);
	}

	TSTRING		 Name;						 // ��������
	int			 Frame;						 // ֡��
	int			 m_curFrame;				 // ��ǰ����֡
	float		 m_fTime;					 // ÿ֡����ʱ��
	static DWORD m_PreTime;
	bool		 m_bIsplaying;				 // �Ƿ����ڲ���
	bool		 m_bLoop;					 // �Ƿ�ѭ������
	vector<CAnimationFrame*> FrameList;      // ֡�б�
};

