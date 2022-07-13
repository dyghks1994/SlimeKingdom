#pragma once

class GameEndingScene : public GameScene
{
public:
	GameEndingScene(string name = "GameEndingScene");
	~GameEndingScene();

private:
	bool m_Restart;
	ImageUI* m_EndingImage;

public:
	virtual void ResetScene();
	virtual void InitScene();
	virtual void DoScene();
};

