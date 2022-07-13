#include "stdafx.h"
#include <random>

int Monster::count = 0;

Monster::Monster(string name, float spawnPosX, float spawnPosY, UnitAttribute attribute)
	: Unit(name), m_SpawnWaitngTime(5.0f)
{
	m_Tag = name;

	Initialize(spawnPosX, spawnPosY, attribute);

	// �߻�ü �ʱ�ȭ
	for (int i = 0; i < MAX_BULLET_SIZE; i++)
	{
		// �߻�ü �̸� ����
		m_Bullets[i] = new Bullet(this);	// �߻� ��ü(����)�� ������ �˷���
		m_Bullets[i]->SetLayer((int)SLLayer::Monster_Atk);
	}

	count++;

	cout << "[����] ī��Ʈ = " << count << "\n";
}

Monster::~Monster()
{
	for (int i = 0; i < MAX_BULLET_SIZE; i++)
	{
		// �߻�ü �̸� ����
		delete m_Bullets[i];
	}
}

void Monster::Initialize(float spawnPosX, float spawnPosY, UnitAttribute attribute)
{
	/// �⺻ �� ����
	m_State = MonsterState::Move;

	// �ϴ��� �ӽ÷�
	m_SpawnPosX = spawnPosX;			// ���� ��ġ X
	m_SpawnPosY = spawnPosY;			// ���� ��ġ Y

	m_MoveSpeed = 3.0f;					// �̵� �ӵ� ����

	m_Attribute = attribute;			// �Ӽ� ����

	m_LookVector = { 0.0f, -1.0f };

	m_CurrentHp = 3;

	this->SetLayer((int)SLLayer::Monster);

	m_pRenderer->m_Depth = (int)SLDepth::Object;

	m_Transform.Position.x = m_SpawnPosX;
	m_Transform.Position.y = m_SpawnPosY;

	m_pCollider->SetSize({ 70.0f, 50.0f });
	m_pCollider->m_Transform.Position.y = 15.0f;

	m_DetectionRange = 600.0f;

	/// Ÿ�̸� ����
	// ������ȯ Ÿ�̸�
	m_ChangeDirTimer = 3.0f;

	// ���� Ÿ�̸�
	m_AttackTimer = 10.0f;

	SetAnimations();
}

void Monster::Reset()
{
	/// �⺻ �� ����
	m_State = MonsterState::Move;

	m_MoveSpeed = 3.0f;					// �̵� �ӵ� ����

	m_LookVector = { 0.0f, -1.0f };

	m_CurrentHp = 3;

	this->SetLayer((int)SLLayer::Monster);

	m_pRenderer->m_Depth = (int)SLDepth::Object;

	m_Transform.Position.x = m_SpawnPosX;
	m_Transform.Position.y = m_SpawnPosY;

	m_DetectionRange = 600.0f;

	/// Ÿ�̸� ����
	// ������ȯ Ÿ�̸�
	m_ChangeDirTimer = 3.0f;

	// ���� Ÿ�̸�
	m_AttackTimer = 10.0f;
}

void Monster::Update()
{
	if (m_CurrentHp <= 0)
	{
		m_SpawnWait -= 1.0f / 60.0f;

		if (m_Visible)
		{
			m_Visible = false;
			m_pCollider->m_Active = false;
			m_SpawnWait = m_SpawnWaitngTime;
			return;
		}

		if (m_SpawnWait < 0)
		{
			m_Visible = true;
			m_pCollider->m_Active = true;

			m_CurrentHp = 3;

			m_Transform.Position.x = m_SpawnPosX;
			m_Transform.Position.y = m_SpawnPosY;
		}
	}

	switch (m_State)
	{
		/// �Ϲ� �̵� ����
		// ���� �ֱ�� ������ ������ ����..
	case MonsterState::Move:
	{
		Move();
		Collision();

		//Shoot();



		break;
	}

	}// end of switch

	UpdateAnimState();
}

void Monster::Collision()
{
	if (this->m_pCollider->m_Hits.empty())
	{
		return;
	}


	for (auto obj : this->m_pCollider->m_Hits)
	{

		if (m_AnimState != MonsterAnimState::Hit)
		{

			Bullet* tempBullet = dynamic_cast<Bullet*>(obj);
			if (tempBullet == nullptr)	continue;

			int attackValue = 1;

			switch (m_Attribute)
			{
			case UnitAttribute::Water:
				if (tempBullet->GetAttribute() == UnitAttribute::Grass)
				{
					attackValue = 3;
				}
				break;

			case UnitAttribute::Fire:
				if (tempBullet->GetAttribute() == UnitAttribute::Water)
				{
					attackValue = 3;
				}
				break;

			case UnitAttribute::Grass:
				if (tempBullet->GetAttribute() == UnitAttribute::Fire)
				{
					attackValue = 3;
				}
				break;
			}


			m_CurrentHp -= attackValue;


			return;
		}

	}

}

