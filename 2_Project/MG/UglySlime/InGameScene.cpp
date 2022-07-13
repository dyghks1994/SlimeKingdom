#include "stdafx.h"
#include "InGameScene.h"

InGameScene::InGameScene(string name)
{
	m_SceneName = name;
}

InGameScene::~InGameScene()
{

}

void InGameScene::ResetScene()
{
	m_Ending = false;
	m_Player->m_Transform.Position.x = 2820;
	m_Player->m_Transform.Position.y = 1840;
	m_Player->Reset();

	MGCamera->m_Transform.Position = { 1920, 1080 };

	int x = m_Player->m_Transform.Position.x / (120 * 16);
	int y = m_Player->m_Transform.Position.y / (120 * 9);
	SLDataManager->m_pMapManager->SwitchingSection(x + (y * 3));

	SLDataManager->m_pMapManager->ResetMonsters();

	m_Manual->m_Visible = true;

	SoundManager::PlayBGM("InGame");
}

void InGameScene::InitScene()
{
	m_Conditions[(int)SLGameScene::GameEnding].push_back([this]()->bool { return m_Ending; });
	m_Conditions[(int)SLGameScene::GameOver].push_back([this]()->bool { return (m_Player->GetCurrentHp() < 0) && (m_Player->GetLife() <= 0); });
	//SetPlayerAnimator();

	m_BG = new GameObject("BackGround");
	m_BG->SetSprite(SLDataManager->GetSprite("total_map_tile_v.0.3"));
	m_BG->m_pCollider->m_Active = false;

	m_BG->m_pRenderer->m_Depth = -1;

	m_BG->m_Transform.Position.x = m_BG->m_pRenderer->GetSprite()->m_pBitmap->GetSize().width * 0.5f;
	m_BG->m_Transform.Position.y = m_BG->m_pRenderer->GetSprite()->m_pBitmap->GetSize().height * 0.5f;

	m_Player = new Player();

	m_Manual = new ImageUI();
	m_Manual->SetSprite(SLDataManager->GetSprite("ui_manual"));
	m_Manual->m_Depth = 100;
	m_Manual->m_Transform.Position.x = 960;
	m_Manual->m_Transform.Position.y = 540;
}

void InGameScene::DoScene()
{
	if (m_Manual->m_Visible)
	{
		for (int i = 0; i < 256; i++)
		{
			if (KeyInput->InputKeyDown(i))
			{
				m_Manual->m_Visible = false;
				break;
			}
		}
	}

	if (KeyInput->InputKeyDown(VK_F5))
	{
		MGSceneManager->DrawCollider = !MGSceneManager->DrawCollider;
	}
	if (KeyInput->InputKeyDown(VK_ESCAPE))
	{
		MGSceneManager->Pause = false;
	}
	if (KeyInput->InputKeyDown(VK_F10) ||
		m_Player->IsGameClear())
	{
		m_Ending = true;
	}

	int x = m_Player->m_Transform.Position.x / (120 * 16);
	int y = m_Player->m_Transform.Position.y / (120 * 9);
	SLDataManager->m_pMapManager->SwitchingSection(x + (y * 3));


}