#include "stdafx.h"
#include "Statue.h"


Statue::Statue(float spawnPosX, float spawnPosY, StatueType type, string str)
	: Gimmick(str)
{
	// �±� ��
	m_Tag = str;
	m_Type = type;

	Initialize(spawnPosX, spawnPosY);
}

Statue::~Statue()
{
}

void Statue::Initialize(const float spawnPosX, const float spawnPosY)
{
	// ��ġ(Ȱ��ȭ)���·� ����
	m_Active = true;
	m_Visible = true;

	// ���� ����Ʈ�� ��ġ��Ų��
	m_Transform.Position.x = spawnPosX;
	m_Transform.Position.y = spawnPosY;

	// ������ ŷ ������  �ݶ��̴� ����� �� ũ�� ����������
	if (m_Tag == "statue_king_off")
	{
		m_pCollider->SetSize({ 200.0f, 180.0f });
		m_pCollider->m_Transform.Position.y += 20.0f;
	}
	
	// �������� ���� Ÿ�� ������� ����������.
	else
	{
		m_pCollider->SetSize({ 100.0f, 100.0f });
		m_pCollider->m_Transform.Position.y += 5.0f;
	}

	SetLayer((int)SLLayer::Object);

	//���� ����
	m_pRenderer->m_Depth = (int)SLDepth::Object;

	/// ���� ������ ���� �̹��� �����ϸ� �ǰ���?
	SetSprite(SLDataManager->GetSprite(m_Tag));
	
}

void Statue::Update()
{
	// ���� ������ �������ִٸ�
	if (m_AttachedJewelry)
	{
		// �н� ����
		return;
	}

	// ���𰡿� �浹 ���� ��
	if (!this->m_pCollider->m_Hits.empty())
	{
		// �浹 ���μ���
		Collision();
	}
}

void Statue::Collision()
{
	//cout << "[Statue] �浹 m_Hits.size = " << m_pCollider->m_Hits.size() << "\n";

	for (auto obj : m_pCollider->m_Hits)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(obj);

		cout << "[Statue] �浹 ������Ʈ�� tag = " << gameObject->m_Tag << "\n\n";


		// �÷��̾�� �浹 ���� �� 
		if (gameObject->m_Tag == "Player")
		{
			Player* player = dynamic_cast<Player*>(gameObject);

			// ���� �÷��̾��� ����(���� ȹ��) ������ ��´�.
			uint bag = player->GetPlayerBag();

			if (bag == 0)
			{
				cout << "[System] ������ ����ִ�!!!\n\n";
				continue;
			}

			AttachJewelry(bag);
		}
	}
}

void Statue::AttachJewelry(uint bag)
{
	/// ���� ������ ���� �̹��� �����ϸ� �ǰ���?
	switch (m_Type)
	{
		// ���� Ÿ���� ���� ��
		case StatueType::Water:	
		{
			// �÷��̾��� ���濡 �� ������ �ִٸ�
			if (bag & PlayerBag::Water)
			{
				// ������ ���� �̹����� ����
				SetSprite(SLDataManager->GetSprite("statue_water_on"));
				SoundManager::PlayEX("Statue_On");

				/// ������ ���� ���·� �ٲٰ� �̹����� �ٲ���
				m_AttachedJewelry = true;

				cout << "[����] ���� ���� ����!! <Ÿ�� -> " << static_cast<int>(m_Type) << ">\n\n";


				/// ���� ������(����)�� �� ������ ������ ����
				/// �� ���� ������ ������ ŷ������ ������ Ȱ��ȭ ��Ų��.
				/// 
				
			}
			break;
		}
		
		// ���� Ÿ���� ���� ��
		case StatueType::Fire:
		{
			// �÷��̾��� ���濡 �� ������ �ִٸ�
			if (bag & PlayerBag::Fire)
			{
				// �� ���� ���� �̹����� ����
				SetSprite(SLDataManager->GetSprite("statue_fire_on"));
				SoundManager::PlayEX("Statue_On");

				/// ������ ���� ���·� �ٲٰ� �̹����� �ٲ���
				m_AttachedJewelry = true;

				cout << "[����] ���� ���� ����!! <Ÿ�� -> " << static_cast<int>(m_Type) << ">\n\n";

			}
			break;
		}

		// ���� Ÿ���� Ǯ�� ��
		case StatueType::Grass:
		{
			// �÷��̾��� ���濡 Ǯ ������ �ִٸ�
			if (bag & PlayerBag::Grass)
			{
				// Ǯ ���� ���� �̹����� ����
				SetSprite(SLDataManager->GetSprite("statue_leaf_on"));
				SoundManager::PlayEX("Statue_On");

				/// ������ ���� ���·� �ٲٰ� �̹����� �ٲ���
				m_AttachedJewelry = true;

				cout << "[����] ���� ���� ����!! <Ÿ�� -> " << static_cast<int>(m_Type) << ">\n\n";
			}
			break;
		}
	}
	
}

bool Statue::IsAttachedJewelry()
{
	return m_AttachedJewelry;
}
