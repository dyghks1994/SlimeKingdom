#include "stdafx.h"
#include <random>

int Monster::count = 0;

Monster::Monster(string name, float spawnPosX, float spawnPosY, UnitAttribute attribute)
	: Unit(name), m_SpawnWaitngTime(5.0f)
{
	m_Tag = name;

	Initialize(spawnPosX, spawnPosY, attribute);

	// 발사체 초기화
	for (int i = 0; i < MAX_BULLET_SIZE; i++)
	{
		// 발사체 미리 생성
		m_Bullets[i] = new Bullet(this);	// 발사 주체(슈터)가 누군지 알려줌
		m_Bullets[i]->SetLayer((int)SLLayer::Monster_Atk);
	}

	count++;

	cout << "[몬스터] 카운트 = " << count << "\n";
}

Monster::~Monster()
{
	for (int i = 0; i < MAX_BULLET_SIZE; i++)
	{
		// 발사체 미리 생성
		delete m_Bullets[i];
	}
}

void Monster::Initialize(float spawnPosX, float spawnPosY, UnitAttribute attribute)
{
	/// 기본 값 세팅
	m_State = MonsterState::Move;

	// 일단은 임시로
	m_SpawnPosX = spawnPosX;			// 스폰 위치 X
	m_SpawnPosY = spawnPosY;			// 스폰 위치 Y

	m_MoveSpeed = 3.0f;					// 이동 속도 설정

	m_Attribute = attribute;			// 속성 설정

	m_LookVector = { 0.0f, -1.0f };

	m_CurrentHp = 3;

	this->SetLayer((int)SLLayer::Monster);

	m_pRenderer->m_Depth = (int)SLDepth::Object;

	m_Transform.Position.x = m_SpawnPosX;
	m_Transform.Position.y = m_SpawnPosY;

	m_pCollider->SetSize({ 70.0f, 50.0f });
	m_pCollider->m_Transform.Position.y = 15.0f;

	m_DetectionRange = 600.0f;

	/// 타이머 설정
	// 방향전환 타이머
	m_ChangeDirTimer = 3.0f;

	// 공격 타이머
	m_AttackTimer = 10.0f;

	SetAnimations();
}

void Monster::Reset()
{
	/// 기본 값 세팅
	m_State = MonsterState::Move;

	m_MoveSpeed = 3.0f;					// 이동 속도 설정

	m_LookVector = { 0.0f, -1.0f };

	m_CurrentHp = 3;

	this->SetLayer((int)SLLayer::Monster);

	m_pRenderer->m_Depth = (int)SLDepth::Object;

	m_Transform.Position.x = m_SpawnPosX;
	m_Transform.Position.y = m_SpawnPosY;

	m_DetectionRange = 600.0f;

	/// 타이머 설정
	// 방향전환 타이머
	m_ChangeDirTimer = 3.0f;

	// 공격 타이머
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
		/// 일반 이동 상태
		// 일정 주기로 방향을 설정해 주자..
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

	//SLDataManager의 애니메이션을 이용하여 새로운 애니메이션 생성
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
	//Animation 상태 체크
	//이동 먼저 체크
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

	//방향 체크
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
	/// 방향 전환 타이머 설정
	static float timer = m_ChangeDirTimer;
	static float shootTimer = m_ChangeDirTimer;

	static bool fired = false;

	// 타이머 감소
	timer -= 1.0f / 60.0f;

	if (timer < 1.0f && fired == false)
	{
		Shoot();
		fired = true;

	}

	// 타이머가 다 되면
	if (timer <= 0)
	{
		// 시드값을 얻기 위한 random_device 생성.
		std::random_device rd;

		// random_device 를 통해 난수 생성 엔진을 초기화 한다.
		std::mt19937 gen(rd());

		// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
		std::uniform_int_distribution<int> dis(0, 3);

		// 타이머 재 설정
		timer = m_ChangeDirTimer;

		static int dir = 0;

		dir++;

		if (dir >= 4)
		{
			dir = 0;
		}

		/// 생성된 난수에 따라 이동방향 설정
		switch (dis(gen))
		//switch (dir)
		{
			// 좌로 설정
		case 0:
		{
			m_LookVector = { -1.0f, 0.0f };
			break;
		}

		// 위로 설정
		case 1:
		{
			m_LookVector = { 0.0f, -1.0f };
			break;
		}

		// 우로 설정
		case 2:
		{
			m_LookVector = { 1.0f, 0.0f };
			break;
		}

		// 아래로 설정
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

	// 타이머 감소
	//timer -= 1.0f / 60.0f;

	//if (timer <= 0.0f)
	//{
		//timer = m_AttackTimer;

		for (int i = 0; i < MAX_BULLET_SIZE; i++)
		{
			// 발사 중이지 않은 발사체를 찾는다.
			if (!m_Bullets[i]->GetIsFired())
			{
				cout << "[Monster] " << i << " 발사 성공!" << this << "\n";

				// 발사위치와 발사방향을 정해준다.
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
