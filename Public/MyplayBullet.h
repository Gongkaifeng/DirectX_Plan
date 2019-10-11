#pragma once

class CMyplayBullet :public CBullet
{
public:
	CMyplayBullet();
	~CMyplayBullet();
	CMyplayBullet(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect, D3DXVECTOR3 _vSpeed);
	
	void	Update();
	void	Render();
	void	BulletMove();
	void	GetRC();
	RECT    rc_mybullet;

};
