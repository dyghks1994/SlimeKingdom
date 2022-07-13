#pragma once
class UI : public Object
{
public:
	UI(string name = "UI");

public:
	int m_Depth;

public:
	virtual void Update();
	virtual void Draw();
};