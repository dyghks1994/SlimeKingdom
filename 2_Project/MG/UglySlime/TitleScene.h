#pragma once

class TitleScene : public GameScene
{
public:
	TitleScene(string name = "TitleScene");
	~TitleScene();

private:
	ImageUI* m_BackGroundUI;
	ImageUI* m_LogoUI;


	bool m_isPressAnyKey;

public:
	virtual void ResetScene();
	virtual void InitScene();
	virtual void DoScene();
};

