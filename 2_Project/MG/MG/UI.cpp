#include "pch.h"
#include "UI.h"

UI::UI(string name)
{
	MGScene->ResistUI(name, this);

	m_Depth = 0;
}

void UI::Update()
{
}

void UI::Draw()
{

}
