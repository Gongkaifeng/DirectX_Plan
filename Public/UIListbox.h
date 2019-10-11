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
	
	//初始化
	VOID Init(int x,int y,HDC& hdc,char* strImage);

	//渲染
	VOID Draw();
	
	//在列表框中增加一个新项目
	VOID AddIteam(char* strIteam);

	//向上翻页
	VOID PageUp();
	
	//向下翻页
	VOID PageDown();

	//移动最后一个显示项
	VOID MoveToEndIteam();

protected:

	//复制需要显示的项
	VOID CopyShowIteam();

	CUIPicture	m_Imgbasic;			//图形
	std::string m_Input[MaxIteam];	//总数据表
	CUIText		m_Text[MaxShow];	//最大显示条数内容
	int			m_nListIteamIndex;	//当前显示起始位置
	int			m_nMaxCount;		//当前数据最大值
};
