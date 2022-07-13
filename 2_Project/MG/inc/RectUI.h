#pragma once
enum class FillDir
{
	Left,
	Right,
	Top,
	Bottom,

	Num
};

class RectUI : public UI
{
public:
	RectUI(string name = "Rect");

public:
	D2D1_SIZE_F m_Size;
	D2D1_COLOR_F m_Color;
	bool m_isFill;
	float m_FillAmount;
	FillDir m_FillDir;

public:
	virtual void Update();
	virtual void Draw();
};