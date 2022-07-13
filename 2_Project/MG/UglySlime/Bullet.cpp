#include "stdafx.h"

Bullet::Bullet(Unit* shooter)
	: m_Shooter(shooter)

{
	// ������ �� ���Ͱ� �������� ������ �ȵȴ�!
	assert(m_Shooter);

	Initialize();
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	/// �⺻ �� �ʱ�ȭ
	// �̵� �ӵ� ����
	m_MoveSpeed = 25.0f;

	// ��ǥ ����
	m_Transform.Position.x = 0.0f;
	m_Transform.Position.y = 0.0f;

	// �ݶ��̴� ������ ����
	m_pCollider->m_Size.width = 40.0f;
	m_pCollider->m_Size.height = 40.0f;

	m_pRenderer->m_Depth = 1;

	// �̹߻� ���·� ����
	m_Active = false;
	m_IsFired = false;
	m_Visible = true;

	// ������ �Ӽ����� �Ҹ��� �Ӽ��� ����
	SetAttribute(m_Shooter->GetAttribute());

	// �ʱ�ȭ�ϸ鼭 �ٽ� �浹 ������Ʈ ����Ʈ�� Ŭ�����Ѵ�.
	m_pCollider->m_Hits.clear();

	cout << "[Bullet] " << this << " - �ʱ�ȭ!\n";

	// �߻�ü ������ �� �� Bullet�� ������
	m_Tag = "Bullet";

	this->m_pRenderer->SetSprite(nullptr);
	if (this->m_pAnimation != nullptr)
	{
		delete this->m_pAnimation;
		this->m_pAnimation = nullptr;
	}
}

void Bullet::Update()
{
	/// �߻� ���� �ʾҴٸ�
	if (!GetIsFired())
	{
		// �н�����
		return;
	}

	/// �߻� �Ǿ��ٸ�

	// ���� ��ȿ�� ��ġ�� ���ٸ�(ī�޶� ����ٸ�)
	if (!CheekValidPosition())
	{
		// �߻� �Ǳ� ������ �ʱ�ȭ
		Initialize();

		return;
	}

	// �ٸ� ������Ʈ�� �ε����ٸ�
	if (!this->m_pCollider->m_Hits.empty())
	{
		// �浹 ���μ���
		Collision();
	}

	// �̵�
	Move();

}

void Bullet::Collision()
{
	cout << "[Bullet] �浹 m_Hits.size = " << m_pCollider->m_Hits.size() << "\n";

	for (auto obj : this->m_pCollider->m_Hits)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(m_pCollider->m_Hits.at(0));

		cout << "[Bullet] �浹 ������Ʈ " << gameObject << "\n";
		cout << "[Bullet] �浹 ������Ʈ�� Tag = " << gameObject->m_Tag << "\n";
		cout << "[Bullet] �浹 ������Ʈ�� Layer = " << gameObject->m_Layer << "\n\n";

		if (m_Layer == (int)SLLayer::Player_Atk)
		{
			// Rock �� �浹 ���� �� 
			if (gameObject->m_Tag == "Rock")
			{
				Rock* rock = dynamic_cast<Rock*>(gameObject);

				rock->ReceiveAttack(this);
			}

			// Bush �� �浹 ���� �� 
			if (gameObject->m_Tag == "Bush")
			{
				Bush* bush = dynamic_cast<Bush*>(gameObject);

				//bush->ReceiveAttack(this);
				bush->Collision();
			}

			// Switch �� �浹 ���� �� 
			if (gameObject->m_Tag == "Switch")
			{
				Switch* switchObj = dynamic_cast<Switch*>(gameObject);

				switchObj->ReceiveAttack(this);
			}
		}
		

		// �߻� �Ǳ� ������ �ʱ�ȭ
		Initialize();

		// ���⼭ ���Ϳ� �浹�� ������Ʈ�� ���Ŀ� ���� ȿ���� �־�� ��.
		// ex. 1. �÷��̾��� �Ҹ� vs ���� -> ������ ����
		//	   2. ���� �� �Ҹ� vs �÷��̾� -> ������ ����
		// �� �� �÷��̾� �Ҹ� vs ������Ʈ

		return;
	}
}

