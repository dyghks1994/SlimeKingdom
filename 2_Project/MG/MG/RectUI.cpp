#include "pch.h"
#include "RectUI.h"

RectUI::RectUI(string name)
	:m_Size({ 100.0f,100.0f }), m_Color(DefaultBrushColor), m_isFill(true), m_FillAmount(1.0f), m_FillDir(FillDir::Right)
{
	MGScene->ResistUI(name, this);
}

void RectUI::Update()
{
	//FillAmount값 보정
	if (m_FillAmount < 0)
	{
		m_FillAmount = 0;
	}

	if (m_FillAmount >= 1)
	{
		m_FillAmount = 1;
	}
}

void RectUI::Draw()
{
	if (m_Active && m_Visible)
	{
		MGGraphicEngine->SetTransform(GetTransform().GetSRMatrix());
		D2D1_POINT_2F drawPoint = GetTransform().Position;
		float width = m_Size.width;
		float height = m_Size.height;

		//FillAmount가 1이상이면 그냥 그린다
		if (m_FillAmount >= 1.0f)
		{
			if (m_isFill)
			{
				MGGraphicEngine->DrawFillRectangle(drawPoint, width, height, m_Color);
			}
			else
			{
				MGGraphicEngine->DrawRectangle(drawPoint, width, height, m_Color);
			}

			return;
		}

		//FillAmount가 1이하면 
		D2D1_RECT_F rect = { drawPoint.x - width * 0.5f, drawPoint.y - height * 0.5f, drawPoint.x + width * 0.5f, drawPoint.y + height * 0.5f };

		switch (m_FillDir)
		{
		case FillDir::Left:
		{
			rect.left = rect.right - (width * m_FillAmount);
		}
		break;

		case FillDir::Right:
		{
			rect.right = rect.left + (width * m_FillAmount);
		}
		break;

		case FillDir::Top:
		{
			rect.top = rect.bottom - (height * m_FillAmount);

		}
		break;
		case FillDir::Bottom:
		{
			rect.bottom = rect.top + (height * m_FillAmount);
		}
		break;
		}

		if (m_isFill)
		{
			MGGraphicEngine->DrawFillRectangle(rect.left, rect.top, rect.right, rect.bottom, m_Color);
		}
		else
		{
			MGGraphicEngine->DrawRectangle(rect.left, rect.top, rect.right, rect.bottom, m_Color);
		}
		MGGraphicEngine->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}
