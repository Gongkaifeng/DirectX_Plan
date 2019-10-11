#pragma once
class CEnemyBullet3 :public CSprite
{
public:
	CEnemyBullet3();
	~CEnemyBullet3();
	CEnemyBullet3(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect, D3DXVECTOR3 _vSpeed, float _angle);

	void	  Update();
	void	  Render();
	void	  BulletMove();
	bool	  IsHit();
	void	  GetRc();

public:
	int		  curFrame_b3;
	DWORD	  m_Pretime;
	RECT	  rc_enemybullet3;
	int		  pel;					// Í¸Ã÷¶ÈÖµ
};

