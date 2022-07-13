#pragma once

/// Map 클래스
/// Json Data를 불러와서 초기화 하자
/// 맵은 모든 유닛이나 오브젝들이 알고 있어야 하고
/// 1개 만 있으면 되니까 싱글톤으로 만들어보자
/// 
/// 맵툴로 만든 각각의 Json 데이타(16 * 9)를 하나의 맵(구역)으로 보고
/// 그 맵들이 모인 3 * 4 의 전체를 월드 정도로 생각해 보자
/// 
/// 최요환
/// 2021.02.20
/// 

// 맵 파일 패스
#define TILE_DATA_PATH   "../resource/JsonData/MapData"		// 타일 경로
#define OBJECT_DATA_PATH "../resource/JsonData/ObjectData"	// 오브젝트 스폰 경로

/// Json 맵 타일 불러올 임시 구조체
struct TileData
{
	int _y, _x, _attribute;
};

// 타일과 오브젝트 모두 데이타 형식은 같으니까..
typedef TileData ObjectData;

class Map
{
public:
	// 생성자
	Map();

public:
	// 타일 하나의 사이즈 ( 120px * 120px)
	static const int TileSize = 120;

	// 1개의 맵당 가로 16 * 세로 9
	static const int MapWidth = 16;
	static const int MapHeight = 9;

	// 전체 월드맵은 맵이 3 * 4 = 12로 구성
	static const int WorldWidth	 = MapWidth  * 3;
	static const int WorldHeight = MapHeight * 4;

	// 월드 맵(속성만 필요)
	int WorldMap[WorldHeight][WorldWidth];

	// 초기 배치(스폰) 위치 정보
	int ObjectSpawnMap[WorldHeight][WorldWidth];	// 이 정보가 게임 시작시에 각 오브젝트의 시작 위치가 된다.

	// 위치 별 스폰 오브젝트 목록

	// 맵 초기화
	void Initialize();

	/// 맵 데이터
	// JsonData에서 맵 데이터들 불러오기
	void LoadMapDatas();

	// 월드맵에 속성값을 세팅한다.(먼저 맵 데이타들이 있어야함)
	void SetAttributeInWorld();
	///

	/// 오브젝트 데이터
	// JsonData에서 오브젝트 데이터들 불러오기
	void LoadObjectDatas();

	// 오브젝트의 배치(스폰)위치 합치기
	void SetObjectSpawnMap();	
	///

	// 데카르트(카티지안) 좌표계로 점(x, y)에 해당하는 위치의 속성값을 얻어온다.
	int GetAttributeAtPos(const int x, const int y);

	/// Json 타일 맵 불러올 벡터
	vector<TileData*> MapDatas[12];			// 0 ~ 11 번 맵의 타일 정보를 받을 백터
	vector<ObjectData*> ObjectDatas[12];	// 0 ~ 11 번 오브젝트들의 위치 정보를 받을 벡터

protected:

private:

};

