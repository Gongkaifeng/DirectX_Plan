#pragma once

class CUIManager:public CSingleton<CUIManager>		// 继承单例
{
public:
	CUIManager(void);
	~CUIManager(void);
		
	void AddNew(CUIObject*);						// 在管理器内注册一个新的控件													
	void Draw();									// 调用注册过的控件的绘制												
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);	// 接受外界的消息响应，分发给各个注册过的控件
	//static CUIManager& GetManager();				// 返回管理器	

protected:
	list<CUIObject*>  m_UIList;						// 控件存储表

};
