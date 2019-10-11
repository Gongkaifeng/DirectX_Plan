#pragma once
#include "Sprite.h"
class CBuff :public CSprite
{
public:
	CBuff();
	~CBuff();
	CBuff(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect);

	virtual void Update();				// 我机子弹更新
	virtual void BulletMove();			// 我机子弹移动
	virtual void Render();				// 子弹渲染
};

