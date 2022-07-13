#include "stdafx.h"
#include "Block.h"

Block::Block(float spawnPosX, float spawnPosY, BlockType type, string name)
	: Gimmick(name)
{
	m_Type = static_cast<BlockType>(type);
	m_Tag = name;

	// ��ġ(Ȱ��ȭ)���·� ����
	m_Active = true;
	m_Visible = true;

	switch (type)
	{
	// ��1 ����
	case BlockType::Wall_1:
	{
		// ���� �ݶ��̴� ������ ��ŭ ����������
		m_pCollider->SetSize({ 120.0f, 100.0f });
		m_pCollider->m_Transform.Position.y = 5.0f;
	}
		break;

	// ��2 ����
	case BlockType::Wall_2:
	{
		// ���� �ݶ��̴� ������ ��ŭ ����������
		m_pCollider->SetSize({ 120.0f, 100.0f });
		m_pCollider->m_Transform.Position.y = 5.0f;
	}
		break;

	// ���� 1 ����
	case BlockType::Tree_1:
	{
		// ����1�� �ݶ��̴� ������ ��ŭ ����������
		m_pCollider->SetSize({ 100.0f, 70.0f });

		m_pCollider->m_Transform.Position.y = 15.0f;
	}
		break;

	// ���� 2 ����
	case BlockType::Tree_2:
	{
		// ����2�� �ݶ��̴� ������ ��ŭ ����������
		m_pCollider->SetSize({ 100.0f, 70.0f });

		m_pCollider->m_Transform.Position.y = 15.0f;
	}
		break;

	// ���� 1 ����
	case BlockType::Rock_1:
	{
		// ���� �ݶ��̴� ������ ��ŭ ����������
		m_pCollider->SetSize({ 120.0f, 120.0f });
	}
		break;

	// �������� ����
	case BlockType::Goal:
	{
		// ó������ ��Ȱ��ȭ �صд�.
		m_pCollider->m_IsTrigger = true;
		m_Transform.Position.x += spawnPosX;
		m_Transform.Position.y += spawnPosY;
		SetSprite(SLDataManager->GetSprite("starting_ani_sprite_0"));
	}
		return;
	default:
		break;
	}

	// ���� ����Ʈ�� ��ġ��Ų��
	m_Transform.Position.x += spawnPosX;
	m_Transform.Position.y += spawnPosY;


	SetSprite(SLDataManager->GetSprite(name));
}

Block::~Block()
{
}
