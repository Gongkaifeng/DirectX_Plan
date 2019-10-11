#pragma once

class CPictureBasic
{
public:
	CPictureBasic() {}
	~CPictureBasic();
	void Init(TSTRING _name, TSTRING _Path);	// IDirect3DDevice9* _pDevice
	WORD GetWidth() { return m_Width; }
	WORD GetHeight() { return m_Height; }
	LPDIRECT3DTEXTURE9 GetTexture() { return m_Texture; }

private:
	TSTRING m_Name;								// 图片名字
	TSTRING m_Path;								// 路径
	LPDIRECT3DTEXTURE9 m_Texture;				// 纹理接口
	WORD m_Width;								// 整张图宽高
	WORD m_Height;
};

