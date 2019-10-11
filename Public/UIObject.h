#pragma once

class CUIObject
{
public:
	CUIObject();
	virtual ~CUIObject();
	virtual VOID Draw(){}
	//控件的隐藏
	VOID Hide() { m_hide = true; }
	
	//控件的显示
	VOID Show() { m_hide = false; }

	//控件消息分发
	virtual VOID WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ){}
	// 获得对象的位置（子类可重新实现）
	virtual D3DXVECTOR3 GetPos();

protected:
	D3DXVECTOR3     m_vPos;
	D3DXVECTOR3     m_Omat;
	float		    ScaleX;
	float		    ScaleY;
protected:
	INT				nX;
	INT				nY;
	bool			m_hide;
};
