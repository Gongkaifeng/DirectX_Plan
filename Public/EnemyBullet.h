#pragma once

class CEnemyBullet :public CBullet
{
public:
	CEnemyBullet(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect);
	~CEnemyBullet();
	CEnemyBullet();
	void	Update();				
	void	Render();				
	void	BulletMove();			
	bool	IsHit();
	void	GetRc();
public:
	RECT	rc_enemybullet;
};

