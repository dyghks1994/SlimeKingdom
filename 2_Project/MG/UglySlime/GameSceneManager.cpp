#include "stdafx.h"
#include "GameSceneManager.h"

GameSceneManager::GameSceneManager()
{
	for (int i = 0; i < (int)SLGameScene::SLGameSceneNum; i++)
	{
		m_GameScenes[i] = nullptr;
	}
}

GameSceneManager::~GameSceneManager()
{
	for (int i = 0; i < (int)SLGameScene::SLGameSceneNum; i++)
	{
		delete m_GameScenes[i];
	}
}

void GameSceneManager::Initialize()
{
	m_GameScenes[(int)SLGameScene::Title] = new TitleScene();
	m_GameScenes[(int)SLGameScene::Intro] = new IntroScene();
	m_GameScenes[(int)SLGameScene::InGame] = new InGameScene();
	m_GameScenes[(int)SLGameScene::GameEnding] = new GameEndingScene();
	m_GameScenes[(int)SLGameScene::GameOver] = new GameOverScene();

	for (int i = 0; i < (int)SLGameScene::SLGameSceneNum; i++)
	{
		m_GameScenes[i]->Initialize();
		for (int j = 0; j < (int)SLGameScene::SLGameSceneNum; j++)
		{
			if (i == j) continue;
			m_GameScenes[i]->SetBrenches(m_GameScenes[j], j);
		}
	}

	SetStartState(m_GameScenes[(int)SLGameScene::Title]);
}

void GameSceneManager::Update()
{
	while (m_NowState != m_NowState->GetNextState())
	{
		m_NowState = m_NowState->GetNextState();
		reinterpret_cast<GameScene*>(m_NowState)->ResetScene();
	};
}