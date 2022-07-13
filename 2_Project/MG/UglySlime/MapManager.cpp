#include "stdafx.h"

void MapManager::Initialize()
{
	MGSceneManager->ChangeNowScene("InGameScene");

	m_MapData = new Map();
	m_MapData->Initialize();

	CreateMapTiles();
	CreateObjects();
}

void MapManager::CreateMapTiles()
{
	int width = m_MapData->WorldWidth;
	int height = m_MapData->WorldHeight;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int attribute = m_MapData->WorldMap[y][x];

			switch (attribute)
			{
			case (int)SLMapTile::Ground:
				break;

			case (int)SLMapTile::Wall:
			{
				if (CheckNearTile(x, y))
				{
					CreateMapTile(attribute, x, y);
				}
			}
			break;

			case (int)SLMapTile::Water:
			{
				CreateMapTile(attribute, x, y);
			}
			break;

			}
		}
	}
}

void MapManager::CreateMapTile(int attribute, int x, int y)
{
	Tile* tempTile = new Tile();
	tempTile->SetValue(attribute, x, y);
	int index = (x / 16) + (3 * (y / 9));
	m_MapSection[index].push_back(tempTile);
}

bool MapManager::CheckNearTile(int x, int y)
{
	////맨 아랫줄
	//if (CheckMapDataRange(x, y + 1) == false)
	//{
	//	return false;
	//}

	if (m_MapData->ObjectSpawnMap[y][x] == (int)SLObject::Wall_1
		|| m_MapData->ObjectSpawnMap[y][x] == (int)SLObject::Wall_2)
	{
		return false;
	}

	if (CheckMapDataRange(x, y - 1) && CheckMapDataRange(x, y + 1)
		&& m_MapData->WorldMap[y - 1][x] == (int)SLMapTile::Ground
		&& m_MapData->WorldMap[y + 1][x] == (int)SLMapTile::Wall)
	{
		return false;
	}

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0) continue;

			if (CheckMapDataRange(x + i, y + j)
				&& m_MapData->WorldMap[y + j][x + i] != (int)SLMapTile::Wall)
			{
				return true;
			}
		}
	}

	return false;
}

bool MapManager::CheckMapDataRange(int x, int y)
{
	return (x >= 0 && x < m_MapData->WorldWidth) && (y >= 0 && y < m_MapData->WorldHeight);
}

void MapManager::CreateObjects()
{
	int width = m_MapData->WorldWidth;
	int height = m_MapData->WorldHeight;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int objNum = m_MapData->ObjectSpawnMap[y][x];
			CreateObject(objNum, x, y);
		}
	}
}

void MapManager::SetObject(GameObject* obj, float x, float y, string name, bool is_sprite)
{
	obj = new GameObject();

	obj->m_pCollider->m_Size = { 120,120 };
	obj->m_Transform.Position.x = x;
	obj->m_Transform.Position.y = y;


	//스프라이트 세팅
	if (is_sprite)
	{
		obj->SetSprite(SLDataManager->GetSprite(name));
	}

	//애니메이션 세팅
	else
	{
	}
}

