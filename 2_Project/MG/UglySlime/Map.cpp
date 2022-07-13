#include "stdafx.h"
#include "Map.h"

Map::Map()
{
	// Ÿ�� ���� ���� �ʱ�ȭ
	for (auto k : MapDatas)
	{
		k.reserve(144);
	}

	// ������Ʈ ���� ���� �ʱ�ȭ
	for (auto k : ObjectDatas)
	{
		k.reserve(144);
	}
}

void Map::Initialize()
{
	// ���� �� ����(Ÿ�� �Ӽ�) ���� 0���� �ʱ�ȭ �ص���
	for (auto k : WorldMap)
	{
		k = 0;
	}

	/// Ÿ�� �� ���� ����
	// MapDatas�� ������ �� ������ �ҷ� �´�.
	LoadMapDatas();

	// �ҷ��� �ʵ���Ÿ���� ������ ������� Ÿ���� �����Ѵ�.
	SetAttributeInWorld();


	/// ������Ʈ ���� ���� ����
	// ObjectDatas �� ������ ������Ʈ ������ �ҷ��´�.
	LoadObjectDatas();

	// �ҷ��� ������Ʈ �������� ������ ������ ������ �����Ѵ�.
	SetObjectSpawnMap();
}

void Map::LoadMapDatas()
{
	/// Json �� Ÿ�� �޾ƿ���  �ڵ�
	//0 ~ 11 �� ���� Ÿ�� ����Ÿ�� �ε��ؼ� �� index ���� vector�� �ִ´�

	// ���� �̸�
	string mapName[12];

	ifstream readMapFile;

	readMapFile.open("..\\resource\\JsonData\\MapData\\DataOrder.txt");    //���� ����

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
		readMapFile.close();    //���� �ݾ��ݴϴ�.
	}


	/// 0 ~ 11 �� �� ���ϵ��� ������ �ҷ��´�
	for (int i = 0; i < 12; i++)
	{
		/// 1���� �� ���� �� 16 * 9 = 144���� �����͸� �о��
		for (int j = 0; j < MapWidth * MapHeight; j++)
		{
			TileData* newTileData = new TileData();

			_JSONMANAGER->LoadDataFromJsonType(TILE_DATA_PATH, mapName[i], MapWidth * MapHeight,
				newTileData->_y,
				newTileData->_x,
				newTileData->_attribute);	// ������ ����ϴ� �Ӽ� ������

			MapDatas[i].push_back(newTileData);	// vector �� �߰��Ѵ�.
		}
	}
}

void Map::SetAttributeInWorld()
{
	// 0 ~ 11�� �� ���� �ֱ�
	for (int i = 0; i < 12; i++)
	{
		// �� ���� �����͸� ������ �ִ� ������ ������ġ�� iterator ����
		vector<TileData*>::iterator iter = MapDatas[i].begin();

		/// y ��ǥ ����
		/// y �� 9�� �ݺ�
		// 0,  1,  2 ���� y ��ġ�� 0  ~ 8
		// 3,  4,  5 ���� y ��ġ�� 9  ~ 17
		// 6,  7,  8 ���� y ��ġ�� 18 ~ 26
		// 9, 10, 11 ���� y ��ġ�� 27 ~ 35
		for (int y = i / 3 * MapHeight; y < (i / 3 * MapHeight) + 9; y++)
		{
			/// x�� 16�� �ݺ�
			for (int x = 0; x < MapWidth; x++)
			{
				// �� ��ȣ(i)�� ���� x ��ġ ����
				switch (i)
				{
					case 0:
					case 3:
					case 6:
					case 9:
					{
						// 0, 3, 6, 9 ������ x ��ġ�� 0 ~ 15
						WorldMap[y][x + MapWidth * 0] = (*iter)->_attribute;
						break;
					}

					case 1:
					case 4:
					case 7:
					case 10:
					{
						// 1, 4, 7, 10 ������ x ��ġ�� 16 ~ 31
						WorldMap[y][x + MapWidth * 1] = (*iter)->_attribute;
						break;
					}

					case 2:
					case 5:
					case 8:
					case 11:
					{
						// 2, 5, 8, 11 ������ x ��ġ�� 32 ~ 47
						WorldMap[y][x + MapWidth * 2] = (*iter)->_attribute;
						break;
					}
				}

				// ���� �����ͷ�~
				++iter;
			}
		}
	}
}

