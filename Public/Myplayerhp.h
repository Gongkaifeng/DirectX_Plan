#pragma once

class CMyplayerhp :public CSprite
{
public:
	CMyplayerhp();
	~CMyplayerhp();

public:
	void	Init(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect);
	void	Update();
	void	Update_front();
	void	Render();
	void	Render_front();
	void	PlayerhpMove();

	int		pel;				// 我机透明度值
};

