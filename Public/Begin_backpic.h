#pragma once
#include "Sprite.h"

class CBegin_backpic :public CSprite
{
public:
	CBegin_backpic();
	~CBegin_backpic();
public:
	void		Init(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect);
	void		Update();
	void		Render();
	D3DXMATRIX mat;

	int 		pel;

};

