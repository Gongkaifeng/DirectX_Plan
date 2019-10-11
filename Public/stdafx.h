// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
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

typedef struct tagHitStruct				// 碰撞临时结构
{
	float Value;
	char  Flag;
}HITSTRUCT;
#define SWAP(X, Y) { t = List[X]; List[X] = List[Y]; List[Y] = t; }

// 敌机状态机制
enum eEnemyState
{
	eES_Normal
	, eES_Boom
	, eES_Dead
};

// 我机状态机制
enum eMyplayState
{
	eMS_Normal
	, eMS_Skill
	, eMS_Boom
	, eMS_Dead
};
# define MAXHP_PLAYER  50				// 我机最大血量
// TODO:  在此处引用程序需要的其他头文件
#include "Singleton.h"		
#include "DirectInput.h"				//
#include "PictureBasic.h"
#include "Picture.h"
#include "AnimationFrame.h"
#include "Animation.h"
#include "ResManager.h"

// UI部分
#include "UIObject.h"
#include "UIButton.h"
#include "BeginScene.h"
#include "Scene.h"

//对象管理
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#include "Object.h"
#pragma comment(lib,"fmodex_vc.lib")
#include "SoundManager.h"

// GameManager部分
#include "Sprite.h"						// 精灵类
#include "Begin_backpic.h"				// 开始界面背景图
#include "Backgroundpicture.h"			// 战斗界面背景图
#include "Bullet.h"						// 子弹基类
#include "MyplayBullet.h"				// 我机子弹类型1
#include "MyplayBullet2.h"				// 我机子弹类型2
#include "MyplayBullet3.h"				// 我机子弹类型3_极光
#include "MyplayBullet4.h"				// 我机子弹类型4_大招
#include "EnemyBullet.h"				// 敌机子弹类型1
#include "EnemyBullet2.h"				// 敌机子弹类型2
#include "EnemyBullet3.h"				// 敌机子弹类型3
#include "BulletManager.h"				// 子弹管理类
#include "Myplayer.h"					// 我机
#include "Myplayerhp.h"					// 我机血条
#include "Myplayer_skill.h"				// 我机大招skill
#include "Enemy.h"						// 敌机1
#include "Enemy2.h"						// 敌机2
#include "Enemy3.h"						// 敌机3
#include "Buff.h"						// 道具


#include "UIManager.h"
#include "EnemyManager.h"
#include "SceneManager.h"
#include "GameManager.h"


//定义四个方向
#define DIR_UP				0
#define DIR_DOWN			1
#define DIR_LEFT			2
#define DIR_RIGHT			3
#define DIR_NONE			-1			// 定义一个不需要移动的方向
#define PI					3.141592654f

enum FireStyle
{
	FIRE_NONE
	, FIRE_01		// 单发子弹
	, FIRE_02		// 两发子弹
	, FIRE_03		// 三发子弹
	, FIRE_04		// 跟踪导弹
	, FIRE_05		// 极光模式
	, FIRE_06		// 全屏大招
};

extern CDirectInput g_DXInput;			// 全局独一份变量

extern HWND hWnd;