void Monster::SetAnimations()
{
	m_AnimState = MonsterAnimState::Idle;
	m_AnimDir = AnimDir::F;

	string attribute[] = { "_water", "_fire", "_grass" };
	string dirStr[] = { "","_B","_L","_R" };
	string stateName[] = { "_idle","_move", "_hurt","_attack" };

	//SLDataManager�� �ִϸ��̼��� �̿��Ͽ� ���ο� �ִϸ��̼� ����
	for (int state = 0; state < (int)MonsterAnimState::Num; state++)
	{
		for (int dir = 0; dir < (int)AnimDir::DirNum; dir++)
		{
			string animName = "monster" + attribute[(int)m_Attribute - 1] + stateName[state] + dirStr[dir];
			Animation tempAnim = *SLDataManager->GetAnimation(animName);
			anims[state][dir] = new Animation(tempAnim);
		}
	}

	for (int dir = 0; dir < (int)AnimDir::DirNum; dir++)
	{
		anims[(int)MonsterAnimState::Attack][dir]->m_IsLoop = false;
		anims[(int)MonsterAnimState::Hit][dir]->m_IsLoop = false;
	}

	Animation* nowAnim = anims[(int)m_AnimState][(int)m_AnimDir];
	if (m_pAnimation != nowAnim)
	{
		nowAnim->Reset();
		SetAnimation(nowAnim);
	}
}

void Monster::UpdateAnimState()
{
	//Animation ���� üũ
	//�̵� ���� üũ
	if (GetDirect().x == 0 && GetDirect().y == 0)
	{
		m_AnimState = MonsterAnimState::Idle;
	}
	else
	{
		m_AnimState = MonsterAnimState::Move;
	}

	if (IsPlayerInRange())
	{
		m_AnimState = MonsterAnimState::Move;
	}

	//���� üũ
	if (m_LookVector.x == 1.0f)
	{
		m_AnimDir = AnimDir::R;
	}
	if (m_LookVector.x == -1.0f)
	{
		m_AnimDir = AnimDir::L;
	}
	if (m_LookVector.y == 1.0f)
	{
		m_AnimDir = AnimDir::F;
	}
	if (m_LookVector.y == -1.0f)
	{
		m_AnimDir = AnimDir::B;
	}

	SetAnimation(anims[(int)m_AnimState][(int)m_AnimDir]);
}

bool Monster::IsPlayerInRange()
{
	float x = m_pPlayer->m_Transform.Position.x;
	float y = m_pPlayer->m_Transform.Position.y;
	float c = Distance(x, y, m_Transform.Position.x, m_Transform.Position.y);

	if (c < m_DetectionRange)
	{
		return true;
	}

	return false;
}


void Monster::Spawn()
{

}

void Monster::Move()
{
	/// ���� ��ȯ Ÿ�̸� ����
	static float timer = m_ChangeDirTimer;
	static float shootTimer = m_ChangeDirTimer;

	static bool fired = false;

	// Ÿ�̸� ����
	timer -= 1.0f / 60.0f;

	if (timer < 1.0f && fired == false)
	{
		Shoot();
		fired = true;

	}

	// Ÿ�̸Ӱ� �� �Ǹ�
	if (timer <= 0)
	{
		// �õ尪�� ��� ���� random_device ����.
		std::random_device rd;

		// random_device �� ���� ���� ���� ������ �ʱ�ȭ �Ѵ�.
		std::mt19937 gen(rd());

		// 0 ���� 99 ���� �յ��ϰ� ��Ÿ���� �������� �����ϱ� ���� �յ� ���� ����.
		std::uniform_int_distribution<int> dis(0, 3);

		// Ÿ�̸� �� ����
		timer = m_ChangeDirTimer;

		static int dir = 0;

		dir++;

		if (dir >= 4)
		{
			dir = 0;
		}

		/// ������ ������ ���� �̵����� ����
		switch (dis(gen))
		//switch (dir)
		{
			// �·� ����
		case 0:
		{
			m_LookVector = { -1.0f, 0.0f };
			break;
		}

		// ���� ����
		case 1:
		{
			m_LookVector = { 0.0f, -1.0f };
			break;
		}

		// ��� ����
		case 2:
		{
			m_LookVector = { 1.0f, 0.0f };
			break;
		}

		// �Ʒ��� ����
		case 3:
		{
			m_LookVector = { 0.0f, 1.0f };
			break;
		}
		}

		m_Transform.Position.x = m_Transform.Position.x * 1.0f;
		m_Transform.Position.y = m_Transform.Position.y * 1.0f;

		fired = false;
	}

	

}

void Monster::Shoot()
{
	static float timer = m_AttackTimer;

	// Ÿ�̸� ����
	//timer -= 1.0f / 60.0f;

	//if (timer <= 0.0f)
	//{
		//timer = m_AttackTimer;

		for (int i = 0; i < MAX_BULLET_SIZE; i++)
		{
			// �߻� ������ ���� �߻�ü�� ã�´�.
			if (!m_Bullets[i]->GetIsFired())
			{
				cout << "[Monster] " << i << " �߻� ����!" << this << "\n";

				// �߻���ġ�� �߻������ �����ش�.
				m_Bullets[i]->Shoot();

				if (this->GetLookVector().x == 1.0f)
				{
					m_Bullets[i]->m_pRenderer->m_Transform.Angle = -90;
				}
				if (this->GetLookVector().x == -1.0f)
				{
					m_Bullets[i]->m_pRenderer->m_Transform.Angle = 90;
				}
				if (this->GetLookVector().y == 1.0f)
				{
					m_Bullets[i]->m_pRenderer->m_Transform.Angle = 0;
				}
				if (this->GetLookVector().y == -1.0f)
				{
					m_Bullets[i]->m_pRenderer->m_Transform.Angle = 180;
				}

				cout << this->GetLookVector().x << " " << this->GetLookVector().y << "\n";

				return;
			}
		}

		//}
	//}

}

void Monster::ReceiveAttack()
{
}

bool Monster::IsDead() const
{
	return false;
}

void Monster::SpawnProcess()
{
	//static float spawnTimer = 
}
