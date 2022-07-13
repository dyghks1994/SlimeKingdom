#include "pch.h"
#include "ImageUI.h"

ImageUI::ImageUI(string name)
{
	MGScene->ResistUI(name, this);

	m_pRenderer = new Renderer();
	m_pAnimation = nullptr;

	m_pRenderer->SetParent(this);
}

void ImageUI::Update()
{
	if (m_pAnimation != nullptr)
	{
		m_pAnimation->Update();
		if (m_pAnimation->GetNowSprite() != nullptr)
		{
			m_pRenderer->SetSprite(m_pAnimation->GetNowSprite());
		}
	}
}

void ImageUI::Draw()
{
	if (m_Active && m_Visible)
	{
		m_pRenderer->Draw();
	}
}

void ImageUI::SetSprite(Sprite* sprite)
{
	if (sprite == nullptr) return;

	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new Renderer();
	}

	m_pRenderer->SetSprite(sprite);
}

void ImageUI::SetAnimation(Animation* anim)
{
	if (m_pAnimation == nullptr)
	{
		m_pAnimation = new Animation();
	}
	m_pAnimation = anim;
}
