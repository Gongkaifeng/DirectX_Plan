#pragma once

class CUIManager:public CSingleton<CUIManager>		// �̳е���
{
public:
	CUIManager(void);
	~CUIManager(void);
		
	void AddNew(CUIObject*);						// �ڹ�������ע��һ���µĿؼ�													
	void Draw();									// ����ע����Ŀؼ��Ļ���												
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);	// ����������Ϣ��Ӧ���ַ�������ע����Ŀؼ�
	//static CUIManager& GetManager();				// ���ع�����	

protected:
	list<CUIObject*>  m_UIList;						// �ؼ��洢��

};
