//——————————图片类——————————
//		处理UI控件图片
//
//_________________________________________________
#pragma once
class CUIPicture
{
public:
	CUIPicture(void);
	~CUIPicture(void);

	//初始化
	VOID Init(int x, int y, HDC& hdc, char * strName);

	//绘制函数
	VOID Draw();

	//隐藏控件
	VOID Hide();

	//显示控件
	VOID Show();
	VOID SetImagePos(int x,int y);
	int GetXPos(){return nX;}
	int GetYPos(){return nY;}
	//返回图片的长宽
	int GetWidth();
	int GetHeight();
protected:

	HBITMAP m_Img;	
	BITMAP	m_bmp;
	HDC		m_Hdc;		//兼容HDC
	HDC*	m_hdc;		//获取外部HDC
	bool	m_hide;
	int     nX;
	int		nY;
};
