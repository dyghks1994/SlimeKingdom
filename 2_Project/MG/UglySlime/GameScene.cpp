#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	AddScene();
	MGSceneManager->ChangeNowScene(m_SceneName);

	InitScene();
	//ResetScene();
}

void GameScene::AddConditions()
{
	if (m_Brenches.size() == 0) return;

	for (int i = 0; i < m_Brenches.size(); i++)
	{
		if (m_Brenches.at(i).second.size() == 0) continue;

		for (int j = 0; j < m_Brenches.at(i).second.size(); j++)
		{
			AddCondition(m_Brenches.at(i).first, m_Brenches.at(i).second.at(j));
		}
	}
}

void GameScene::Do()
{
	if (MGScene != MGSceneManager->GetScene(m_SceneName))
	{
		MGSceneManager->ChangeNowScene(m_SceneName);
		ResetScene();
	}

	DoScene();
}

void GameScene::ResetScene()
{
}

void GameScene::DoScene()
{
}

void GameScene::InitScene()
{
}

void GameScene::AddScene()
{
	MGSceneManager->AddScene(m_SceneName);
}

void GameScene::SetBrenches(State* scene, int scene_num)
{
	for (int i = 0; i < m_Conditions[scene_num].size(); i++)
	{
		m_Brenches.push_back(pair<State*, vector<Condition>>(scene, m_Conditions[scene_num]));
	}
}
