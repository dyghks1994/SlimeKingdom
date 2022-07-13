#pragma once
class Renderer : public Object
{
public:
	Renderer();

public:
	D2D1_SIZE_F m_Size;
	int m_Depth;
	float m_Opacity;

private:
	Sprite* m_pSprite;

public:
	void Draw();
	void SetSprite(Sprite* sprite);
	Sprite* const GetSprite();
};