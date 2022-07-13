#pragma once
class GameObjectManager : public Manager<GameObject>
{
public:
	//Manager �ʱ�ȭ(��ӹ��� Ŭ�������� ���� �ʿ�)
	virtual void InitManager();
	//Manager ����(��ӹ��� Ŭ�������� ���� �ʿ�)
	virtual void UpdateManager();

	void Draw();

	void CheckCollision();

	bool FindGameObject(GameObject* gameobj);

	GameObject* FindGameObject(const string tag);

	void prevUpdate();

	void SetActive(bool active);
};

