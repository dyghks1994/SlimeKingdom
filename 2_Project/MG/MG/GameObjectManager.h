#pragma once
class GameObjectManager : public Manager<GameObject>
{
public:
	//Manager 초기화(상속받은 클래스에서 정의 필요)
	virtual void InitManager();
	//Manager 갱신(상속받은 클래스에서 정의 필요)
	virtual void UpdateManager();

	void Draw();

	void CheckCollision();

	bool FindGameObject(GameObject* gameobj);

	GameObject* FindGameObject(const string tag);

	void prevUpdate();

	void SetActive(bool active);
};

