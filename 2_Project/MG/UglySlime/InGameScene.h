#pragma once

class Monster;

/// 인게임 클래스
class InGameScene : public GameScene
{
public:
	InGameScene(string name = "InGameScene");
	~InGameScene();

private:
	bool m_Ending;
	GameObject* m_BG;
	Player* m_Player;
	Animator* m_PlayerAnimator;

	ImageUI* m_Manual;

public:
	virtual void ResetScene();
	virtual void InitScene();
	virtual void DoScene();
};

