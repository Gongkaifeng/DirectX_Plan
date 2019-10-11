#pragma once

class CEnemyBullet2 :public CBullet
{
public:
	CEnemyBullet2(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect, D3DXVECTOR3 _vSpeed);
	~CEnemyBullet2();
	CEnemyBullet2();
	void	Update();
	void	Render();
	void	BulletMove();
	bool	IsHit();
	void	GetRc();

public:
	RECT	rc_enemybullet2;

};

