#pragma once
class CPicture
{
public:
	CPicture(TSTRING, TSTRING);
	~CPicture();

	WORD GetWidth();
	WORD GetHeight();
	LPDIRECT3DTEXTURE9 GetTexture();

private:
	TSTRING Name;
	TSTRING Path;
	LPDIRECT3DTEXTURE9 Texture;
	WORD Width;
	WORD Height;
};

