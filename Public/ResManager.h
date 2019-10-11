#pragma once
class CResManager//:public CSingleton<CResManager>	 //继承单例
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
	//void LoadPicture(TSTRING);									    // 导入图片，同时生成帧信息
	//void LoadAnimation(TSTRING);								        // 导入动画播放方式

	void AddPicture(TSTRING name, CPicture* pic);						// 添加图片
	CPicture* GetPicture(TSTRING name);									// 获取图片属性

	void AddAnimation(TSTRING animationName, CAnimation* animation);	// 添加动画
	CAnimation* GetAnimation(TSTRING animationName);					// 获取动画属性

	void AddAnimationFrame(TSTRING, CAnimationFrame*);					// 添加帧
	CAnimationFrame* GetAnimationFrame(TSTRING animationName);			// 获取帧属性

public:
	map<TSTRING, CPicture*>			picture;							// 存储图片
	map<TSTRING, CAnimationFrame*>  frame;								// 存储动画帧
	map<TSTRING, CAnimation*>		animation;							// 存储动画

	static CResManager*				m_pResInstance;						// 单例

};

