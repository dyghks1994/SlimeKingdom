#include "stdafx.h"
#include "Switch.h"

Switch::Switch(float spawnPosX, float spawnPosY, string name)
{
	// �±� ����
	m_Tag = name;

	m_Door = nullptr;

	// ������ġ �ʱ�ȭ
	Initialize(spawnPosX, spawnPosY);
}

Switch::~Switch()
{
}

void Switch::SetSwitchOn(const SwitchState val)
{
	m_SwitchState = val;
}

void Switch::SetDoor(Door* door)
{
	m_Door = door;

	cout << "[Switch]  �� ����(����)!!\n\n";
}

void Switch::Initialize(const float spawnPosX, const float spawnPosY)
{
	// ������Ʈ Ȱ��ȭ
	m_Active = true;
	m_Visible = true;

	// ��ġ ����
	m_Transform.Position.x = spawnPosX;
	m_Transform.Position.y = spawnPosY;

	// �ݶ��̴� ����
	this->SetLayer(int(SLLayer::Object));
	m_pCollider->SetSize({ 120.0f, 120.0f });

	// ����ġ Off ���·�
	m_SwitchState = SwitchState::Off;

	//���� ����
	m_pRenderer->m_Depth = (int)SLDepth::Object;

	// ��������Ʈ ���
	m_Sprite[0] = SLDataManager->GetSprite(m_Tag);
	m_Sprite[1] = SLDataManager->GetSprite("switch_1_on");

	// �ʱ� ��������Ʈ �̹��� ����
	SetSprite(m_Sprite[0]);
}

void Switch::Update()
{
	// �������� �ȵǾ� �ִٸ�
	if (!m_Door)
	{
 		Door* door = nullptr;

		// ����ġ�� �±׿� ���� ���� ã�� �����Ѵ�.
		if (m_Tag == "switch_1_off")
		{
			door = dynamic_cast<Door*>(MGScene->m_pGameObjectManager->FindGameObject("door_1_closed"));
		}

		else if (m_Tag == "switch_2_off")
		{
			door = dynamic_cast<Door*>(MGScene->m_pGameObjectManager->FindGameObject("door_2_closed"));
		}

		else if (m_Tag == "switch_3_off")
		{
			door = dynamic_cast<Door*>(MGScene->m_pGameObjectManager->FindGameObject("door_3_closed"));
		}

		else if (m_Tag == "switch_4_off")
		{
			door = dynamic_cast<Door*>(MGScene->m_pGameObjectManager->FindGameObject("door_4_closed"));
		}

		else if (m_Tag == "switch_5_off")
		{
  			door = dynamic_cast<Door*>(MGScene->m_pGameObjectManager->FindGameObject("door_5_closed"));
		}

		// ã�� ���� �ִٸ� ���� ����(����)�Ѵ�.
		if (door)
		{
			SetDoor(door);
			cout << "[Switch] �� ���� ����!!\n\n";
		}
	}

	if (IsSwitchOn())
	{
		// �̹� ����ġ�� on �̶�� �н�����
		return;
	}
	// ���𰡿� �浹 ���� ��
	if (!this->m_pCollider->m_Hits.empty())
	{
		// �浹 ���μ���
		Collision();
	}
}

void Switch::Collision()
{
	//cout << "[Switch] �浹 m_Hits.size = " << m_pCollider->m_Hits.size() << "\n";

	for (auto obj : m_pCollider->m_Hits)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(obj);

		//cout << "[Switch] �浹 ������Ʈ�� tag = " << gameObject->m_Tag << "\n\n";

		// �Ҹ��̶� �浹 ���� �� 
		if (gameObject->m_Tag == "Bullet")
		{
			Bullet* bullet = dynamic_cast<Bullet*>(gameObject);

			// �� bullet�� ���Ͱ� Player ���
			if (bullet->m_Shooter->m_Tag == "Player")
			{
				if (IsSwitchOn())
				{
					cout << "[Switch] �̹� �۵� �Ǿ���!!\n";

					return;
				}

				// �ǰ� ó���� �Ѵ�.
				ReceiveAttack(bullet);
			}
		}
	}
}

void Switch::ReceiveAttack(Bullet* bulletObject)
{
	UnitAttribute bulletAttribute = bulletObject->m_Attribute;

	// ���� źȯ�� �Ӽ��� ����
	switch (bulletAttribute)
	{
		// ���Ӽ�() źȯ�� ���
	case UnitAttribute::Water:
	case UnitAttribute::Fire:
	{
		cout << "[Switch] �ƹ� �ϵ� �Ͼ�� �ʾҴ�..\n\n";

		break;
	}


	// Ǯ�ӻ� źȯ�� ���
	case UnitAttribute::Grass:
	{
		if (!m_Door)
		{
			cout << "[Switch] ����� ���� �����ϴ�!!! ���� �����ϼ���~~\n\n";

			return;
		}
		// ���� ����
		m_Door->OpenDoor();

		// ���鼭 �ִϸ��̼� ����
		m_Door->StartAnim(m_Door->GetAnim());

		m_SwitchState = SwitchState::On;

		cout << "[Switch] ����� ���� ���ϴ�!!\n\n";

		// �̹��� ����
		SetSprite(m_Sprite[1]);

		break;
	}
	}// end of switch
}

bool Switch::IsSwitchOn()
{
	
	return static_cast<int>(m_SwitchState);
}
