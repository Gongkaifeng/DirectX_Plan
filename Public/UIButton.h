#pragma once

class CUIButton: public CUIObject
{
public:
	CUIButton(void);
	~CUIButton(void);
	VOID Init(int x, int y, IDirect3DDevice9* g_pDevice,TSTRING strBasic, TSTRING strMouseOver, TSTRING strMouseUp);

	//按钮消息处理
	VOID WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//绘制
	VOID Draw();
	BOOL InHot();					// 判断是否点击在控件内
	//按钮响应
	bool IsButtonDown();

protected:
	LPD3DXSPRITE	m_pSprite;		// 图片精灵

	CPictureBasic*	m_Imgbasic;		// 控件默认图片
	CPictureBasic*	m_ImgMouseOver;	// 鼠标悬浮图片
	CPictureBasic*	m_ImgMouseUp;	// 鼠标点击图片
	CPictureBasic*	m_Img;			// 当前显示图片
	POINT			m_Point;	    // 鼠标位置点
	bool			m_bButtonDown;  // 鼠标点击标志
};
