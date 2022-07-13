#pragma once
class GameOverScene : public GameScene
{
public:
	GameOverScene(string name = "GameOverScene");
	~GameOverScene();

private:
	ImageUI* m_GameOverUI;
	bool m_isPressAnyKey;

public:
	virtual void ResetScene();
	virtual void InitScene();
	virtual void DoScene();
};

