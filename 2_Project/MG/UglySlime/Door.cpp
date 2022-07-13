#include "stdafx.h"
#include "Door.h"

Door::Door(float spawnPosX, float spawnPosY, string name)
	: Gimmick(name)
{
	// �±� ����
	m_Tag = name;

	Initialize(spawnPosX, spawnPosY);
}

Door::~Door()
{
}

Animation* Door::GetAnim()
{
	return m_Anim;
}

void Door::StartAnim(Animation* anim)
{
	SetAnimation(anim);
}

void Door::Initialize(const float spawnPosX, const float spawnPosY)
{
	// Ȱ��ȭ ���·� ����
	this->m_Active = true;
	this->m_Visible = true;

	// ���� ���·� ����
	m_State = DoorState::Closed;

	// ��ǥ ����
	this->m_Transform.Position.x = spawnPosX;
	this->m_Transform.Position.y = spawnPosY;

	// �ݶ��̴� ������ ����
	this->m_pCollider->SetSize({ 120.0f, 100.0f });
	m_pCollider->m_Transform.Position.y = 5.0f;

	this->SetLayer(int(SLLayer::Object));

	// �� ������ �ӵ�(�ð�) ����
	m_DoorOpenTime = 0.5f;

	//���� ����
	m_pRenderer->m_Depth = (int)SLDepth::Object;

	// ��������Ʈ ����
	m_Sprite[0] = SLDataManager->GetSprite(m_Tag);
	m_Sprite[1] = SLDataManager->GetSprite("door_open");

	SetSprite(m_Sprite[0]);

	// �ִϸ��̼� ����
	m_Anim = new Animation(*SLDataManager->GetAnimation("door_opening"));
}

void Door::Update()
{
	// ���� �ִٸ�
	if (IsOpened())
	{
		// �н�����.
		return;
	}

	// ���� �����ؼ� Ÿ�̸Ӱ� �������̶�� Ÿ�̸Ӹ� ������
	if (m_State == DoorState::Opening)
	{
		// Ÿ�̸� ����
		openTimer -= 0.5f / 60.0f;

		int x = m_Transform.Position.x / (120 * 16);
		int y = m_Transform.Position.y / (120 * 9);
		MGCamera->m_Transform.Position = { (float)(1920 * x), (float)(1080 * y) };
		SLDataManager->m_pMapManager->SwitchingSection(x + (y * 3));


		// Ÿ�̸Ӱ� �� ��������
		if (openTimer <= 0.0f)
		{
			// ���� ���·� ����
			m_State = DoorState::Opened;

			/// ���� ������ �ƿ� ��Ȱ��ȭ ��ų��?
			/// �ݶ��̴��� 0���� ����� ������?
			/// Ȱ��ȭ ���¿��� �ݶ��̴��� 0�̸� �������� �ǳ�?

			// �ִϸ��̼� ����
			SetAnimation(nullptr);

			// ���� �̹����� ����
			SetSprite(m_Sprite[1]);

			// �� Ȱ��ȭ 
			this->m_pCollider->m_Active = false;

			for (auto i : MGScene->m_pGameObjectManager->m_ItemList)
			{
				if (i.second.second->m_Layer == (int)SLLayer::Player)
				{
					int x = i.second.second->m_Transform.Position.x / (120 * 16);
					int y = i.second.second->m_Transform.Position.y / (120 * 9);
					MGCamera->m_Transform.Position = { (float)(1920 * x), (float)(1080 * y) };
					SLDataManager->m_pMapManager->SwitchingSection(x + (y * 3));
				}
			}
		}
	}
}


bool Door::IsOpened()
{
	// ���� ���� ������
	if (m_State == DoorState::Opened)
	{
		return true;
	}

	// ���� �ְų� ������ ��
	return false;
}

void Door::OpenDoor()
{
	switch (m_State)
	{
	case DoorState::Closed:
	{
		cout << "[Door] " << this << "���� ���ϴ�~~\n\n";

		// ������ ������ ���� ����
		m_State = DoorState::Opening;

		// Ÿ�̸� ����
		openTimer = m_DoorOpenTime;

		// �� ������ �ִϸ��̼� ����
		SoundManager::PlayEX("Door_Open");

		break;
	}

	case DoorState::Opening:
	{
		//cout << "[Door] " << this << "�� �̹� ���� ��~~\n\n";
		break;

	}

	case DoorState::Opened:
	{
		cout << "[Door] " << this << "�� �̹� ���� �ִ�!!\n\n";
		break;

	}
	}
}
