#pragma once

class CAnimationFrame
{
public:
	CAnimationFrame(TSTRING _Name, LPDIRECT3DTEXTURE9 _Texture, RECT _Rect);
	~CAnimationFrame();
	RECT GetRect() { return m_Rect; }
	LPDIRECT3DTEXTURE9 GetTexture() { return m_Texture; }

private:
	TSTRING m_Name;
	LPDIRECT3DTEXTURE9 m_Texture;
	RECT m_Rect;
};