bool Bullet::GetIsFired() const
{
	return m_IsFired;
}

void Bullet::SetIsFired(const bool val)
{
	this->m_IsFired = val;
}

void Bullet::Shoot()
{
	// �߻�(�̵�) ���� ����
	m_Dir = m_Shooter->GetLookVector();

	// ������ ���� ��
	if (m_Dir.x == 0 && m_Dir.y == 0)
	{
		cout << "[System] ������ �������� �ʾҽ��ϴ�..\n";
		cout << "[System] �ӽ÷� ���������� �����մϴ�!\n";

		m_Dir.x = 1.0f;
	}

	/// �߻� ��ġ ����
	// �߻���ڸ��� �浹�ؼ� ����� ���׸� �����ϱ� ���� ��ġ�� ������ ��.
	float startPosX = m_Shooter->m_Transform.Position.x + (m_Shooter->m_pCollider->m_Size.width + 5) * m_Dir.x;
	float startPosY = m_Shooter->m_Transform.Position.y + (m_Shooter->m_pCollider->m_Size.height + 5) * m_Dir.y;

	// ������ �߻���ġ ����
	this->m_Transform.Position.x = startPosX;
	this->m_Transform.Position.y = startPosY;

	// �߻� ���·� ����
	m_IsFired = true;

	// ������ �Ӽ����� �Ҹ��� �Ӽ��� ����
	SetAttribute(m_Shooter->GetAttribute());
	string effectName = (m_Layer == (int)SLLayer::Player_Atk)? "Player" : "Monster";
	effectName += "AttackEffect_";
	switch (m_Attribute)
	{
	case UnitAttribute::Water:
		effectName += "water";
		SoundManager::PlayEX("Ch_wAtk");
		break;
	case UnitAttribute::Fire:
		effectName += "fire";
		SoundManager::PlayEX("Ch_fAtk");
		break;
	case UnitAttribute::Grass:
		effectName += "leaf";
		SoundManager::PlayEX("Ch_gAtk");
		break;
	}

	if (m_pAnimation != nullptr)
	{
		delete m_pAnimation;
		SetAnimation(nullptr);
	}
	SetSprite(SLDataManager->GetSprite(effectName+"_0"));
	SetAnimation(new Animation(*SLDataManager->GetAnimation(effectName)));


	// ������Ʈ Ȱ��ȭ
	m_Active = true;
	m_Visible = true;
	m_pCollider->m_Visible = true;

}

UnitAttribute Bullet::GetAttribute()
{
	return this->m_Attribute;
}

void Bullet::SetAttribute(const UnitAttribute attribute)
{
	this->m_Attribute = attribute;
}

void Bullet::SetDirection(Unit* shooter)
{
	this->m_Dir = shooter->GetDirect();
}

void Bullet::Move()
{
	//cout << "[Bullet] �̵� �� ��ǥ[" << this->m_Transform.Position.x;
	//cout << "," << this->m_Transform.Position.y << "]\n";

	// �̵�
	this->m_Transform.Position.x += m_Dir.x * m_MoveSpeed;
	this->m_Transform.Position.y += m_Dir.y * m_MoveSpeed;

	cout << this->m_Transform.Position.x << "  " << this->m_Transform.Position.y << "\n";
}

bool Bullet::CheekValidPosition()
{
	// ī�޶� ���� ��ġ
	D2D1_POINT_2F cameraStartPos = MGCamera->m_Transform.Position;

	// ��ũ�� ������ ��ġ
	D2D1_POINT_2F cameraEndPos = {
		MGCamera->m_Transform.Position.x + 1920.0f,
		MGCamera->m_Transform.Position.y + 1080.0f
	};

	if (m_Transform.Position.x > cameraStartPos.x &&
		m_Transform.Position.x < cameraEndPos.x &&
		m_Transform.Position.y > cameraStartPos.y &&
		m_Transform.Position.y < cameraEndPos.y)
	{
		// ī�޶� ���� �ȿ� �ִ� ���(��ȿ�� ��ġ)
		return true;
	}

	// ī�޶� ���� �Ѿ ���
	return false;
}
