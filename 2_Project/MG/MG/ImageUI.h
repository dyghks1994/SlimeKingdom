#pragma once
class ImageUI : public UI
{
public:
	ImageUI(string name = "Text");

public:
	Renderer* m_pRenderer;
	Animation* m_pAnimation;

public:
	virtual void Update();
	virtual void Draw();

	void SetSprite(Sprite* sprite);
	void SetAnimation(Animation* anim);
};

