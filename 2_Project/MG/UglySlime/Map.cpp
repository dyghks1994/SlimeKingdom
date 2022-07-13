#include "stdafx.h"
#include "Map.h"

Map::Map()
{
	// 타일 정보 벡터 초기화
	for (auto k : MapDatas)
	{
		k.reserve(144);
	}

	// 오브젝트 정보 벡터 초기화
	for (auto k : ObjectDatas)
	{
		k.reserve(144);
	}
}

void Map::Initialize()
{
	// 먼저 각 영역(타일 속성) 값을 0으로 초기화 해두자
	for (auto k : WorldMap)
	{
		k = 0;
	}

	/// 타일 맵 정보 세팅
	// MapDatas에 각각의 맵 파일을 불러 온다.
	LoadMapDatas();

	// 불러온 맵데이타들의 정보로 월드맵의 타일을 세팅한다.
	SetAttributeInWorld();


	/// 오브젝트 스폰 정보 세팅
	// ObjectDatas 에 각각의 오브젝트 파일을 불러온다.
	LoadObjectDatas();

	// 불러온 오브젝트 데이터의 정보로 스폰맵 정보를 세팅한다.
	SetObjectSpawnMap();
}

void Map::LoadMapDatas()
{
	/// Json 맵 타일 받아오는  코드
	//0 ~ 11 번 맵의 타일 데이타를 로드해서 각 index 번의 vector에 넣는다

	// 파일 이름
	string mapName[12];

	ifstream readMapFile;

	readMapFile.open("..\\resource\\JsonData\\MapData\\DataOrder.txt");    //파일 열기

	if (readMapFile.is_open())
	{
		while (!readMapFile.eof())
		{
			string str_line;
			getline(readMapFile, str_line);
			istringstream ss(str_line);

			int order;
			string name;

			ss >> order;
			ss >> name;

			mapName[order - 1] = name;
		}
		readMapFile.close();    //파일 닫아줍니다.
	}


	/// 0 ~ 11 번 맵 파일들의 정보를 불러온다
	for (int i = 0; i < 12; i++)
	{
		/// 1개의 맵 파일 당 16 * 9 = 144개의 데이터를 읽어옴
		for (int j = 0; j < MapWidth * MapHeight; j++)
		{
			TileData* newTileData = new TileData();

			_JSONMANAGER->LoadDataFromJsonType(TILE_DATA_PATH, mapName[i], MapWidth * MapHeight,
				newTileData->_y,
				newTileData->_x,
				newTileData->_attribute);	// 실제로 사용하는 속성 데이터

			MapDatas[i].push_back(newTileData);	// vector 에 추가한다.
		}
	}
}

void Map::SetAttributeInWorld()
{
	// 0 ~ 11번 맵 정보 넣기
	for (int i = 0; i < 12; i++)
	{
		// 각 맵의 데이터를 가지고 있는 벡터의 시작위치로 iterator 설정
		vector<TileData*>::iterator iter = MapDatas[i].begin();

		/// y 좌표 설정
		/// y 는 9번 반복
		// 0,  1,  2 맵의 y 위치는 0  ~ 8
		// 3,  4,  5 맵의 y 위치는 9  ~ 17
		// 6,  7,  8 맵의 y 위치는 18 ~ 26
		// 9, 10, 11 맵의 y 위치는 27 ~ 35
		for (int y = i / 3 * MapHeight; y < (i / 3 * MapHeight) + 9; y++)
		{
			/// x는 16번 반복
			for (int x = 0; x < MapWidth; x++)
			{
				// 맵 번호(i)에 따라서 x 위치 보정
				switch (i)
				{
					case 0:
					case 3:
					case 6:
					case 9:
					{
						// 0, 3, 6, 9 번맵의 x 위치는 0 ~ 15
						WorldMap[y][x + MapWidth * 0] = (*iter)->_attribute;
						break;
					}

					case 1:
					case 4:
					case 7:
					case 10:
					{
						// 1, 4, 7, 10 번맵의 x 위치는 16 ~ 31
						WorldMap[y][x + MapWidth * 1] = (*iter)->_attribute;
						break;
					}

					case 2:
					case 5:
					case 8:
					case 11:
					{
						// 2, 5, 8, 11 번맵의 x 위치는 32 ~ 47
						WorldMap[y][x + MapWidth * 2] = (*iter)->_attribute;
						break;
					}
				}

				// 다음 데이터로~
				++iter;
			}
		}
	}
}

