#include "stdafx.h"

GameManager::GameManager()
{
	m_pGameSceneManager = new GameSceneManager();
}

GameManager::~GameManager()
{
}

void GameManager::Initialize()
{
	SetCollisionTable();

	/// 사운드 매니져 초기화
	SoundManager::Initialize();
	//SoundManager::SetVolumeEX(0.2f);
	SLDataManager->Initialize();
	m_pGameSceneManager->Initialize();
	SLDataManager->m_pMapManager->Initialize();
}

void GameManager::Update()
{
	// 사운드 업데이트
	SoundManager::Update();

	m_pGameSceneManager->Do();
	m_pGameSceneManager->Update();
}

void GameManager::Finalize()
{
	delete m_pGameSceneManager;
}

void GameManager::SetCollisionTable()
{
	MGSceneManager->SetLayerCollisionTable((int)SLLayer::Monster, (int)SLLayer::Monster, false);
	MGSceneManager->SetLayerCollisionTable((int)SLLayer::Monster, (int)SLLayer::Monster_Atk, false);

	MGSceneManager->SetLayerCollisionTable((int)SLLayer::Player, (int)SLLayer::Player_Atk, false);

	MGSceneManager->SetLayerCollisionTable((int)SLLayer::Monster_Atk, (int)SLLayer::Monster_Atk, false);
	MGSceneManager->SetLayerCollisionTable((int)SLLayer::Monster_Atk, (int)SLLayer::Player_Atk, false);
	MGSceneManager->SetLayerCollisionTable((int)SLLayer::Monster_Atk, (int)SLLayer::Water, false);

	MGSceneManager->SetLayerCollisionTable((int)SLLayer::Player_Atk, (int)SLLayer::Player_Atk, false);
	MGSceneManager->SetLayerCollisionTable((int)SLLayer::Player_Atk, (int)SLLayer::Water, false);

	MGSceneManager->SetLayerCollisionTable((int)SLLayer::Wall, (int)SLLayer::Wall, false);

	MGSceneManager->SetLayerCollisionTable((int)SLLayer::Water, (int)SLLayer::Water, false);
	MGSceneManager->SetLayerCollisionTable((int)SLLayer::Water, (int)SLLayer::Player_Atk, false);
	MGSceneManager->SetLayerCollisionTable((int)SLLayer::Water, (int)SLLayer::Monster_Atk, false);
}
