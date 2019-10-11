#pragma once

class CUIButton: public CUIObject
{
public:
	CUIButton(void);
	~CUIButton(void);
	VOID Init(int x, int y, IDirect3DDevice9* g_pDevice,TSTRING strBasic, TSTRING strMouseOver, TSTRING strMouseUp);

	//��ť��Ϣ����
	VOID WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//����
	VOID Draw();
	BOOL InHot();					// �ж��Ƿ����ڿؼ���
	//��ť��Ӧ
	bool IsButtonDown();

protected:
	LPD3DXSPRITE	m_pSprite;		// ͼƬ����

	CPictureBasic*	m_Imgbasic;		// �ؼ�Ĭ��ͼƬ
	CPictureBasic*	m_ImgMouseOver;	// �������ͼƬ
	CPictureBasic*	m_ImgMouseUp;	// �����ͼƬ
	CPictureBasic*	m_Img;			// ��ǰ��ʾͼƬ
	POINT			m_Point;	    // ���λ�õ�
	bool			m_bButtonDown;  // �������־
};
