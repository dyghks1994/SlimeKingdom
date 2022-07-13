#include "stdafx.h"
#include "Rock.h"

Rock::Rock(float spawnPosX, float spawnPosY, string)
{
	Initialize(spawnPosX, spawnPosY);
}

Rock::~Rock()
{
}

void Rock::Initialize(const float spawnPosX, const float spawnPosY)
{
	// ��ġ(Ȱ��ȭ)���·� ����
	m_Active = true;
	m_Visible = true;

	m_IsDestroyed = false;

	// ó���� ������ �� ���� ����
	m_IsMoving = false;
	m_MoveSpeed = 5.0f;

	// �±� ��
	m_Tag = "Rock";

	// ���� ����Ʈ�� ��ġ��Ų��
	m_Transform.Position.x = spawnPosX;
	m_Transform.Position.y = spawnPosY;

	// ������ �ݶ��̴� ������ ��ŭ ����������
	m_pCollider->SetSize({ 120.0f, 120.0f });

	//���� ����
	m_pRenderer->m_Depth = (int)SLDepth::Object;

	//��������Ʈ ����
	SetSprite(SLDataManager->GetSprite("stone_none_broken"));
}

void Rock::Update()
{
	/// �ı��Ǿ� �ִٸ� 
	if (IsDestroyed())
	{
		// �н�
		m_Active = false;
		m_Visible = false;
		return;
	}

	/// ���� ���� �ִٸ�

	// ���𰡿� �浹 ���� ��
	if (!this->m_pCollider->m_Hits.empty())
	{
		// �浹 ���μ���
		Collision();
	}


}

void Rock::Collision()
{
	//cout << "[Rock] �浹 m_Hits.size = " << m_pCollider->m_Hits.size() << "\n";

	for (auto obj : m_pCollider->m_Hits)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(obj);

		//cout << "[Rock] �浹 ������Ʈ�� tag = " << gameObject->m_Tag << "\n\n";

		// �Ҹ��̶� �浹 ���� �� 
		if (gameObject->m_Tag == "Bullet")
		{
			Bullet* bullet = dynamic_cast<Bullet*>(gameObject);

			// �� bullet�� ���Ͱ� Player ���
			if (bullet->m_Shooter->m_Tag == "Player")
			{
				// �ǰ� ó���� �Ѵ�.
				ReceiveAttack(bullet);


			}
		}

		// �̵� ���� �����̸鼭 �÷��̾�� �浹 ���� ��
		if (m_IsMoving && gameObject->m_Tag == "Player")
		{
			Player* player = dynamic_cast<Player*>(gameObject);

			Move(player);
		}
	}

	m_MoveSpeed = 0.0f;
}

void Rock::Move(Player* player)
{
	if (!m_IsMoving)
	{
		cout << "[Rock] �б� �Ұ���!!\n";
		return;
	}

	m_MoveSpeed = player->GetMoveSpeed();

	D2D1_POINT_2F dir = player->GetLookVector();

	//�̴� ���⿡ �ٸ� ������Ʈ�� �ִ��� üũ..
	for (int i = 0; i < m_pCollider->m_Hits.size(); i++)
	{
		Object* tempObj = m_pCollider->m_Hits[i];
		//�˻��� ����� �÷��̾�� �н�
		if (tempObj == player) continue;

		D2D1_POINT_2F tempDir = { 0,0 };

		if (player->m_Transform.Position.x < tempObj->m_Transform.Position.x)
		{
			tempDir.x = 1.0f;
		}
		else if (player->m_Transform.Position.x > tempObj->m_Transform.Position.x)
		{
			tempDir.x = -1.0f;
		}

		if (player->m_Transform.Position.y < tempObj->m_Transform.Position.y)
		{
			tempDir.y = 1.0f;
		}
		else if (player->m_Transform.Position.y > tempObj->m_Transform.Position.y)
		{
			tempDir.y = -1.0f;
		}

		if ((dir.x == tempDir.x) || (dir.y == tempDir.y))
		{
			return;
		}
	}

	m_Transform.Position.x += dir.x * m_MoveSpeed;
	m_Transform.Position.y += dir.y * m_MoveSpeed;

	cout << "[Rock] �̵�(�и�) !!\n";

}

void Rock::ReceiveAttack(Bullet* bulletObject)
{
	UnitAttribute bulletAttribute = bulletObject->m_Attribute;

	cout << "[Rock] �ǰ�! �ǰݼӼ� -> " << static_cast<int>(bulletAttribute) << "\n";

	// ���� źȯ�� �Ӽ��� ����
	switch (bulletAttribute)
	{

		// ���Ӽ�(+���Ӽ�) źȯ�� ���
	case UnitAttribute::Water:
	{
		// �������� ������ ���·� ����
		m_IsMoving = true;

		cout << "[Rock] �̵� ���� ���·� ����~~!\n\n";

		// ������ �̹����� �ٲ��� �Ѵ�
		SetSprite(SLDataManager->GetSprite("stone_water_broken"));

		break;
	}

	// �Ҽӻ� źȯ�� ���
	case UnitAttribute::Fire:
	{
		// ������Ʈ ��Ȱ��ȭ(�� ��ġ ����(���Ż��·�)
		m_Active = false;
		m_Visible = false;
		m_IsDestroyed = true;

		cout << "[Rock] " << this << " �ı�!!\n\n";


		break;
	}

	// Ǯ�ӻ� źȯ�� ���
	case UnitAttribute::Grass:
	case UnitAttribute::None:
	{
		// �ƹ� �ϵ� �Ͼ�� �ʾҴ�
		cout << "[Rock] �ƹ� �ϵ� �Ͼ�� �ʾҴ�!\n\n";

		break;
	}
	}// end of switch
}

