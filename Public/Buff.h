#pragma once
#include "Sprite.h"
class CBuff :public CSprite
{
public:
	CBuff();
	~CBuff();
	CBuff(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect);

	virtual void Update();				// �һ��ӵ�����
	virtual void BulletMove();			// �һ��ӵ��ƶ�
	virtual void Render();				// �ӵ���Ⱦ
};

