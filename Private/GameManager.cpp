#pragma once
#include "stdafx.h"
CGameManager* CGameManager::m_pGameInstance = nullptr;
CGameManager::CGameManager()
{
}
CGameManager::~CGameManager()
{
	// 释放map容器
	map<TSTRING, CPictureBasic*>::iterator it1 = pic.begin();
	for (; it1 != pic.end(); it1++)
	{
		delete it1->second;
	}
	pic.clear();
	// 释放接口、设备
	if (Direct3D)
		Direct3D->Release();
	if (D3DDevice)
		D3DDevice->Release();
	if (CGameManager::GetGameInstance())
		delete CGameManager::GetGameInstance();
	if (CEnemyManager::GetEnemyInstance())
		delete CEnemyManager::GetEnemyInstance();
	if (CBulletManager::GetBulletInstance())
		delete CBulletManager::GetBulletInstance();
}

void CGameManager::InitD3D(HWND hWnd)
{
	Direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	//GetClientRect(hWnd, &g_clientRC);
	D3DPRESENT_PARAMETERS d3dpp;												          // 定义双缓冲的后台参数
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;									          // 后台缓冲的像素格式，32真彩色
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;									          // 交换模式，设置后台缓冲和前台缓冲之间的交换模式
	d3dpp.Windowed = true;														          // 是否窗口显示，false为全屏
	Direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &D3DDevice);
	
	// D3DXCreateLine(D3DDevice, &g_pLine); //画线部分，暂没用

	// 打字部分
	D3DXFONT_DESC df;
	ZeroMemory(&df, sizeof(D3DXFONT_DESC));
	df.Height = 25;
	df.Width = 15;
	df.MipLevels = D3DX_DEFAULT;
	df.Italic = false;
	df.CharSet = OEM_CHARSET;//DEFAULT_CHARSET;
	df.OutputPrecision = 0;
	df.Quality = 0;
	df.PitchAndFamily = 0;
	wcscpy_s(df.FaceName, _T("TIME NEW ROMAN"));
	D3DXCreateFontIndirect(D3DDevice, &df, &Font);
}

