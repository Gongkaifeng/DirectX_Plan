//��������������������ͼƬ�ࡪ������������������
//		����UI�ؼ�ͼƬ
//
//_________________________________________________
#pragma once
class CUIPicture
{
public:
	CUIPicture(void);
	~CUIPicture(void);

	//��ʼ��
	VOID Init(int x, int y, HDC& hdc, char * strName);

	//���ƺ���
	VOID Draw();

	//���ؿؼ�
	VOID Hide();

	//��ʾ�ؼ�
	VOID Show();
	VOID SetImagePos(int x,int y);
	int GetXPos(){return nX;}
	int GetYPos(){return nY;}
	//����ͼƬ�ĳ���
	int GetWidth();
	int GetHeight();
protected:

	HBITMAP m_Img;	
	BITMAP	m_bmp;
	HDC		m_Hdc;		//����HDC
	HDC*	m_hdc;		//��ȡ�ⲿHDC
	bool	m_hide;
	int     nX;
	int		nY;
};
