#include "pch.h"
#include "Scene.h"

Scene::Scene()
{
	m_pGameObjectManager = new GameObjectManager();
	m_pUIManager = new UIManager();
	m_pCameraManager = new CameraManager();
}

void Scene::Initialize()
{
	m_pGameObjectManager->InitManager();
	m_pUIManager->InitManager();
	m_pCameraManager->InitManager();
}

void Scene::prevUpdate()
{
	m_pGameObjectManager->prevUpdate();
}

void Scene::Update()
{
	if (!MGSceneManager->Pause)
	{
		m_pGameObjectManager->UpdateManager();
		m_pUIManager->UpdateManager();
		m_pCameraManager->UpdateManager();
	}
}

void Scene::Draw()
{
	MGGraphicEngine->BeginRender();
	m_pGameObjectManager->Draw();
	m_pUIManager->Draw();
	MGGraphicEngine->EndRender();
}

void Scene::SetActive(bool active)
{
	m_pGameObjectManager->SetActive(active);
	m_pUIManager->SetActive(active);
}

Camera* Scene::GetNowCamera()
{
	return m_pCameraManager->GetNowCamera();
}

void Scene::AddCamera(string camera_name)
{
	m_pCameraManager->AddCamera(camera_name);
}

void Scene::ResistGameObject(string name, GameObject* gameobject)
{
	m_pGameObjectManager->ResistItem(name, gameobject);
}

void Scene::ResistCamera(string name, Camera* camera)
{
	m_pCameraManager->ResistItem(name, camera);
}

void Scene::ResistUI(string name, UI* ui)
{
	m_pUIManager->ResistItem(name, ui);
}

bool Scene::FindGameObject(GameObject* gameobj)
{
	return m_pGameObjectManager->FindGameObject(gameobj);
}

void Scene::RemoveGameObject(GameObject* gameobj)
{
	m_pGameObjectManager->RemoveItem(gameobj);
}