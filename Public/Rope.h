#pragma once

class CRope :public CSprite
{
public:
	CRope();
	~CRope();
public:
	void Init(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect);
	void Update();
	void Render();
	float tempRope;
	float scalex;
	float scaley;
	float ropespeed;
};

