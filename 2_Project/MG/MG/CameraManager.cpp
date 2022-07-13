#include "pch.h"
#include "CameraManager.h"

void CameraManager::InitManager()
{
	m_NowCamera = new Camera("main");
}

void CameraManager::UpdateManager()
{
	m_NowCamera->Update();
}

void CameraManager::ChangeNowCamera(string camera_name)
{
	for (auto iter = m_ItemList.begin(); iter != m_ItemList.end(); iter++)
	{
		if (iter->first == camera_name)
		{
			m_NowCamera = iter->second.second;
			return;
		}
	}
}

void CameraManager::ChangeNowCamera(Camera* camera)
{
	for (auto iter = m_ItemList.begin(); iter != m_ItemList.end(); iter++)
	{
		if (iter->second.second == camera)
		{
			m_NowCamera = iter->second.second;
			return;
		}
	}
}

void CameraManager::AddCamera(string camera_name)
{
	Camera* tempCamera = new Camera(camera_name);
}

Camera* CameraManager::GetNowCamera()
{
	return m_NowCamera;
}

Camera* CameraManager::GetCamera(string camera_name)
{
	for (auto iter = m_ItemList.begin(); iter != m_ItemList.end(); iter++)
	{
		if (iter->first == camera_name)
		{
			return iter->second.second;
		}
	}

	return nullptr;
}