void MapManager::CreateObject(int objnum, int x, int y)
{
	GameObject* obj = nullptr;

	int index = (x / 16) + (3 * (y / 9));
	float posX = x * 120 + 60;
	float posY = y * 120 + 60;

	GameObject* player = nullptr;
	for (auto obj : MGScene->m_pGameObjectManager->m_ItemList)
	{
		if (obj.second.second->m_Layer == (int)SLLayer::Player)
		{
			player = obj.second.second;
			break;
		}
	}

	switch (objnum)
	{
	case (int)SLObject::Mon_Water:
	{
		Monster* mon = new Monster("Mon_Water", posX, posY, UnitAttribute::Water);
		reinterpret_cast<Monster*>(mon)->m_pPlayer = reinterpret_cast<Player*>(player);
		mon->m_pRenderer->m_Depth = (int)SLDepth::Object;
		m_MapMonster[index].push_back(mon);
	}
	return;

	case (int)SLObject::Mon_Fire:
	{
		Monster* mon = new Monster("Mon_Fire", posX, posY, UnitAttribute::Fire);
		reinterpret_cast<Monster*>(mon)->m_pPlayer = reinterpret_cast<Player*>(player);
		mon->m_pRenderer->m_Depth = (int)SLDepth::Object;
		m_MapMonster[index].push_back(mon);
	}
	return;

	case (int)SLObject::Mon_Grass:
	{
		Monster* mon = new Monster("Mon_Grass", posX, posY, UnitAttribute::Grass);
		reinterpret_cast<Monster*>(mon)->m_pPlayer = reinterpret_cast<Player*>(player);
		mon->m_pRenderer->m_Depth = (int)SLDepth::Object;
		m_MapMonster[index].push_back(mon);

	}
	return;

	case (int)SLObject::Box_Water:
	{
		obj = new Box(posX, posY, JewelryAttribute::Water, "box_lock");
	}
	break;

	case (int)SLObject::Box_Fire:
	{
		obj = new Box(posX, posY, JewelryAttribute::Fire, "box_lock");
	}
	break;

	case (int)SLObject::Box_Grass:
	{
		obj = new Box(posX, posY, JewelryAttribute::Grass, "box_lock");
	}
	break;

	case (int)SLObject::Bush:
	{
		obj = new Bush(posX, posY);
	}
	break;

	case (int)SLObject::Bush_Life:
	{
		obj = new Bush(posX, posY, true);
	}
	break;

	case (int)SLObject::Rock_Broken:
	{
		obj = new Rock(posX, posY);
	}
	break;

	case (int)SLObject::Tree_1:
	{
		obj = new Block(posX, posY, BlockType::Tree_1, "tree_1");
	}
	break;

	case (int)SLObject::Tree_2:
	{
		obj = new Block(posX, posY, BlockType::Tree_2, "tree_2");
	}
	break;
	case (int)SLObject::Rock_1:
	{
		obj = new Block(posX, posY, BlockType::Rock_1, "stone_none_3");
	}
	break;
	case (int)SLObject::Rock_2:
	{
		//obj = new Block(posX, posY, BlockType::Rock_2, "stone_none_2");	// 원래 쓸려고 했으나 안쓴다고 함...
	}
	break;
	case (int)SLObject::Wall_1:
	{
		obj = new Block(posX, posY, BlockType::Wall_1, "wall_1");
	}
	break;
	case (int)SLObject::Wall_2:
	{
		obj = new Block(posX, posY, BlockType::Wall_2, "wall_2");
	}
	break;
	case (int)SLObject::Sign_1:
	{
		obj = new Sign(posX, posY, "sign_1");
	}
	break;
	case (int)SLObject::Sign_2:
	{
		obj = new Sign(posX, posY, "sign_2");
	}
	break;
	case (int)SLObject::Sign_3:
	{
		obj = new Sign(posX, posY, "sign_3");
	}
	break;
	case (int)SLObject::Sign_4:
	{
		obj = new Sign(posX, posY, "sign_4");
	}
	break;
	case (int)SLObject::Sign_5:
	{
		obj = new Sign(posX, posY, "sign_5");
	}
	break;
	case (int)SLObject::Statue_Water:
	{
		obj = new Statue(posX, posY, StatueType::Water, "statue_water_off");
	}
	break;
	case (int)SLObject::Statue_Fire:
	{
		obj = new Statue(posX, posY, StatueType::Fire, "statue_fire_off");
	}
	break;
	case (int)SLObject::Statue_Grass:
	{
		obj = new Statue(posX, posY, StatueType::Grass, "statue_leaf_off");
	}
	break;
	case (int)SLObject::Statue_King:
	{
		obj = new Statue(posX, posY, StatueType::King, "statue_king_off");
	}
	break;
	case (int)SLObject::Switch_A_1:
	{
		obj = new Switch(posX, posY, "switch_1_off");
	}
	break;
	case (int)SLObject::Switch_B_1:
	{
		obj = new Door(posX, posY, "door_1_closed");
	}
	break;
	case (int)SLObject::Switch_A_2:
	{
		obj = new Switch(posX, posY, "switch_2_off");
	}
	break;
	case (int)SLObject::Switch_B_2:
	{
		obj = new Door(posX, posY, "door_2_closed");
	}
	break;
	case (int)SLObject::Switch_A_3:
	{
		obj = new Switch(posX, posY, "switch_3_off");
	}
	break;
	case (int)SLObject::Switch_B_3:
	{
		obj = new Door(posX, posY, "door_3_closed");
	}
	break;
	case (int)SLObject::Switch_A_4:
	{
		obj = new Switch(posX, posY, "switch_4_off");
	}
	break;
	case (int)SLObject::Switch_B_4:
	{
		obj = new Door(posX, posY, "door_4_closed");
	}
	break;
	case (int)SLObject::Switch_A_5:
	{
		obj = new Switch(posX, posY, "switch_5_off");
	}
	break;
	case (int)SLObject::Switch_B_5:
	{
		obj = new Door(posX, posY, "door_5_closed");
	}
	break;
	case (int)SLObject::Goal:
	{
		obj = new Block(posX, posY, BlockType::Goal, "shining_starting_point");
		obj->SetLayer((int)SLLayer::Object);
		m_MapObject[index].push_back(obj);
		return;
	}
	break;
	default:
		break;
	}


	if (obj != nullptr)
	{
		obj->m_pRenderer->m_Depth = (int)SLDepth::Object;
		obj->SetLayer((int)SLLayer::Object);
		m_MapObject[index].push_back(obj);
	}
}

