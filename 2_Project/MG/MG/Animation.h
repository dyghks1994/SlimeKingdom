#pragma once
class Animation : public State
{
public:
	Animation(vector<Sprite*> sprites);
	Animation();
	Animation(Animation& anim);

public:
	vector<Sprite*> m_pSprites;

	float m_Speed;
	float m_TotalDelay;

	bool m_IsLoop;
	int m_NowIndex;

public:
	void Reset();
	void Update();
	Sprite* GetNowSprite();
	float GetProgress();
};

