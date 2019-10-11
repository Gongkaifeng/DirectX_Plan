// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�: 
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <ctime>
#include <iostream>
#include <xstring>
#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>
#include <vector>
#include <map>
#include <list>
#include <string>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
using namespace std;

#define TSTRING basic_string<TCHAR>

typedef struct tagHitStruct				// ��ײ��ʱ�ṹ
{
	float Value;
	char  Flag;
}HITSTRUCT;
#define SWAP(X, Y) { t = List[X]; List[X] = List[Y]; List[Y] = t; }

// �л�״̬����
enum eEnemyState
{
	eES_Normal
	, eES_Boom
	, eES_Dead
};

// �һ�״̬����
enum eMyplayState
{
	eMS_Normal
	, eMS_Skill
	, eMS_Boom
	, eMS_Dead
};
# define MAXHP_PLAYER  50				// �һ����Ѫ��
// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "Singleton.h"		
#include "DirectInput.h"				//
#include "PictureBasic.h"
#include "Picture.h"
#include "AnimationFrame.h"
#include "Animation.h"
#include "ResManager.h"

// UI����
#include "UIObject.h"
#include "UIButton.h"
#include "BeginScene.h"
#include "Scene.h"

//�������
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#include "Object.h"
#pragma comment(lib,"fmodex_vc.lib")
#include "SoundManager.h"

// GameManager����
#include "Sprite.h"						// ������
#include "Begin_backpic.h"				// ��ʼ���汳��ͼ
#include "Backgroundpicture.h"			// ս�����汳��ͼ
#include "Bullet.h"						// �ӵ�����
#include "MyplayBullet.h"				// �һ��ӵ�����1
#include "MyplayBullet2.h"				// �һ��ӵ�����2
#include "MyplayBullet3.h"				// �һ��ӵ�����3_����
#include "MyplayBullet4.h"				// �һ��ӵ�����4_����
#include "EnemyBullet.h"				// �л��ӵ�����1
#include "EnemyBullet2.h"				// �л��ӵ�����2
#include "EnemyBullet3.h"				// �л��ӵ�����3
#include "BulletManager.h"				// �ӵ�������
#include "Myplayer.h"					// �һ�
#include "Myplayerhp.h"					// �һ�Ѫ��
#include "Myplayer_skill.h"				// �һ�����skill
#include "Enemy.h"						// �л�1
#include "Enemy2.h"						// �л�2
#include "Enemy3.h"						// �л�3
#include "Buff.h"						// ����


#include "UIManager.h"
#include "EnemyManager.h"
#include "SceneManager.h"
#include "GameManager.h"


//�����ĸ�����
#define DIR_UP				0
#define DIR_DOWN			1
#define DIR_LEFT			2
#define DIR_RIGHT			3
#define DIR_NONE			-1			// ����һ������Ҫ�ƶ��ķ���
#define PI					3.141592654f

enum FireStyle
{
	FIRE_NONE
	, FIRE_01		// �����ӵ�
	, FIRE_02		// �����ӵ�
	, FIRE_03		// �����ӵ�
	, FIRE_04		// ���ٵ���
	, FIRE_05		// ����ģʽ
	, FIRE_06		// ȫ������
};

extern CDirectInput g_DXInput;			// ȫ�ֶ�һ�ݱ���

extern HWND hWnd;
