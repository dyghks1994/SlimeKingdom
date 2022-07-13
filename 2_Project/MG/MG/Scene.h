#pragma once
class Scene
{
public:
	Scene();

public:
	GameObjectManager* m_pGameObjectManager;
	UIManager* m_pUIManager;
	CameraManager* m_pCameraManager;

public:
	void Initialize();
	void prevUpdate();
	void Update();
	void Draw();

	void SetActive(bool active);

	Camera* GetNowCamera();
	void AddCamera(string camera_name = "Camera");

	void ResistGameObject(string name, GameObject* gameobject);
	void ResistCamera(string name, Camera* camera);
	void ResistUI(string name, UI* ui);

	bool FindGameObject(GameObject* gameobj);
	void RemoveGameObject(GameObject* gameobj);
};