#include "stdafx.h"
#include "Block.h"

Block::Block(float spawnPosX, float spawnPosY, BlockType type, string name)
	: Gimmick(name)
{
	m_Type = static_cast<BlockType>(type);
	m_Tag = name;

	// 배치(활성화)상태로 설정
	m_Active = true;
	m_Visible = true;

	switch (type)
	{
	// 벽1 설정
	case BlockType::Wall_1:
	{
		// 벽의 콜라이더 사이즈 만큼 설정해주자
		m_pCollider->SetSize({ 120.0f, 100.0f });
		m_pCollider->m_Transform.Position.y = 5.0f;
	}
		break;

	// 벽2 설정
	case BlockType::Wall_2:
	{
		// 벽의 콜라이더 사이즈 만큼 설정해주자
		m_pCollider->SetSize({ 120.0f, 100.0f });
		m_pCollider->m_Transform.Position.y = 5.0f;
	}
		break;

	// 나무 1 설정
	case BlockType::Tree_1:
	{
		// 나무1의 콜라이더 사이즈 만큼 설정해주자
		m_pCollider->SetSize({ 100.0f, 70.0f });

		m_pCollider->m_Transform.Position.y = 15.0f;
	}
		break;

	// 나무 2 설정
	case BlockType::Tree_2:
	{
		// 나무2의 콜라이더 사이즈 만큼 설정해주자
		m_pCollider->SetSize({ 100.0f, 70.0f });

		m_pCollider->m_Transform.Position.y = 15.0f;
	}
		break;

	// 바위 1 설정
	case BlockType::Rock_1:
	{
		// 벽의 콜라이더 사이즈 만큼 설정해주자
		m_pCollider->SetSize({ 120.0f, 120.0f });
	}
		break;

	// 골인지점 설정
	case BlockType::Goal:
	{
		// 처음에는 비활성화 해둔다.
		m_pCollider->m_IsTrigger = true;
		m_Transform.Position.x += spawnPosX;
		m_Transform.Position.y += spawnPosY;
		SetSprite(SLDataManager->GetSprite("starting_ani_sprite_0"));
	}
		return;
	default:
		break;
	}

	// 스폰 포인트에 위치시킨다
	m_Transform.Position.x += spawnPosX;
	m_Transform.Position.y += spawnPosY;


	SetSprite(SLDataManager->GetSprite(name));
}

Block::~Block()
{
}
