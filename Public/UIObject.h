#pragma once

class CUIObject
{
public:
	CUIObject();
	virtual ~CUIObject();
	virtual VOID Draw(){}
	//�ؼ�������
	VOID Hide() { m_hide = true; }
	
	//�ؼ�����ʾ
	VOID Show() { m_hide = false; }

	//�ؼ���Ϣ�ַ�
	virtual VOID WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ){}
	// ��ö����λ�ã����������ʵ�֣�
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
