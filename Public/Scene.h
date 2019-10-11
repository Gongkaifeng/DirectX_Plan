#pragma once
class CScene
{
public:
	CScene();
	~CScene();
	virtual void Init(){}
	virtual void Update() {}
	virtual void Render() {}
};

