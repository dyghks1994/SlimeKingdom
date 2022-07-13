#pragma once

class GameSceneManager : public FSM
{
public:
	GameSceneManager();
	~GameSceneManager();

private:
	GameScene* m_GameScenes[(int)SLGameScene::SLGameSceneNum];

public:
	virtual void Initialize();
	virtual void Update();
};

