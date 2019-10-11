#pragma once
class CSprite
{
public:
	CSprite();
	~CSprite();
	virtual void Init(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect);		// 初始化
	virtual void Update();					// 更新 虚函数
	virtual void Render();					// 绘制 虚函数

	bool	HitTest(RECT rc1, RECT rc2);	// 矩形区域碰撞
	void	Sort4(HITSTRUCT *List);			// 数据交换函数

public:
	LPD3DXSPRITE		m_pSprite;		    // 图片精灵
	LPDIRECT3DTEXTURE9  m_Texture;		    // 纹理

	RECT				m_rect;			    // 图片绘制区域
	D3DXVECTOR3			m_Pos;			    // 目标坐标
	D3DXVECTOR3			m_center;		    // 图片中心

	D3DXVECTOR3			m_vSpeed;		    // 移动速度向量
	DWORD				m_Speed;			// 移动速度

	D3DXMATRIX			scaleMat;			// 缩放
	D3DXMATRIX			roteMat;			// 旋转
	D3DXMATRIX			transMat;			// 平移
	D3DXMATRIX			matMatrix;	        // 综合矩阵
	float				m_angle;		    // 旋转角度
	double				scaleX;				// x方向缩放比例
	double				scaleY;				// y方向缩放比例
	
};

