#pragma once

class CMyplayBullet4 :public CBullet
{
public:
	CMyplayBullet4();
	~CMyplayBullet4();
	CMyplayBullet4(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect, D3DXVECTOR3 _vSpeed);

	void		Update();
	void		Render();
	void		BulletMove();
	void		GetRC();

public:
	int		    curFrame_b4;
	DWORD	    m_Pretime;
	RECT		rc_mybullet4;
	
};

