#include "stdafx.h"
#include "Tile.h"

Tile::Tile(float size)
{
	m_pCollider->m_Size = { size, size };
	m_pRenderer->m_Depth = (int)SLDepth::Tile;
}

Tile::~Tile()
{
}


void Tile::SetValue(int attribute, int x, int y, bool typecheck)
{
	float width = m_pCollider->m_Size.width;
	float height = m_pCollider->m_Size.height;

	m_Transform.Position.x = x * width + width * 0.5f;
	m_Transform.Position.y = y * height + height * 0.5f;

	switch (attribute)
	{
	case (int)SLMapTile::Wall:
	{
		SetLayer((int)SLLayer::Wall);
		//SetSprite(SLDataManager->GetSprite("monster_grass_idle_0"));
	}
	break;

	case (int)SLMapTile::Water:
	{
		SetLayer((int)SLLayer::Water);
		//SetSprite(SLDataManager->GetSprite("monster_water_idle_0"));
	}
	break;
	}
}