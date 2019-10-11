#pragma once
#include "UIObject.h"
#include "UIImage.h"
#include"UIText.h"
#include <string>

#define MaxIteam 40
#define MaxShow  8
class CUIListbox :
	public CUIObject
{
public:
	CUIListbox(void);
	~CUIListbox(void);
	
	//��ʼ��
	VOID Init(int x,int y,HDC& hdc,char* strImage);

	//��Ⱦ
	VOID Draw();
	
	//���б��������һ������Ŀ
	VOID AddIteam(char* strIteam);

	//���Ϸ�ҳ
	VOID PageUp();
	
	//���·�ҳ
	VOID PageDown();

	//�ƶ����һ����ʾ��
	VOID MoveToEndIteam();

protected:

	//������Ҫ��ʾ����
	VOID CopyShowIteam();

	CUIPicture	m_Imgbasic;			//ͼ��
	std::string m_Input[MaxIteam];	//�����ݱ�
	CUIText		m_Text[MaxShow];	//�����ʾ��������
	int			m_nListIteamIndex;	//��ǰ��ʾ��ʼλ��
	int			m_nMaxCount;		//��ǰ�������ֵ
};
