#include "pch.h"
#include "TextUI.h"

TextUI::TextUI(string name)
{
	MGScene->ResistUI(name, this);
}

void TextUI::Update()
{
}

void TextUI::Draw()
{
	if (m_Active && m_Visible)
	{
		MGGraphicEngine->SetTransform(GetTransform().GetSRMatrix());
		D2D1_POINT_2F drawPoint = { GetTransform().Position.x, GetTransform().Position.y };
		MGGraphicEngine->DrawTextFormat(drawPoint.x, drawPoint.y, DefaultBrushColor, m_Text);
		MGGraphicEngine->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}