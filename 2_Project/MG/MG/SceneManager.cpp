#include "pch.h"
#include "SceneManager.h"

void SceneManager::InitManager()
{
	DrawCollider = false;
	Pause = false;

	m_NowScene = new Scene();
	ResistItem("Scene", m_NowScene);
	m_NowScene->Initialize();

	for (int i = 0; i < 16; i++)
	{
		LayerCollisionTable[i] = 0;
	}
}

void SceneManager::UpdateManager()
{
	m_NowScene->Update();
}

void SceneManager::Finalize()
{
	ResetItemList();
}

void SceneManager::ChangeNowScene(string scene_name)
{
	Scene* tempScene = m_ItemList.at(scene_name).second;
	if (tempScene != nullptr)
	{
		m_NowScene->SetActive(false);
		m_NowScene = tempScene;
		m_NowScene->SetActive(true);
	}
}

void SceneManager::AddScene(string scene_name)
{
	Scene* tempScene = new Scene();
	tempScene->Initialize();
	ResistItem(scene_name, tempScene);
}

Scene* SceneManager::GetNowScene()
{
	return m_NowScene;
}

Scene* SceneManager::GetScene(string scene_name)
{
	return m_ItemList.find(scene_name)->second.second;
}

void SceneManager::RemoveGameObject(GameObject* gameobj)
{
	for (auto scene : m_ItemList)
	{
		Scene* tempScene = scene.second.second;
		if (tempScene->FindGameObject(gameobj))
		{
			tempScene->RemoveGameObject(gameobj);
		}
	}
}

bool SceneManager::CheckLayerCollisionTabele(int sourcelayer, int targetlayer)
{
	return !(LayerCollisionTable[sourcelayer] & (1 << targetlayer));
}

void SceneManager::SetLayerCollisionTable(int sourcelayer, int targetlayer, bool check)
{
	if (sourcelayer < 0 && sourcelayer >= 16)		return;
	if (targetlayer < 0 && targetlayer >= 16)		return;

	int checkMask[2];

	checkMask[0] = (1 << targetlayer);
	checkMask[1] = (1 << sourcelayer);

	if (!check)
	{
		LayerCollisionTable[sourcelayer] |= checkMask[0];
		LayerCollisionTable[targetlayer] |= checkMask[1];
	}
	else
	{
		LayerCollisionTable[sourcelayer] &= checkMask[0];
		LayerCollisionTable[targetlayer] &= checkMask[1];
	}
}

