#include "stdafx.h"
#include "Box.h"

Box::Box(float spawnPosX, float spawnPosY, JewelryAttribute jewelry, string name)
	: Gimmick(name)
{
	cout << "[Box] " << this << " ����\n";
	
	// �±� ����
	m_Tag = name;
	
	Initialize(spawnPosX, spawnPosY, jewelry);
}

Box::~Box()
{
}

BoxState Box::GetState()
{
	return m_BoxState;
}

void Box::Initialize(const float spawnPosX, const float spawnPosY, const JewelryAttribute jewelry)
{
	// ������Ʈ Ȱ��ȭ
	m_Active = true;
	m_Visible = true;

	// ��ġ ����
	m_Transform.Position.x = spawnPosX;
	m_Transform.Position.y = spawnPosY;

	// �ݶ��̴� ������ ����
	m_pCollider->SetSize({ 120.0f, 120.0f });

	// �ڽ� ���� �ð� ����
	m_BoxOpenTime = 0.3f;

	// ���� ���´� ���� ���·� �ʱ�ȭ
	m_BoxState = BoxState::Closed;

	//���� ����
	m_pRenderer->m_Depth = (int)SLDepth::Object;

	//��������Ʈ ����
	SetSprite(SLDataManager->GetSprite(m_Tag));

	// ���� �Ӽ� ����
	m_JewelryAttribute = jewelry;

	/// ���� Ÿ��(�Ӽ�)�� ���� �ִϸ��̼�(�̹���) ����
	switch (m_JewelryAttribute)
	{
		case JewelryAttribute::Water: m_Anim = new Animation(*SLDataManager->GetAnimation("box_opening_W")); break;
		case JewelryAttribute::Fire:  m_Anim = new Animation(*SLDataManager->GetAnimation("box_opening_F")); break;
		case JewelryAttribute::Grass: m_Anim = new Animation(*SLDataManager->GetAnimation("box_opening_G")); break;
	}
}

void Box::Reset()
{

}

void Box::Update()
{
	// �̹� ���� ���¸� 
	if (IsOpened())
	{
		// �н�����
		return;
	}

	// �浹 ���� ��
	if (!this->m_pCollider->m_Hits.empty())
	{
		// �浹 ���μ���
		Collision();
	}

	// ���� �����ؼ� Ÿ�̸Ӱ� �������̶�� Ÿ�̸Ӹ� ������
	if (m_BoxState == BoxState::Opening)
	{
		// Ÿ�̸� ����
		openTimer -= 1.0f / 60.0f;

		// Ÿ�̸Ӱ� �� ��������
		if (openTimer <= 0.0f)
		{
			// ���� ���·� ����
			m_BoxState = BoxState::Opened;

			// �̹��� ����
			SetSprite(SLDataManager->GetSprite("box_open"));

			// �ִϸ��̼� ����
			SetAnimation(nullptr);
		}
	}
}

void Box::Collision()
{
	//cout << "[Box] �浹 m_Hits.size = " << m_pCollider->m_Hits.size() << "\n";

	for (auto obj : m_pCollider->m_Hits)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(obj);

		//cout << "[Box] �浹 ������Ʈ�� tag = " << gameObject->m_Tag << "\n\n";


		// �÷��̾�� �浹���� ��
		if (gameObject->m_Tag == "Player")
		{
			Player* player = dynamic_cast<Player*>(gameObject);

			// ���� ���� ����.
			OpenBox();

			// �ִϸ��̼� ����
			SetAnimation(m_Anim);

			// �÷��̾��� ���濡 ������ �߰��Ѵ�.
			switch (m_JewelryAttribute)
			{
			case JewelryAttribute::Water: player->SetPlayerBag(player->GetPlayerBag() | PlayerBag::Water); break;
			case JewelryAttribute::Fire: player->SetPlayerBag(player->GetPlayerBag() | PlayerBag::Fire);  break;
			case JewelryAttribute::Grass: player->SetPlayerBag(player->GetPlayerBag() | PlayerBag::Grass); break;
			}

		}
	}
}

bool Box::IsOpened()
{
	// ���� ������
	if (m_BoxState == BoxState::Opened)
	{
		// Ʈ��
		return true;
	}

	// ���� �ְų� , ������ ���̸�
	else
	{
		// false
		return false;
	}
}

void Box::OpenBox()
{
	switch (m_BoxState)
	{
		case BoxState::Closed:
		{
			cout << "[Box] " << this << "�ڽ��� ���ϴ�~~\n\n";

			// ������ ������ ���� ����
			m_BoxState = BoxState::Opening;

			// Ÿ�̸� ����
			openTimer = m_BoxOpenTime;

			// �ڽ� ������ �ִϸ��̼� ����

			// �ڽ� ������ ȿ����
			SoundManager::PlayEX("Box_Open");

			break;
		}

		case BoxState::Opening:
		{
			cout << "[Box] " << this << "�ڽ� �̹� ���� ��~~\n\n";
			break;

		}

		case BoxState::Opened:
		{
			cout << "[Box] " << this << "�ڽ� ���� �ִ�!!\n\n";
			break;

		}
	}// end of switch
}
