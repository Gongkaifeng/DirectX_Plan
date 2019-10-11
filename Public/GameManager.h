#pragma once
enum eSceneState
{
	Scene_begin				// 游戏场景：开始界面
	,Scene_game				// 游戏场景：战斗
	,Scene_over				// 游戏场景：结束
	,Scene_none				// 无状态，待定
};

class CGameManager
{
public:
	CGameManager();
	~CGameManager();
	static CGameManager* GetGameInstance()
	{
		if (!m_pGameInstance)
			m_pGameInstance = new CGameManager;
		return m_pGameInstance;
	}
	IDirect3DDevice9* GetDevice() { return D3DDevice; }

	void	InitD3D(HWND hWnd);
	void	Init();
	void	Update();
	void	Render();

	void	FontUpdate();
	void	FontRender();

public:
	IDirect3D9*				Direct3D;			// D3D对象接口
	IDirect3DDevice9*		D3DDevice;			// 设备接口
	static CGameManager*	m_pGameInstance;	// 全局单例
	ID3DXLine*				g_pLine = NULL;		// 画线
	ID3DXFont*				Font = NULL;		// 字体部分

	CBegin_backpic			backpic_begin;		// 开始界面背景图
	CBegin_backpic			score_bj;			// 记分背景图
	CBegin_backpic			Logo;				// logo图
	CBegin_backpic			OI;					// 操作说明
	CBegin_backpic			story01;			// 前述图片1
	CBegin_backpic			story02;			// 前述图片2
	CBegin_backpic			gamewin;			// 战斗胜利
	CBegin_backpic			gameover;			// 战斗失败

	CUIButton				button_begin;		// 开始按钮
	CUIButton				button_over;		// 结束按钮
	CUIButton				button_shuoming;	// 说明按钮

	CBackgroundpicture		backpic_Sprite;		// 战斗界面背景图			
	CMyplayer				player01_Sprite;	// 我机
	CMyplayer_skill			skill_Sprite;		// 我机大招
	CMyplayerhp				hp_back;			// 后色
	CMyplayerhp				hp_front;			// 前色
	CMyplayBullet3			myplaybullet3;		// 我机激光子弹

	eSceneState				m_GState;			// 游戏场景状态

	map<TSTRING, CPictureBasic*>  pic;			// 存储图片

	int						num_small;			// 小型敌机歼灭数量
	int						num_middle;			// 中型敌机歼灭数量
	int						num_large;			// 大型敌机歼灭数量
	int						num_total;			// 敌机歼灭总数量
	int						num_level;			// 关卡
	int						cur_frame;			// 前述故事当前帧
	bool					flag_shuoming;		// 说明开关
	bool					flag_story;			// 故事开关
};

