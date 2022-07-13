#pragma once
class TextUI : public UI
{
public:
	TextUI(string name = "Text");

public:
	const WCHAR* m_Text;

public:
	virtual void Update();
	virtual void Draw();
};

