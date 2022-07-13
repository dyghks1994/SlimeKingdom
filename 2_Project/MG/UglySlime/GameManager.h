#pragma once

class GameManager : public Singleton<GameManager>
{
public:
	GameManager();
	~GameManager();

public:
	void Initialize();
	void Update();
	void Finalize();

	void SetCollisionTable();

private:
	GameSceneManager* m_pGameSceneManager;
};

