#include "stdafx.h"
#include "GameEndingScene.h"

GameEndingScene::GameEndingScene(string name)
{
	m_SceneName = name;
}

GameEndingScene::~GameEndingScene()
{

}

void GameEndingScene::ResetScene()
{
	SoundManager::PlayBGM("Ending");

	m_Restart = false;
}

void GameEndingScene::InitScene()
{
	m_Conditions[(int)SLGameScene::Title].push_back([this]()->bool { return m_Restart; });

	m_EndingImage = new ImageUI("Ending");
	m_EndingImage->SetSprite(SLDataManager->GetSprite("Ending"));
	m_EndingImage->m_Transform.Position.x = 960;
	m_EndingImage->m_Transform.Position.y = 540;
}

void GameEndingScene::DoScene()
{
	for (int i = 0; i < 256; i++)
	{
		if (KeyInput->InputKeyDown(i))
		{
			m_Restart = true;
			break;
		}
	}
}