void CGameManager::Init()
{
	srand(time(0));
	m_GState = Scene_begin;

	num_small		= 0;
	num_middle		= 0;
	num_large		= 0;
	num_level		= 1;
	cur_frame		= 1;
	flag_shuoming	= false;
	flag_story		= true;
	//m_GState = Scene_game;

	// 加载开始界面背景图片
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("backpic_begin"), new CPictureBasic));
	pic[_T("backpic_begin")]->Init(_T("backpic_begin.bmp"), _T("..bin/backpic_begin.bmp"));
	RECT rect_backpic_begin = { 0,0, pic[_T("backpic_begin")]->GetWidth(), pic[_T("backpic_begin")]->GetHeight() };
	D3DXVECTOR3 m_pos_backpic_begin = { 300, 450 ,0 };
	D3DXVECTOR3 center_backpic_begin = { (float)pic[_T("backpic_begin")]->GetWidth() / 2, (float)pic[_T("backpic_begin")]->GetHeight() / 2 ,0 };
	backpic_begin.Init(pic[_T("backpic_begin")]->GetTexture(), m_pos_backpic_begin, center_backpic_begin, rect_backpic_begin);

	// 加载开始界面记分背景
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("map2"), new CPictureBasic));
	pic[_T("map2")]->Init(_T("map2.bmp"), _T("..bin/map2.bmp"));
	RECT rect_backpic_score = { 0,0, pic[_T("map2")]->GetWidth(), pic[_T("map2")]->GetHeight() };
	D3DXVECTOR3 m_pos_backpic_score = { 750, 450 ,0 };
	D3DXVECTOR3 center_backpic_score = { (float)pic[_T("map2")]->GetWidth() / 2, (float)pic[_T("map2")]->GetHeight() / 2 ,0 };
	score_bj.Init(pic[_T("map2")]->GetTexture(), m_pos_backpic_score, center_backpic_score, rect_backpic_score);

	// 加载开始界面Logo
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("Logo"), new CPictureBasic));
	pic[_T("Logo")]->Init(_T("Logo.bmp"), _T("..bin/Logo.bmp"));
	RECT rect_backpic_logo = { 0,0, pic[_T("Logo")]->GetWidth(), pic[_T("Logo")]->GetHeight() };
	D3DXVECTOR3 m_pos_backpic_logo = { 750, 60 ,0 };
	D3DXVECTOR3 center_backpic_logo = { (float)pic[_T("Logo")]->GetWidth() / 2, (float)pic[_T("Logo")]->GetHeight() / 2 ,0 };
	Logo.Init(pic[_T("Logo")]->GetTexture(), m_pos_backpic_logo, center_backpic_logo, rect_backpic_logo);

	// 加载前述动画帧图片01
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("story01"), new CPictureBasic));
	pic[_T("story01")]->Init(_T("story01.bmp"), _T("..bin/story01.bmp"));
	RECT rect_backpic_story01 = { 0,0, pic[_T("story01")]->GetWidth(), pic[_T("story01")]->GetHeight() };
	D3DXVECTOR3 m_pos_backpic_story01 = { 750, 450 ,0 };
	D3DXVECTOR3 center_backpic_story01 = { (float)pic[_T("story01")]->GetWidth() / 2, (float)pic[_T("story01")]->GetHeight() / 2 ,0 };
	story01.Init(pic[_T("story01")]->GetTexture(), m_pos_backpic_story01, center_backpic_story01, rect_backpic_story01);
	// 加载前述动画帧图片02
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("story02"), new CPictureBasic));
	pic[_T("story02")]->Init(_T("story02.bmp"), _T("..bin/story02.bmp"));
	RECT rect_backpic_story02 = { 0,0, pic[_T("story02")]->GetWidth(), pic[_T("story02")]->GetHeight() };
	D3DXVECTOR3 m_pos_backpic_story02 = { 750, 450 ,0 };
	D3DXVECTOR3 center_backpic_story02 = { (float)pic[_T("story02")]->GetWidth() / 2, (float)pic[_T("story02")]->GetHeight() / 2 ,0 };
	story02.Init(pic[_T("story02")]->GetTexture(), m_pos_backpic_story02, center_backpic_story02, rect_backpic_story02);

	// 加载GameWin
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("gamewin"), new CPictureBasic));
	pic[_T("gamewin")]->Init(_T("gamewin.bmp"), _T("..bin/gamewin.bmp"));
	RECT rect_gamewin = { 0,0, pic[_T("gamewin")]->GetWidth(), pic[_T("gamewin")]->GetHeight() };
	D3DXVECTOR3 m_pos_gamewin = { 300, 400 ,0 };
	D3DXVECTOR3 center_gamewin = { (float)pic[_T("gamewin")]->GetWidth() / 2, (float)pic[_T("gamewin")]->GetHeight() / 2 ,0 };
	gamewin.Init(pic[_T("gamewin")]->GetTexture(), m_pos_gamewin, center_gamewin, rect_gamewin);

	// 加载GameOver
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("gameover"), new CPictureBasic));
	pic[_T("gameover")]->Init(_T("gameover.bmp"), _T("..bin/gameover.bmp"));
	RECT rect_gameover = { 0,0, pic[_T("gameover")]->GetWidth(), pic[_T("gameover")]->GetHeight() };
	D3DXVECTOR3 m_pos_gameover = { 300, 400 ,0 };
	D3DXVECTOR3 center_gameover = { (float)pic[_T("gameover")]->GetWidth() / 2, (float)pic[_T("gameover")]->GetHeight() / 2 ,0 };
	gameover.Init(pic[_T("gameover")]->GetTexture(), m_pos_gameover, center_gameover, rect_gameover);


	// 加载开始界面操作说明
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("OI"), new CPictureBasic));
	pic[_T("OI")]->Init(_T("OI.bmp"), _T("..bin/OI.bmp"));
	RECT rect_backpic_OI = { 0,0, pic[_T("OI")]->GetWidth(), pic[_T("OI")]->GetHeight() };
	D3DXVECTOR3 m_pos_backpic_OI = { 730, 620 ,0 };
	D3DXVECTOR3 center_backpic_OI = { (float)pic[_T("OI")]->GetWidth() / 2, (float)pic[_T("OI")]->GetHeight() / 2 ,0 };
	OI.Init(pic[_T("OI")]->GetTexture(), m_pos_backpic_OI, center_backpic_OI, rect_backpic_OI);


	// 加载开始界面开始按钮图片
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("begin_basic"), new CPictureBasic));
	pic[_T("begin_basic")]->Init(_T("begin_basic.bmp"), _T("..bin/begin_basic.bmp"));
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("begin_mouseover"), new CPictureBasic));
	pic[_T("begin_mouseover")]->Init(_T("begin_mouseover.bmp"), _T("..bin/begin_mouseover.bmp"));
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("begin_mouseup"), new CPictureBasic));
	pic[_T("begin_mouseup")]->Init(_T("begin_mouseup.bmp"), _T("..bin/begin_mouseup.bmp"));
	// 加载开始界面结束按钮图片
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("outgame_basic"), new CPictureBasic));
	pic[_T("outgame_basic")]->Init(_T("outgame_basic.bmp"), _T("..bin/outgame_basic.bmp"));
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("outgame_mouseover"), new CPictureBasic));
	pic[_T("outgame_mouseover")]->Init(_T("outgame_mouseover.bmp"), _T("..bin/outgame_mouseover.bmp"));
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("outgame_mouseup"), new CPictureBasic));
	pic[_T("outgame_mouseup")]->Init(_T("outgame_mouseup.bmp"), _T("..bin/outgame_mouseup.bmp"));
	// 加载开始界面说明按钮图片
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("shuoming_basic"), new CPictureBasic));
	pic[_T("shuoming_basic")]->Init(_T("shuoming_basic.bmp"), _T("..bin/shuoming_basic.bmp"));
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("shuoming_mouseover"), new CPictureBasic));
	pic[_T("shuoming_mouseover")]->Init(_T("shuoming_mouseover.bmp"), _T("..bin/shuoming_mouseover.bmp"));
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("shuoming_mouseup"), new CPictureBasic));
	pic[_T("shuoming_mouseup")]->Init(_T("shuoming_mouseup.bmp"), _T("..bin/shuoming_mouseup.bmp"));


	// 初始化开始按钮
	button_begin.Init(100,400, D3DDevice, _T("begin_basic"), _T("begin_mouseover"), _T("begin_mouseup"));
	// 初始化结束按钮
	button_over.Init(100, 600, D3DDevice, _T("outgame_basic"), _T("outgame_mouseover"), _T("outgame_mouseup"));
	// 初始化说明按钮
	button_shuoming.Init(100, 500, D3DDevice, _T("shuoming_basic"), _T("shuoming_mouseover"), _T("shuoming_mouseup"));


	//加载背景图1(600x2700)
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("map"),new CPictureBasic ));	// 加载背景
	pic[_T("map")]->Init(_T("map.bmp"), _T("..bin/map.bmp"));
	RECT rect1 = { 0,0, 600, 2700 };
	D3DXVECTOR3 m_pos1 = { 300, 450 ,0 };
	D3DXVECTOR3 center1 = { 300, 2250 ,0 };
	backpic_Sprite.Init(pic[_T("map")]->GetTexture(), m_pos1, center1, rect1);
	
	//加载战机01(200x200)
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("player01"), new CPictureBasic));	// 加载背景
	pic[_T("player01")]->Init(_T("player01.bmp"), _T("..bin/player01.bmp"));
	RECT rect2 = { 0,0, pic[_T("player01")]->GetWidth(), pic[_T("player01")]->GetHeight() };
	D3DXVECTOR3 m_pos2 = { 300, 750 ,0 };
	D3DXVECTOR3 center2 = { (float)pic[_T("player01")]->GetWidth() / 2, (float)pic[_T("player01")]->GetHeight() / 2 ,0 };
	player01_Sprite.Init(pic[_T("player01")]->GetTexture(), m_pos2, center2, rect2);

	//加载战机02(200x200)
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("player02"), new CPictureBasic));	// 加载背景
	pic[_T("player02")]->Init(_T("player02.bmp"), _T("..bin/player02.bmp"));
	RECT rect3 = { 0,0, pic[_T("player02")]->GetWidth(), pic[_T("player02")]->GetHeight() };
	D3DXVECTOR3 m_pos3 = { 300, 750 ,0 };
	D3DXVECTOR3 center3 = { (float)pic[_T("player02")]->GetWidth() / 2, (float)pic[_T("player02")]->GetHeight() / 2 ,0 };
	player01_Sprite.Init(pic[_T("player02")]->GetTexture(), m_pos3, center3, rect3);

	//加载战机03(200x200):我机大招用
	RECT rect_skill = { 0,0, pic[_T("player01")]->GetWidth(), pic[_T("player01")]->GetHeight() };
	D3DXVECTOR3 m_pos_skill = { 300,900 ,0 };
	D3DXVECTOR3 center_skill = { (float)pic[_T("player01")]->GetWidth() / 2, (float)pic[_T("player01")]->GetHeight() / 2 ,0 };
	skill_Sprite.Init(pic[_T("player01")]->GetTexture(), m_pos_skill, center_skill, rect_skill);


	// 加载战机血条后
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("hp_back"), new CPictureBasic));	// 加载背景
	pic[_T("hp_back")]->Init(_T("hp_back.bmp"), _T("..bin/hp_back.bmp"));
	RECT rect4 = { 0,0, pic[_T("hp_back")]->GetWidth(), pic[_T("hp_back")]->GetHeight() };
	D3DXVECTOR3 m_pos4 = { (float)CGameManager::GetGameInstance()->player01_Sprite.m_Pos.x - pic[_T("hp_back")]->GetWidth() / 2, (float)CGameManager::GetGameInstance()->player01_Sprite.m_Pos.y - pic[_T("hp_back")]->GetHeight() / 2 ,0 };
	D3DXVECTOR3 center4 = { 0, 0 ,0 };
	hp_back.Init(pic[_T("hp_back")]->GetTexture(), m_pos4, center4, rect4);

	// 加载战机血条前
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("hp_front"), new CPictureBasic));	// 加载背景
	pic[_T("hp_front")]->Init(_T("hp_front.bmp"), _T("..bin/hp_front.bmp"));
	RECT rect5 = { 0,0, pic[_T("hp_front")]->GetWidth(), pic[_T("hp_front")]->GetHeight() };
	D3DXVECTOR3 m_pos5 = { (float)CGameManager::GetGameInstance()->player01_Sprite.m_Pos.x - pic[_T("hp_front")]->GetWidth() / 2, (float)CGameManager::GetGameInstance()->player01_Sprite.m_Pos.y - pic[_T("hp_front")]->GetHeight() / 2 ,0 };
	D3DXVECTOR3 center5 = { 0, 0 ,0 };
	hp_front.Init(pic[_T("hp_front")]->GetTexture(), m_pos5, center5, rect5);

	//加载战机子弹01(100x100)
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("bullet01"), new CPictureBasic));	
	pic[_T("bullet01")]->Init(_T("bullet01.bmp"), _T("..bin/bullet01.bmp"));
	//加载战机子弹05(100x100)
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("bullet05"), new CPictureBasic));
	pic[_T("bullet05")]->Init(_T("bullet05.bmp"), _T("..bin/bullet05.bmp"));
	//加载战机子弹-laser01(600x900)
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("laser01"), new CPictureBasic));
	pic[_T("laser01")]->Init(_T("laser01.bmp"), _T("..bin/laser01.bmp"));
	D3DXVECTOR3 _Pos = CGameManager::GetGameInstance()->player01_Sprite.m_Pos;
	D3DXVECTOR3 _center = { (float)CGameManager::GetGameInstance()->pic[_T("laser01")]->GetWidth() / 2, (float)CGameManager::GetGameInstance()->pic[_T("laser01")]->GetHeight() ,0 };
	D3DXVECTOR3 _vSpeed = { 0,0,0 };
	RECT _rect = { 0,0, CGameManager::GetGameInstance()->pic[_T("laser01")]->GetWidth(), CGameManager::GetGameInstance()->pic[_T("laser01")]->GetHeight() };
	myplaybullet3.Init(pic[_T("laser01")]->GetTexture(), _Pos, _center, _rect, _vSpeed);


	// 加载战机子弹-skill01(我机大招帧动画)
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("skill01"), new CPictureBasic));
	pic[_T("skill01")]->Init(_T("skill01.bmp"), _T("..bin/skill01.bmp"));
	// 加载战机子弹-skill02
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("skill02"), new CPictureBasic));
	pic[_T("skill02")]->Init(_T("skill02.bmp"), _T("..bin/skill02.bmp"));
	// 加载战机子弹-skill03
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("skill03"), new CPictureBasic));
	pic[_T("skill03")]->Init(_T("skill03.bmp"), _T("..bin/skill03.bmp"));
	// 加载战机子弹-skill04
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("skill04"), new CPictureBasic));
	pic[_T("skill04")]->Init(_T("skill04.bmp"), _T("..bin/skill04.bmp"));
	// 加载战机子弹-skill05
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("skill05"), new CPictureBasic));
	pic[_T("skill05")]->Init(_T("skill05.bmp"), _T("..bin/skill05.bmp"));
	// 加载战机子弹-skill06
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("skill06"), new CPictureBasic));
	pic[_T("skill06")]->Init(_T("skill06.bmp"), _T("..bin/skill06.bmp"));
	// 加载战机子弹-skill07
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("skill07"), new CPictureBasic));
	pic[_T("skill07")]->Init(_T("skill07.bmp"), _T("..bin/skill07.bmp"));
	// 加载战机子弹-skill08
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("skill08"), new CPictureBasic));
	pic[_T("skill08")]->Init(_T("skill08.bmp"), _T("..bin/skill08.bmp"));
	// 加载战机子弹-skill09
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("skill09"), new CPictureBasic));
	pic[_T("skill09")]->Init(_T("skill09.bmp"), _T("..bin/skill09.bmp"));


	//加载敌机子弹06(100x100)
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("bullet06"), new CPictureBasic));
	pic[_T("bullet06")]->Init(_T("bullet06.bmp"), _T("..bin/bullet06.bmp"));
	//加载敌机子弹07(100x100)
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("bullet07"), new CPictureBasic));
	pic[_T("bullet07")]->Init(_T("bullet07.bmp"), _T("..bin/bullet07.bmp"));


	//加载敌机子弹20(100x100)_BOSS
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("bullet20"), new CPictureBasic));
	pic[_T("bullet20")]->Init(_T("bullet20.bmp"), _T("..bin/bullet20.bmp"));
	//加载敌机子弹21(100x100)_BOSS
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("bullet21"), new CPictureBasic));
	pic[_T("bullet21")]->Init(_T("bullet21.bmp"), _T("..bin/bullet21.bmp"));
	//加载敌机子弹22(100x100)_BOSS
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("bullet22"), new CPictureBasic));
	pic[_T("bullet22")]->Init(_T("bullet22.bmp"), _T("..bin/bullet22.bmp"));
	//加载敌机子弹23(100x100)_BOSS
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("bullet23"), new CPictureBasic));
	pic[_T("bullet23")]->Init(_T("bullet23.bmp"), _T("..bin/bullet23.bmp"));
	//加载敌机子弹24(100x100)_BOSS
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("bullet24"), new CPictureBasic));
	pic[_T("bullet24")]->Init(_T("bullet24.bmp"), _T("..bin/bullet24.bmp"));
	//加载敌机子弹25(100x100)_BOSS
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("bullet25"), new CPictureBasic));
	pic[_T("bullet25")]->Init(_T("bullet25.bmp"), _T("..bin/bullet25.bmp"));
	//加载敌机子弹26(100x100)_BOSS
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("bullet26"), new CPictureBasic));
	pic[_T("bullet26")]->Init(_T("bullet26.bmp"), _T("..bin/bullet26.bmp"));


	//加载敌机01（200x200）
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("enemy01"), new CPictureBasic));
	pic[_T("enemy01")]->Init(_T("enemy01.bmp"), _T("..bin/enemy01.bmp"));
	//加载敌机01_boom（200x200）
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("enemy01_boom"), new CPictureBasic));
	pic[_T("enemy01_boom")]->Init(_T("enemy01_boom.bmp"), _T("..bin/enemy01_boom.bmp"));
	//加载敌机02（200x200）
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("enemy02"), new CPictureBasic));
	pic[_T("enemy02")]->Init(_T("enemy02.bmp"), _T("..bin/enemy02.bmp"));
	//加载敌机02_boom（200x200）
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("enemy02_boom"), new CPictureBasic));
	pic[_T("enemy02_boom")]->Init(_T("enemy02_boom.bmp"), _T("..bin/enemy02_boom.bmp"));
	//加载敌机03（200x200）
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("enemy03"), new CPictureBasic));
	pic[_T("enemy03")]->Init(_T("enemy03.bmp"), _T("..bin/enemy03.bmp"));
	//加载敌机04（200x200）
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("enemy04"), new CPictureBasic));
	pic[_T("enemy04")]->Init(_T("enemy04.bmp"), _T("..bin/enemy04.bmp"));
	//加载敌机04_boom（200x200）
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("enemy04_boom"), new CPictureBasic));
	pic[_T("enemy04_boom")]->Init(_T("enemy04_boom.bmp"), _T("..bin/enemy04_boom.bmp"));

	// 加载爆炸01 
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("boom01"), new CPictureBasic));
	pic[_T("boom01")]->Init(_T("boom01.bmp"), _T("..bin/boom01.bmp"));
	// 加载爆炸02 
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("boom02"), new CPictureBasic));
	pic[_T("boom02")]->Init(_T("boom02.bmp"), _T("..bin/boom02.bmp"));
	// 加载爆炸03
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("boom03"), new CPictureBasic));
	pic[_T("boom03")]->Init(_T("boom03.bmp"), _T("..bin/boom03.bmp"));
	// 加载爆炸04
	pic.insert(pair<TSTRING, CPictureBasic*>(_T("boom04"), new CPictureBasic));
	pic[_T("boom04")]->Init(_T("boom04.bmp"), _T("..bin/boom04.bmp"));

	// 初始化音效
	string s;
	SoundManager::GetSoundManagerInstancePtr()->Initialize();
	s = "../bin/music/UI_music.mp3";
	SoundManager::getSingletonPtr()->CreateLoopedSound(s);			// 1  UI界面音乐
	s = "../bin/music/bgm_kaichangdonghua.mp3";
	SoundManager::getSingletonPtr()->CreateLoopedSound(s);			// 2  战斗界面音乐
	s = "../bin/music/gun.wav";										
	SoundManager::getSingletonPtr()->CreateStream(s);				// 3  单发子弹
	s = "../bin/music/极光音乐.wav";
	SoundManager::getSingletonPtr()->CreateStream(s);				// 4  极光
	s = "../bin/music/导弹发射.wav";
	SoundManager::getSingletonPtr()->CreateStream(s);				// 5  跟着导弹
	s = "../bin/music/boom.wav";
	SoundManager::getSingletonPtr()->CreateStream(s);				// 6  爆炸
	s = "../bin/music/被击中.wav";
	SoundManager::getSingletonPtr()->CreateStream(s);				// 7  被击中

	SoundManager::getSingletonPtr()->PlaySound(1, 0, NULL);			// 播放背景音乐
	
	//SoundManager::getSingletonPtr()->StopAllSounds();				// 关闭所有音乐
}

