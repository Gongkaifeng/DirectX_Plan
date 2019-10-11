#pragma once
enum eSceneState
{
	Scene_begin				// ��Ϸ��������ʼ����
	,Scene_game				// ��Ϸ������ս��
	,Scene_over				// ��Ϸ����������
	,Scene_none				// ��״̬������
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
	IDirect3D9*				Direct3D;			// D3D����ӿ�
	IDirect3DDevice9*		D3DDevice;			// �豸�ӿ�
	static CGameManager*	m_pGameInstance;	// ȫ�ֵ���
	ID3DXLine*				g_pLine = NULL;		// ����
	ID3DXFont*				Font = NULL;		// ���岿��

	CBegin_backpic			backpic_begin;		// ��ʼ���汳��ͼ
	CBegin_backpic			score_bj;			// �Ƿֱ���ͼ
	CBegin_backpic			Logo;				// logoͼ
	CBegin_backpic			OI;					// ����˵��
	CBegin_backpic			story01;			// ǰ��ͼƬ1
	CBegin_backpic			story02;			// ǰ��ͼƬ2
	CBegin_backpic			gamewin;			// ս��ʤ��
	CBegin_backpic			gameover;			// ս��ʧ��

	CUIButton				button_begin;		// ��ʼ��ť
	CUIButton				button_over;		// ������ť
	CUIButton				button_shuoming;	// ˵����ť

	CBackgroundpicture		backpic_Sprite;		// ս�����汳��ͼ			
	CMyplayer				player01_Sprite;	// �һ�
	CMyplayer_skill			skill_Sprite;		// �һ�����
	CMyplayerhp				hp_back;			// ��ɫ
	CMyplayerhp				hp_front;			// ǰɫ
	CMyplayBullet3			myplaybullet3;		// �һ������ӵ�

	eSceneState				m_GState;			// ��Ϸ����״̬

	map<TSTRING, CPictureBasic*>  pic;			// �洢ͼƬ

	int						num_small;			// С�͵л���������
	int						num_middle;			// ���͵л���������
	int						num_large;			// ���͵л���������
	int						num_total;			// �л�����������
	int						num_level;			// �ؿ�
	int						cur_frame;			// ǰ�����µ�ǰ֡
	bool					flag_shuoming;		// ˵������
	bool					flag_story;			// ���¿���
};

