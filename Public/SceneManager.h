#pragma once
class CSceneManager:public CSingleton<CSceneManager>
{
public:
	CSceneManager();
	~CSceneManager();
	void AddScene(TSTRING,CScene*);
	CScene* GetCurScene();
	void SetCurSceneName(TSTRING);
	TSTRING GetCurSceneName();
	
private:
	bool NeedInit;
	TSTRING CurSceneName;
	map<TSTRING, CScene*> SceneList;
};