void CGameManager::Update()
{
	switch (m_GState)
	{
	case Scene_begin:
	{
		// 通过计时器来生成子弹(区分激光与其他子弹的生成时间)
		static DWORD preTime = GetTickCount();
		DWORD curTime = GetTickCount();
		float elapsedTime = (curTime - preTime)*0.001f;//换算成秒

		if (button_shuoming.IsButtonDown())
		{
			if (elapsedTime >= 1.0f / 4)
			{
				if (flag_shuoming == false)
					flag_shuoming = true;
				else
				{
					flag_shuoming = false;
				}
				preTime = curTime;
			}
			flag_story = false;
		}
	}
	break;
	case Scene_game:
	{
		backpic_Sprite.Update();
		player01_Sprite.Update();
		hp_back.Update();
		hp_front.Update_front();
		myplaybullet3.Update();
		CEnemyManager::GetEnemyInstance()->Update();
		CBulletManager::GetBulletInstance()->Update();
	}
	break;
	case Scene_over:
	{

	}
	break;
	default:
		break;
	}
}

void CGameManager::Render()
{
	D3DDevice->Clear(0, 0, D3DCLEAR_TARGET, 0xff000000, 1.0f, 0.0f);//背景刷
	D3DDevice->BeginScene();

	switch (m_GState)
	{
	case Scene_begin:
	{
		backpic_begin.Render();
		button_begin.Draw();
		button_shuoming.Draw();
		button_over.Draw();	

		if (button_begin.IsButtonDown())
		{
			m_GState = Scene_game;
			SoundManager::getSingletonPtr()->StopAllSounds();				// 关闭所有音乐
			SoundManager::getSingletonPtr()->PlaySound(2, 0, NULL);			// 播放背景音乐
		}		
		if (button_over.IsButtonDown())
			PostQuitMessage(0);

		score_bj.Render();
		Logo.Render();

		if (flag_shuoming == true)
		{
			FontRender();
			OI.Render();
		}
		if (flag_story == true)
		{
			switch (cur_frame)
			{
			case 1:
			{
				story01.Render();
				story01.pel -= 1;
			}
				break;
			case 2:
			{
				story02.Render();
				story02.pel -= 1;
			}
				break;
			default:
				break;
			}
			if (story01.pel<10)
			{
				cur_frame = 2;
			}
			if (story02.pel<10)
			{
				cur_frame = 3;
				flag_story == false;
			}
		}
	}
	break;
	case Scene_game:
	{
		backpic_Sprite.Render();
		CEnemyManager::GetEnemyInstance()->Render();
		hp_back.Render();
		hp_front.Render();
		CBulletManager::GetBulletInstance()->Render();
		player01_Sprite.Render();
		myplaybullet3.Render();

		score_bj.Render();			// 游戏说明背景图片
		Logo.Render();				// 图标
		if (flag_shuoming == true)
		{
			FontRender();			// 打字部分
			OI.Render();			// 操作说明图片
		}	

		// 胜利图片
		switch (num_level)
		{
		case 1:
		{
			if (num_total>10)
			{
				gamewin.Render();
				gamewin.pel--;
			}
		}
		break;
		case 2:
		{
			if (num_total > 30)
			{
				gamewin.Render();
				gamewin.pel--;
			}
		}
		break;
		default:
			break;
		}

		// num_level增加
		if (num_total > 10 && gamewin.pel < 5)
		{
			num_level++;
			gamewin.pel = 255;
		}
	}
	break;
	case Scene_over:
	{
			
	}
	break;
	default:
		break;
	}
		
	D3DDevice->EndScene();
	D3DDevice->Present(NULL, 0, 0, 0);
}