void Map::LoadObjectDatas()
{
	/// Json 타일별 오브젝트 정보 받아오는  코드
	//0 ~ 11 번 오브젝트 데이타를 로드해서 각 index 번의 vector에 넣는다

	// 파일 이름
	string objectName[12];

	ifstream readObjectFile;

	readObjectFile.open("..\\resource\\JsonData\\ObjectData\\ObjectOrder.txt");    //파일 열기

	if (readObjectFile.is_open())
	{
		while (!readObjectFile.eof())
		{
			string str_line;
			getline(readObjectFile, str_line);
			istringstream ss(str_line);

			int order;
			string name;

			ss >> order;
			ss >> name;

			objectName[order - 1] = name;
		}
		readObjectFile.close();    //파일 닫아줍니다.
	}


	/// 0 ~ 11 번 오브젝트 파일들의 정보를 불러온다
	for (int i = 0; i < 12; i++)
	{
		/// 1개의 맵 파일 당 16 * 9 = 144개의 데이터를 읽어옴
		for (int j = 0; j < MapWidth * MapHeight; j++)
		{
			TileData* newTileData = new TileData();

			_JSONMANAGER->LoadDataFromJsonType(OBJECT_DATA_PATH, objectName[i], MapWidth * MapHeight,
				newTileData->_y,
				newTileData->_x,
				newTileData->_attribute);	// 실제로 사용하는 속성 데이터

			ObjectDatas[i].push_back(newTileData);	// vector 에 추가한다.
		}
	}
}

void Map::SetObjectSpawnMap()
{

	// 0 ~ 11번 맵 정보 넣기
	for (int i = 0; i < 12; i++)
	{
		// 각 오브젝트의 데이터를 가지고 있는 벡터의 시작위치로 iterator 설정
		vector<TileData*>::iterator iter = ObjectDatas[i].begin();

		/// y 좌표 설정
		/// y 는 9번 반복
		// 0,  1,  2 맵의 y 위치는 0  ~ 8
		// 3,  4,  5 맵의 y 위치는 9  ~ 17
		// 6,  7,  8 맵의 y 위치는 18 ~ 26
		// 9, 10, 11 맵의 y 위치는 27 ~ 35
		for (int y = i / 3 * MapHeight; y < (i / 3 * MapHeight) + 9; y++)
		{
			/// x는 16번 반복
			for (int x = 0; x < MapWidth; x++)
			{
				// 맵 번호(i)에 따라서 x 위치 보정
				switch (i)
				{
				case 0:
				case 3:
				case 6:
				case 9:
				{
					// 0, 3, 6, 9 번맵의 x 위치는 0 ~ 15
					ObjectSpawnMap[y][x + MapWidth * 0] = (*iter)->_attribute;
					break;
				}

				case 1:
				case 4:
				case 7:
				case 10:
				{
					// 1, 4, 7, 10 번맵의 x 위치는 16 ~ 31
					ObjectSpawnMap[y][x + MapWidth * 1] = (*iter)->_attribute;
					break;
				}

				case 2:
				case 5:
				case 8:
				case 11:
				{
					// 2, 5, 8, 11 번맵의 x 위치는 32 ~ 47
					ObjectSpawnMap[y][x + MapWidth * 2] = (*iter)->_attribute;
					break;
				}
				}

				// 다음 데이터로~
				++iter;
			}
		}
	}


}

int Map::GetAttributeAtPos(const int x, const int y)
{
	/// 데카르트(카티지안) 좌표공간에서의 (x,y) 의 값을 WorldMap에서 구해서 반환한다.
	/// 데카르트(카티지안) 좌표계는 가로(x), 세로(y), 순이지만
	/// C++ 배열은 행우선이라 제대로 매핑하려면 (y,x)로 뒤집어 줘야한다
	return WorldMap[y][x];
}

