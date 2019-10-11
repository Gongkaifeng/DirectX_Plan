#pragma once

class CMyplayBullet3 :public CBullet
{
public:
	CMyplayBullet3();
	~CMyplayBullet3();

	void	Init(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect, D3DXVECTOR3 _vSpeed);
	void	Update();
	void	Render();
	void	BulletMove();
	void	GetRC();

	bool	ishide;
	RECT    rc_mybullet3;
	int		pel;				// Í¸Ã÷¶ÈÖµ

};

