#pragma once
#include "stdafx.h"

CPictureBasic::~CPictureBasic()
{
	m_Texture->Release();
}

void CPictureBasic::Init(TSTRING _name, TSTRING _Path)
{
	m_Name = _name;
	m_Path = _Path;
	D3DXCreateTextureFromFileEx(
		CGameManager::GetGameInstance()->GetDevice()    //�豸�ӿ�
		, m_Name.c_str()								//ͼ���ļ�·�����ļ���
		, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2	//������,�߶�
		, 0												//ָ�������������м���
		, 0												//����ʹ�÷�ʽ��һ��Ϊ0
		, D3DFMT_A8R8G8B8								//ָ�������ͼ�θ�ʽ
		, D3DPOOL_DEFAULT								//�����ŵ��ڴ����ͣ�һ��Ϊ0
		, D3DX_DEFAULT									//����Ĺ��˷�ʽ
		, D3DX_DEFAULT									//�Զ����ɵ��������й��˷�ʽ
		, 0xffc3c3c3									//����͸��ɫARGB(clear��������ɫ)
		, 0												//ͼ���ļ���Ϣ��ŵ�ַ������Ϊ0
		, 0												//��ɫ��洢��ַ
		, &m_Texture);									//������Direct3D����ָ���ŵ�ַ
	
	D3DSURFACE_DESC desc;
	m_Texture->GetLevelDesc(0, &desc);
	m_Width = desc.Width;
	m_Height = desc.Height;
}