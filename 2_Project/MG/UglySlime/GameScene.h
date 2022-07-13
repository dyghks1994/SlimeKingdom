#pragma once

class GameSceneManager;

class GameScene : public State
{
public:
	GameScene();
	~GameScene();

protected:
	string m_SceneName;

public:
	vector<Condition> m_Conditions[(int)SLGameScene::SLGameSceneNum];

public:
	virtual void Initialize();
	virtual void AddConditions();
	virtual void Do();

	virtual void ResetScene();
	virtual void DoScene();
	virtual void InitScene();

	void AddScene();

	void SetBrenches(State* scene, int scene_num);
};