void MapManager::SwitchingSection(int section_num)
{
	for (int i = 0; i < 12; i++)
	{
		if (i == section_num)
		{
			SectionColliderSet(i, true);
			for (int obj = 0; obj < m_MapMonster[i].size(); obj++)
			{
				m_MapMonster[i].at(obj)->m_Active = true;
			}
			CameraMove((i % 3) * 16 * 120, (i / 3) * 9 * 120);

			switch (i % 3)
			{
			case 0:
			{
				SectionColliderSet(i - 3, true);
				SectionColliderSet(i + 1, true);
				SectionColliderSet(i + 3, true);
			}
			break;

			case 1:
			{
				SectionColliderSet(i - 3, true);
				SectionColliderSet(i - 1, true);
				SectionColliderSet(i + 1, true);
				SectionColliderSet(i + 3, true);
			}
			break;

			case 2:
			{
				SectionColliderSet(i - 3, true);
				SectionColliderSet(i - 1, true);
				SectionColliderSet(i + 3, true);
			}
			break;
			}
		}
		else
		{
			SectionColliderSet(i, false);
			for (int obj = 0; obj < m_MapMonster[i].size(); obj++)
			{
				m_MapMonster[i].at(obj)->m_Active = false;
			}
		}
	}


}

void MapManager::SectionColliderSet(int section_num, bool set)
{
	if (section_num < 0 || section_num >= 12) return;

	for (int j = 0; j < m_MapSection[section_num].size(); j++)
	{
		m_MapSection[section_num].at(j)->m_pCollider->m_Active = set;
	}

	for (int obj = 0; obj < m_MapObject[section_num].size(); obj++)
	{
		m_MapObject[section_num].at(obj)->m_Active = set;
	}
}

void MapManager::CameraMove(float TargetX, float TargetY)
{
	MGCamera->Move(TargetX, TargetY);
}

void MapManager::ResetMonsters()
{
	for (auto sec : m_MapMonster)
	{
		for (auto mon : sec)
		{
			mon->Reset();
		}
	}
}
