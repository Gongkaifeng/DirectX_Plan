//场景上所有的和图形渲染相关的对象的基类
//包括摄像机,灯光,渲染的静态,动态物体
#pragma once

class CObject
{
public:
	//构造函数
	CObject();
	//析构函数
	virtual ~CObject();
	virtual void Draw() {}
	//控件的隐藏
	VOID Hide() { m_hide = true; }

	//控件的显示
	VOID Show() { m_hide = false; }

	//控件消息分发
	virtual VOID WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {}
	//获得对象的位置(子类可重新实现)
	virtual D3DXVECTOR3 GetPos();
	
protected:
	D3DXVECTOR3 m_vPos;
	D3DXMATRIX m_Omat;
	float ScaleX;
	float ScaleY;
protected:
	INT nX;
	INT nY;
	bool m_hide;
};
