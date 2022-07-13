#pragma once
class IntroScene : public GameScene
{
public:
	IntroScene(string name = "IntroScene");
	~IntroScene();

private:
	ImageUI* m_Intro;

	float m_OpacityChange;
	const float m_OpacityValue = 3.0f / (60 * 1.0f);

	float m_WaitCheck;
	float m_TimeCheck;

	int m_State;

	int m_NowCutNum;

	const int m_CutNum = 7;

public:
	virtual void ResetScene();
	virtual void InitScene();
	virtual void DoScene();

	bool WaitCut(float time);
	void NextCut();
	bool FadeInOut(bool fade);
};

