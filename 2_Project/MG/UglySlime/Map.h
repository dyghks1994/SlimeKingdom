#pragma once

/// Map Ŭ����
/// Json Data�� �ҷ��ͼ� �ʱ�ȭ ����
/// ���� ��� �����̳� ���������� �˰� �־�� �ϰ�
/// 1�� �� ������ �Ǵϱ� �̱������� ������
/// 
/// ������ ���� ������ Json ����Ÿ(16 * 9)�� �ϳ��� ��(����)���� ����
/// �� �ʵ��� ���� 3 * 4 �� ��ü�� ���� ������ ������ ����
/// 
/// �ֿ�ȯ
/// 2021.02.20
/// 

// �� ���� �н�
#define TILE_DATA_PATH   "../resource/JsonData/MapData"		// Ÿ�� ���
#define OBJECT_DATA_PATH "../resource/JsonData/ObjectData"	// ������Ʈ ���� ���

/// Json �� Ÿ�� �ҷ��� �ӽ� ����ü
struct TileData
{
	int _y, _x, _attribute;
};

// Ÿ�ϰ� ������Ʈ ��� ����Ÿ ������ �����ϱ�..
typedef TileData ObjectData;

class Map
{
public:
	// ������
	Map();

public:
	// Ÿ�� �ϳ��� ������ ( 120px * 120px)
	static const int TileSize = 120;

	// 1���� �ʴ� ���� 16 * ���� 9
	static const int MapWidth = 16;
	static const int MapHeight = 9;

	// ��ü ������� ���� 3 * 4 = 12�� ����
	static const int WorldWidth	 = MapWidth  * 3;
	static const int WorldHeight = MapHeight * 4;

	// ���� ��(�Ӽ��� �ʿ�)
	int WorldMap[WorldHeight][WorldWidth];

	// �ʱ� ��ġ(����) ��ġ ����
	int ObjectSpawnMap[WorldHeight][WorldWidth];	// �� ������ ���� ���۽ÿ� �� ������Ʈ�� ���� ��ġ�� �ȴ�.

	// ��ġ �� ���� ������Ʈ ���

	// �� �ʱ�ȭ
	void Initialize();

	/// �� ������
	// JsonData���� �� �����͵� �ҷ�����
	void LoadMapDatas();

	// ����ʿ� �Ӽ����� �����Ѵ�.(���� �� ����Ÿ���� �־����)
	void SetAttributeInWorld();
	///

	/// ������Ʈ ������
	// JsonData���� ������Ʈ �����͵� �ҷ�����
	void LoadObjectDatas();

	// ������Ʈ�� ��ġ(����)��ġ ��ġ��
	void SetObjectSpawnMap();	
	///

	// ��ī��Ʈ(īƼ����) ��ǥ��� ��(x, y)�� �ش��ϴ� ��ġ�� �Ӽ����� ���´�.
	int GetAttributeAtPos(const int x, const int y);

	/// Json Ÿ�� �� �ҷ��� ����
	vector<TileData*> MapDatas[12];			// 0 ~ 11 �� ���� Ÿ�� ������ ���� ����
	vector<ObjectData*> ObjectDatas[12];	// 0 ~ 11 �� ������Ʈ���� ��ġ ������ ���� ����

protected:

private:

};

