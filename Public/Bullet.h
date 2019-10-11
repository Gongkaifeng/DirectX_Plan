#pragma once

class CBullet :public CSprite
{
public:
	CBullet(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect);
	CBullet();
	~CBullet();

	virtual void Update();				// 我机子弹更新
	virtual void BulletMove();			// 我机子弹移动
	virtual void Render();				// 子弹渲染
	
};

