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
	TSTRING m_Name;								// ͼƬ����
	TSTRING m_Path;								// ·��
	LPDIRECT3DTEXTURE9 m_Texture;				// ����ӿ�
	WORD m_Width;								// ����ͼ���
	WORD m_Height;
};

