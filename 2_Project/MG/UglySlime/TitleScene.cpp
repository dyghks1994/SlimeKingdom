#include "stdafx.h"

TitleScene::TitleScene(string name)
{
	m_SceneName = name;
}

TitleScene::~TitleScene()
{

}

void TitleScene::ResetScene()
{
	SoundManager::PlayBGM("Title");

	m_isPressAnyKey = false;
}

void TitleScene::InitScene()
{
	m_Conditions[(int)SLGameScene::Intro].push_back([this]()->bool { return m_isPressAnyKey; });

	m_BackGroundUI = new ImageUI("BG");
	m_BackGroundUI->SetSprite(SLDataManager->GetSprite("title_background"));
	m_BackGroundUI->m_Transform.Position.x = 960;
	m_BackGroundUI->m_Transform.Position.y = 540;

	m_LogoUI = new ImageUI("Logo");
	m_LogoUI->SetAnimation(SLDataManager->GetAnimation("title_logo_29"));
	m_LogoUI->m_Transform.Position.x = 960;
	m_LogoUI->m_Transform.Position.y = 490;
}

void TitleScene::DoScene()
{
	for (int i = 0; i < 256; i++)
	{
		if (KeyInput->InputKeyDown(i))
		{
			m_isPressAnyKey = true;
			break;
		}
	}
}
