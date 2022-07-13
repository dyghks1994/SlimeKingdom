#include "stdafx.h"
#include "DataManager.h"

void DataManager::Initialize()
{
	m_pSpriteManager = new SpriteManager();
	m_pMapManager = new MapManager();

	m_pSpriteManager->LoadAll();
}

Sprite* DataManager::GetSprite(string name)
{
	return m_pSpriteManager->GetSprite(name);
}

Animation* DataManager::GetAnimation(string name)
{
	return m_pSpriteManager->GetAnimation(name);
}