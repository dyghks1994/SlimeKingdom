#pragma once
class MapManager
{
public:
	void Initialize();

public:
	vector<Tile*> m_MapSection[12];
	vector<GameObject*> m_MapObject[12];
	vector<Monster*> m_MapMonster[12];

public:
	void CreateMapTiles();
	void CreateMapTile(int attribute, int x, int y);
	bool CheckNearTile(int x, int y);
	bool CheckMapDataRange(int x, int y);

	void CreateObjects();
	void SetObject(GameObject* obj, float x, float y, string name, bool is_sprite=false);
	void CreateObject(int objnum, int x, int y);

	void SwitchingSection(int section_num);
	void SectionColliderSet(int section_num, bool set);
	void CameraMove(float TargetX, float TargetY);

	void ResetMonsters();
private:
	Map* m_MapData;
};

