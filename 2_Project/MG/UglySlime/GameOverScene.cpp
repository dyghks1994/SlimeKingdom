#include "stdafx.h"
#include "GameOverScene.h"

GameOverScene::GameOverScene(string name)
{
	m_SceneName = name;
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::ResetScene()
{
	m_isPressAnyKey = false;
}

void GameOverScene::InitScene()
{
	m_Conditions[(int)SLGameScene::Title].push_back([this]()->bool { return m_isPressAnyKey; });

	m_GameOverUI = new ImageUI("GameOver");
	m_GameOverUI->SetSprite(SLDataManager->GetSprite("GAMEOVER"));
	m_GameOverUI->m_Transform.Position.x = 960;
	m_GameOverUI->m_Transform.Position.y = 540;
}

void GameOverScene::DoScene()
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