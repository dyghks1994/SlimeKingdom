#include "pch.h"
#include "Renderer.h"

Renderer::Renderer()
	:m_Size({ 100.0f, 100.0f }), m_pSprite(nullptr), m_Depth(0), m_Opacity(1.0f)
{
}

void Renderer::Draw()
{
	if (m_Active && m_Visible)
	{
		if (m_pSprite != nullptr)
		{
			MGGraphicEngine->SetTransform(GetTransform().GetSRMatrix());
			MGGraphicEngine->DrawBitmap(GetTransform(), m_pSprite->m_OriginPos, m_Size, m_pSprite->m_SpriteRect, m_pSprite->m_pBitmap, m_Opacity);
			MGGraphicEngine->SetTransform(D2D1::Matrix3x2F::Identity());
		}
	}
}

void Renderer::SetSprite(Sprite* sprite)
{
	if (sprite == nullptr) return;

	m_pSprite = sprite;
	float width = m_pSprite->m_SpriteRect.right - m_pSprite->m_SpriteRect.left;
	float height = m_pSprite->m_SpriteRect.bottom - m_pSprite->m_SpriteRect.top;

	m_Size.width = width;
	m_Size.height = height;
}

Sprite* const Renderer::GetSprite()
{
	return m_pSprite;
}
