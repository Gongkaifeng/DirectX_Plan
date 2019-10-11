#pragma once
#include "stdafx.h"

CPicture::CPicture(TSTRING name, TSTRING path)
{
	Name = name;
	Path = path;
	Path = Name;
	D3DXCreateTextureFromFileEx(
		CGameManager::GetGameInstance()->GetDevice()    //设备接口
		, Path.c_str()									//图形文件路径与文件名
		, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2	//纹理宽度,高度
		, 0												//指定渐进纹理序列级数
		, 0												//纹理使用方式，一般为0
		, D3DFMT_A8R8G8B8								//指定纹理的图形格式
		, D3DPOOL_DEFAULT								//纹理存放的内存类型，一般为0
		, D3DX_DEFAULT									//纹理的过滤方式
		, D3DX_DEFAULT									//自动生成的纹理序列过滤方式
		, 0xffc3c3c3									//设置透明色ARGB
		, 0												//图形文件信息存放地址，可设为0
		, 0												//调色板存储地址
		, &Texture);									//创建的Direct3D纹理指针存放地址

	D3DSURFACE_DESC desc;
	Texture->GetLevelDesc(0, &desc);
	Width = desc.Width;
	Height = desc.Height;
}

CPicture::~CPicture() { Texture->Release(); }

WORD CPicture::GetWidth() { return Width; }
WORD CPicture::GetHeight() { return Height; }
LPDIRECT3DTEXTURE9 CPicture::GetTexture() { return Texture; }