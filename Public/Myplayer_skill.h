#pragma once

class CMyplayer_skill :public CSprite
{
public:
	CMyplayer_skill();
	~CMyplayer_skill();

	void	Init(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect);
	void	Update();
	void	Render();
	void	Move();

	int		pel;				// 我机大招透明度值

};

