#pragma once

class CBullet :public CSprite
{
public:
	CBullet(LPDIRECT3DTEXTURE9 _Texture, D3DXVECTOR3 _Pos, D3DXVECTOR3 _center, RECT _rect);
	CBullet();
	~CBullet();

	virtual void Update();				// �һ��ӵ�����
	virtual void BulletMove();			// �һ��ӵ��ƶ�
	virtual void Render();				// �ӵ���Ⱦ
	
};

