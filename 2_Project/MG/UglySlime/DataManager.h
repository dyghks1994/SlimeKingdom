#pragma once
class DataManager : public Singleton<DataManager>
{
public:
	SpriteManager* m_pSpriteManager;
	MapManager* m_pMapManager;

public:
	virtual void Initialize();

	Sprite* GetSprite(string name);
	Animation* GetAnimation(string name);
};

