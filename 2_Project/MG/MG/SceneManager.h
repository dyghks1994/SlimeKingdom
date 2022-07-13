#pragma once
class SceneManager : public Manager<Scene>, public Singleton<SceneManager>
{
public:
	Scene* m_NowScene;		//���� Scene

public:
	int LayerCollisionTable[16];		//�浹 üũ ���̺�
	bool DrawCollider;
	bool Pause;

public:
	//Manager �ʱ�ȭ(��ӹ��� Ŭ�������� ���� �ʿ�)
	virtual void InitManager();
	//Manager ����(��ӹ��� Ŭ�������� ���� �ʿ�)
	virtual void UpdateManager();

	void Finalize();

	//���� Scene�� ����
	void ChangeNowScene(string scene_name);
	//Scene �߰�
	void AddScene(string scene_name);

	//���� Scene�� ��ȯ
	Scene* GetNowScene();
	//Scene �̸�����  Scene ������ �޾ƿ���
	Scene* GetScene(string scene_name);

	void RemoveGameObject(GameObject* gameobj);

	bool CheckLayerCollisionTabele(int sourcelayer, int targetlayer);

	void SetLayerCollisionTable(int sourcelayer, int targetlayer, bool check);
};

