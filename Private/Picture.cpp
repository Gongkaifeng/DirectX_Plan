#pragma once
#include "stdafx.h"

CPicture::CPicture(TSTRING name, TSTRING path)
{
	Name = name;
	Path = path;
	Path = Name;
	D3DXCreateTextureFromFileEx(
		CGameManager::GetGameInstance()->GetDevice()    //�豸�ӿ�
		, Path.c_str()									//ͼ���ļ�·�����ļ���
		, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2	//������,�߶�
		, 0												//ָ�������������м���
		, 0												//����ʹ�÷�ʽ��һ��Ϊ0
		, D3DFMT_A8R8G8B8								//ָ�������ͼ�θ�ʽ
		, D3DPOOL_DEFAULT								//�����ŵ��ڴ����ͣ�һ��Ϊ0
		, D3DX_DEFAULT									//����Ĺ��˷�ʽ
		, D3DX_DEFAULT									//�Զ����ɵ��������й��˷�ʽ
		, 0xffc3c3c3									//����͸��ɫARGB
		, 0												//ͼ���ļ���Ϣ��ŵ�ַ������Ϊ0
		, 0												//��ɫ��洢��ַ
		, &Texture);									//������Direct3D����ָ���ŵ�ַ

	D3DSURFACE_DESC desc;
	Texture->GetLevelDesc(0, &desc);
	Width = desc.Width;
	Height = desc.Height;
}

CPicture::~CPicture() { Texture->Release(); }

WORD CPicture::GetWidth() { return Width; }
WORD CPicture::GetHeight() { return Height; }
LPDIRECT3DTEXTURE9 CPicture::GetTexture() { return Texture; }