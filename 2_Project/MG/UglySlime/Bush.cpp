#include "stdafx.h"
#include "Bush.h"

Bush::Bush(float spawnPosX, float spawnPosY, bool fruit, string name)
	: Gimmick(name)
{
	// ���� ���� ����
	m_Fruit = fruit;

	Initialize(spawnPosX, spawnPosY);
}

Bush::~Bush()
{
}

void Bush::Initialize(const float spawnPosX, const float spawnPosY)
{
	// ��ġ(Ȱ��ȭ)���·� ����
	m_Active = true;
	m_Visible = true;

	m_IsDestroyed = false;

	// ó���� ������ �� ���� ����
	m_IsMoving = false;

	// �±� ��
	m_Tag = "Bush";

	// ���� ����Ʈ�� ��ġ��Ų��
	m_Transform.Position.x = spawnPosX;
	m_Transform.Position.y = spawnPosY;

	// ������ �ݶ��̴� ������ ��ŭ ����������
	m_pCollider->SetSize({ 110.0f, 100.0f });
	SetLayer((int)SLLayer::Object);


	//���� ����
	m_pRenderer->m_Depth = (int)SLDepth::Object;


	//��������Ʈ ����
	string name = "bush_none";
	name += (m_Fruit) ? "_life" : "";
	SetSprite(SLDataManager->GetSprite(name));
}

void Bush::Update()
{
	/// �ı� �Ǿ��ִٸ� ������Ʈ ���� ����
	if (IsDestroyed())
	{
		m_Active = false;
		m_Visible = false;
		return;
	}

	/// ���� ���� �ִٸ�
	m_Active = true;
	m_Visible = true;

	// ���𰡿� �浹 ���� ��
	if (!this->m_pCollider->m_Hits.empty())
	{
		// �浹 ���μ���
		Collision();
	}
}

void Bush::Collision()
{
	//cout << "[Bush] �浹 m_Hits.size = " << m_pCollider->m_Hits.size() << "\n";

	for (auto obj : m_pCollider->m_Hits)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(obj);

		//cout << "[Bush] �浹 ������Ʈ�� tag = " << gameObject->m_Tag << "\n\n";

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
}



void Bush::Move()
{

}

void Bush::Move(Player* player)
{
	if (!m_IsMoving)
	{
		cout << "[Bush] �б� �Ұ���!!\n";
		return;
	}

	m_MoveSpeed = player->GetMoveSpeed();

	// �÷��̾��� �ü� ���͸� ���Ѵ�.
	//D2D1_POINT_2F dir = player->GetLookVector();
	D2D1_POINT_2F playerDir = player->GetLookVector();

	// Bush�� ���� �÷��̾��� ����(��ġ)�� ���Ѵ�.
	//m_Transform
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

		if ((playerDir.x == tempDir.x)||(playerDir.y == tempDir.y))
		{
			return;
		}
	}


	m_Transform.Position.x += playerDir.x * m_MoveSpeed;
	m_Transform.Position.y += playerDir.y * m_MoveSpeed;

	cout << "[Bush] �̵�(�и�) !!\n";
}

void Bush::ReceiveAttack(Bullet* bulletObject)
{
	UnitAttribute bulletAttribute = bulletObject->m_Attribute;

	// ���� źȯ�� �Ӽ��� ����
	switch (bulletAttribute)
	{
		// ���Ӽ�() źȯ�� ���
		case UnitAttribute::Water:
		{
			// ���� ����(ȸ�� ��Ű�� �ʾҴٸ�)�� �ִٸ�
			if (m_Fruit)
			{
				cout << "[Bush] ���Ű� �־ �������� ����~~\n\n";
				break;
			}

			// �������� ������ ���·� ����
			m_IsMoving = true;

			cout << "[Bush] �̵� ���� ���·� ����~~!\n\n";

			SetSprite(SLDataManager->GetSprite("bush_water"));

			break;
		}

		// �Ҽӻ� źȯ�� ���
		case UnitAttribute::Fire:
		{
			// ������Ʈ ��Ȱ��ȭ(�� ��ġ ����(���Ż��·�)
			m_Active = false;
			m_Visible = false;

			m_IsDestroyed = true;

			cout << "[Bush] " << this << " �ı�!!\n\n";

			break;
		}

		// Ǯ�ӻ� źȯ�� ���
		case UnitAttribute::Grass:
		{
			if (m_Fruit)
			{
				// ���� ����
				m_Fruit = false;
				SoundManager::PlayEX("Ch_Heal");

				// ���� ���� �̹����� ����
				SetSprite(SLDataManager->GetSprite("bush_none"));

				if (bulletObject->m_Shooter->GetCurrentHp() < bulletObject->m_Shooter->GetMaxHp())
				{
					// �÷��̾��� Hp�� 1 ���� ��Ű��.
					bulletObject->m_Shooter->SetCurrentHp(bulletObject->m_Shooter->GetCurrentHp() + 1);

					cout << "[Player] Hp 1 ȸ��!\n\n";	
				}
				
				else
				{
					cout << "[Player] Hp�� Max�� ȸ�� �Ұ���~\n\n";
				}

				break;
			}	

			
			cout << "[Bush] �̹� ���Ű� ���Ǿ���!!\n\n";

			break;
		}
	}// end of switch
}

