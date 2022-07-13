#include "stdafx.h"

Bullet::Bullet(Unit* shooter)
	: m_Shooter(shooter)

{
	// 생성할 때 슈터가 지정되지 않으면 안된다!
	assert(m_Shooter);

	Initialize();
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	/// 기본 값 초기화
	// 이동 속도 설정
	m_MoveSpeed = 25.0f;

	// 좌표 설정
	m_Transform.Position.x = 0.0f;
	m_Transform.Position.y = 0.0f;

	// 콜라이더 사이즈 설정
	m_pCollider->m_Size.width = 40.0f;
	m_pCollider->m_Size.height = 40.0f;

	m_pRenderer->m_Depth = 1;

	// 미발사 상태로 설정
	m_Active = false;
	m_IsFired = false;
	m_Visible = true;

	// 슈터의 속성으로 불릿의 속성을 설정
	SetAttribute(m_Shooter->GetAttribute());

	// 초기화하면서 다시 충돌 오브젝트 리스트를 클리어한다.
	m_pCollider->m_Hits.clear();

	cout << "[Bullet] " << this << " - 초기화!\n";

	// 발사체 생성할 때 다 Bullet로 해주자
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
	/// 발사 되지 않았다면
	if (!GetIsFired())
	{
		// 패스하자
		return;
	}

	/// 발사 되었다면

	// 현재 유효한 위치에 없다면(카메라를 벗어났다면)
	if (!CheekValidPosition())
	{
		// 발사 되기 전으로 초기화
		Initialize();

		return;
	}

	// 다른 오브젝트와 부딪혔다면
	if (!this->m_pCollider->m_Hits.empty())
	{
		// 충돌 프로세스
		Collision();
	}

	// 이동
	Move();

}

void Bullet::Collision()
{
	cout << "[Bullet] 충돌 m_Hits.size = " << m_pCollider->m_Hits.size() << "\n";

	for (auto obj : this->m_pCollider->m_Hits)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(m_pCollider->m_Hits.at(0));

		cout << "[Bullet] 충돌 오브젝트 " << gameObject << "\n";
		cout << "[Bullet] 충돌 오브젝트의 Tag = " << gameObject->m_Tag << "\n";
		cout << "[Bullet] 충돌 오브젝트의 Layer = " << gameObject->m_Layer << "\n\n";

		if (m_Layer == (int)SLLayer::Player_Atk)
		{
			// Rock 과 충돌 했을 때 
			if (gameObject->m_Tag == "Rock")
			{
				Rock* rock = dynamic_cast<Rock*>(gameObject);

				rock->ReceiveAttack(this);
			}

			// Bush 과 충돌 했을 때 
			if (gameObject->m_Tag == "Bush")
			{
				Bush* bush = dynamic_cast<Bush*>(gameObject);

				//bush->ReceiveAttack(this);
				bush->Collision();
			}

			// Switch 과 충돌 했을 때 
			if (gameObject->m_Tag == "Switch")
			{
				Switch* switchObj = dynamic_cast<Switch*>(gameObject);

				switchObj->ReceiveAttack(this);
			}
		}
		

		// 발사 되기 전으로 초기화
		Initialize();

		// 여기서 슈터와 충돌한 오브젝트가 뭐냐에 따라서 효과를 주어야 함.
		// ex. 1. 플레이어의 불릿 vs 몬스터 -> 데미지 적용
		//	   2. 몬스터 의 불릿 vs 플레이어 -> 데미지 적용
		// 그 외 플레이어 불릿 vs 오브젝트

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
	// 발사(이동) 방향 설정
	m_Dir = m_Shooter->GetLookVector();

	// 방향이 없을 때
	if (m_Dir.x == 0 && m_Dir.y == 0)
	{
		cout << "[System] 방향이 설정되지 않았습니다..\n";
		cout << "[System] 임시로 오른쪽으로 설정합니다!\n";

		m_Dir.x = 1.0f;
	}

	/// 발사 위치 세팅
	// 발사되자마자 충돌해서 생기는 버그를 방지하기 위해 위치를 보정해 줌.
	float startPosX = m_Shooter->m_Transform.Position.x + (m_Shooter->m_pCollider->m_Size.width + 5) * m_Dir.x;
	float startPosY = m_Shooter->m_Transform.Position.y + (m_Shooter->m_pCollider->m_Size.height + 5) * m_Dir.y;

	// 보정된 발사위치 세팅
	this->m_Transform.Position.x = startPosX;
	this->m_Transform.Position.y = startPosY;

	// 발사 상태로 변경
	m_IsFired = true;

	// 슈터의 속성으로 불릿의 속성을 설정
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


	// 오브젝트 활성화
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
	//cout << "[Bullet] 이동 전 좌표[" << this->m_Transform.Position.x;
	//cout << "," << this->m_Transform.Position.y << "]\n";

	// 이동
	this->m_Transform.Position.x += m_Dir.x * m_MoveSpeed;
	this->m_Transform.Position.y += m_Dir.y * m_MoveSpeed;

	cout << this->m_Transform.Position.x << "  " << this->m_Transform.Position.y << "\n";
}

bool Bullet::CheekValidPosition()
{
	// 카메라 시작 위치
	D2D1_POINT_2F cameraStartPos = MGCamera->m_Transform.Position;

	// 스크린 끝나는 위치
	D2D1_POINT_2F cameraEndPos = {
		MGCamera->m_Transform.Position.x + 1920.0f,
		MGCamera->m_Transform.Position.y + 1080.0f
	};

	if (m_Transform.Position.x > cameraStartPos.x &&
		m_Transform.Position.x < cameraEndPos.x &&
		m_Transform.Position.y > cameraStartPos.y &&
		m_Transform.Position.y < cameraEndPos.y)
	{
		// 카메라 영역 안에 있는 경우(유효한 위치)
		return true;
	}

	// 카메라 영역 넘어간 경우
	return false;
}
