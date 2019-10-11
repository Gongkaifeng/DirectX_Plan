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

	TSTRING		 Name;						 // 动画名称
	int			 Frame;						 // 帧数
	int			 m_curFrame;				 // 当前播放帧
	float		 m_fTime;					 // 每帧播放时间
	static DWORD m_PreTime;
	bool		 m_bIsplaying;				 // 是否正在播放
	bool		 m_bLoop;					 // 是否循环播放
	vector<CAnimationFrame*> FrameList;      // 帧列表
};