void Map::LoadObjectDatas()
{
	/// Json Ÿ�Ϻ� ������Ʈ ���� �޾ƿ���  �ڵ�
	//0 ~ 11 �� ������Ʈ ����Ÿ�� �ε��ؼ� �� index ���� vector�� �ִ´�

	// ���� �̸�
	string objectName[12];

	ifstream readObjectFile;

	readObjectFile.open("..\\resource\\JsonData\\ObjectData\\ObjectOrder.txt");    //���� ����

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
		readObjectFile.close();    //���� �ݾ��ݴϴ�.
	}


	/// 0 ~ 11 �� ������Ʈ ���ϵ��� ������ �ҷ��´�
	for (int i = 0; i < 12; i++)
	{
		/// 1���� �� ���� �� 16 * 9 = 144���� �����͸� �о��
		for (int j = 0; j < MapWidth * MapHeight; j++)
		{
			TileData* newTileData = new TileData();

			_JSONMANAGER->LoadDataFromJsonType(OBJECT_DATA_PATH, objectName[i], MapWidth * MapHeight,
				newTileData->_y,
				newTileData->_x,
				newTileData->_attribute);	// ������ ����ϴ� �Ӽ� ������

			ObjectDatas[i].push_back(newTileData);	// vector �� �߰��Ѵ�.
		}
	}
}

void Map::SetObjectSpawnMap()
{

	// 0 ~ 11�� �� ���� �ֱ�
	for (int i = 0; i < 12; i++)
	{
		// �� ������Ʈ�� �����͸� ������ �ִ� ������ ������ġ�� iterator ����
		vector<TileData*>::iterator iter = ObjectDatas[i].begin();

		/// y ��ǥ ����
		/// y �� 9�� �ݺ�
		// 0,  1,  2 ���� y ��ġ�� 0  ~ 8
		// 3,  4,  5 ���� y ��ġ�� 9  ~ 17
		// 6,  7,  8 ���� y ��ġ�� 18 ~ 26
		// 9, 10, 11 ���� y ��ġ�� 27 ~ 35
		for (int y = i / 3 * MapHeight; y < (i / 3 * MapHeight) + 9; y++)
		{
			/// x�� 16�� �ݺ�
			for (int x = 0; x < MapWidth; x++)
			{
				// �� ��ȣ(i)�� ���� x ��ġ ����
				switch (i)
				{
				case 0:
				case 3:
				case 6:
				case 9:
				{
					// 0, 3, 6, 9 ������ x ��ġ�� 0 ~ 15
					ObjectSpawnMap[y][x + MapWidth * 0] = (*iter)->_attribute;
					break;
				}

				case 1:
				case 4:
				case 7:
				case 10:
				{
					// 1, 4, 7, 10 ������ x ��ġ�� 16 ~ 31
					ObjectSpawnMap[y][x + MapWidth * 1] = (*iter)->_attribute;
					break;
				}

				case 2:
				case 5:
				case 8:
				case 11:
				{
					// 2, 5, 8, 11 ������ x ��ġ�� 32 ~ 47
					ObjectSpawnMap[y][x + MapWidth * 2] = (*iter)->_attribute;
					break;
				}
				}

				// ���� �����ͷ�~
				++iter;
			}
		}
	}


}

int Map::GetAttributeAtPos(const int x, const int y)
{
	/// ��ī��Ʈ(īƼ����) ��ǥ���������� (x,y) �� ���� WorldMap���� ���ؼ� ��ȯ�Ѵ�.
	/// ��ī��Ʈ(īƼ����) ��ǥ��� ����(x), ����(y), ��������
	/// C++ �迭�� ��켱�̶� ����� �����Ϸ��� (y,x)�� ������ ����Ѵ�
	return WorldMap[y][x];
}