void CGameManager::FontUpdate()
{

}

void CGameManager::FontRender()
{
	// Score
	RECT rect_score = { 670, 120, 900, 300 };
	Font->DrawTextA(NULL, "游戏说明", -1, &rect_score, DT_TOP | DT_LEFT, 0xffeeefa5);
	// Small
	RECT rect_Small = { 620, 160, 800, 200 };
	string small_score;
	small_score = "Small:  "+ to_string(num_small);
	Font->DrawTextA(NULL, small_score.c_str(), -1, &rect_Small, DT_TOP | DT_LEFT, 0xffeeefa5);
	// Middle
	RECT rect_Middle = { 620, 210, 800, 250 };
	string middle_score;
	middle_score = "Middle:  " + to_string(num_middle);
	Font->DrawTextA(NULL, middle_score.c_str(), -1, &rect_Middle, DT_TOP | DT_LEFT, 0xffeeefa5);
	// Large
	RECT rect_Large = { 620, 260, 800, 300 };
	string large_score;
	large_score = "Large:  " + to_string(num_large);
	Font->DrawTextA(NULL, large_score.c_str(), -1, &rect_Large, DT_TOP | DT_LEFT, 0xffeeefa5);
	// Total
	RECT rect_Total = { 620, 310, 800, 350 };
	num_total = num_small + num_middle*2 + num_large*5;
	string total_score;
	total_score = "Score:  " + to_string(num_total);
	Font->DrawTextA(NULL, total_score.c_str(), -1, &rect_Total, DT_TOP | DT_LEFT, 0xffeeefa5);
	// Player hp
	RECT rect_hp = { 620, 360, 800, 400 };
	string playerhp_score;
	playerhp_score = "Py_hp:  " + to_string(player01_Sprite.m_hp_myplayer);
	Font->DrawTextA(NULL, playerhp_score.c_str(), -1, &rect_hp, DT_TOP | DT_LEFT, 0xffeeefa5);
	// Level
	RECT rect_Level = { 620, 410, 800, 500 };
	string level_score;
	level_score = "Level:  " + to_string(num_level);
	Font->DrawTextA(NULL, level_score.c_str(), -1, &rect_Level, DT_TOP | DT_LEFT, 0xffeeefa5);

}