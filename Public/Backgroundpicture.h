#pragma once
class CBackgroundpicture :public CSprite
{
public:
	CBackgroundpicture();
	~CBackgroundpicture();
public:
	void	Init(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect);
	void	Update();
	void	Render();

	D3DXMATRIX mat;
};

