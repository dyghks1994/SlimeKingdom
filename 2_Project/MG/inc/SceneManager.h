#pragma once
class SceneManager : public Manager<Scene>, public Singleton<SceneManager>
{
public:
	Scene* m_NowScene;		//현재 Scene

public:
	int LayerCollisionTable[16];		//충돌 체크 테이블
	bool DrawCollider;
	bool Pause;

public:
	//Manager 초기화(상속받은 클래스에서 정의 필요)
	virtual void InitManager();
	//Manager 갱신(상속받은 클래스에서 정의 필요)
	virtual void UpdateManager();

	void Finalize();

	//현재 Scene을 변경
	void ChangeNowScene(string scene_name);
	//Scene 추가
	void AddScene(string scene_name);

	//현재 Scene을 반환
	Scene* GetNowScene();
	//Scene 이름으로  Scene 포인터 받아오기
	Scene* GetScene(string scene_name);

	void RemoveGameObject(GameObject* gameobj);

	bool CheckLayerCollisionTabele(int sourcelayer, int targetlayer);

	void SetLayerCollisionTable(int sourcelayer, int targetlayer, bool check);
};

