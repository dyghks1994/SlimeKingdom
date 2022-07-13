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
	// 배치(활성화)상태로 설정
	m_Active = true;
	m_Visible = true;

	m_IsDestroyed = false;

	// 처음엔 움직일 수 없게 설정
	m_IsMoving = false;
	m_MoveSpeed = 5.0f;

	// 태그 값
	m_Tag = "Rock";

	// 스폰 포인트에 위치시킨다
	m_Transform.Position.x = spawnPosX;
	m_Transform.Position.y = spawnPosY;

	// 바위의 콜라이더 사이즈 만큼 설정해주자
	m_pCollider->SetSize({ 120.0f, 120.0f });

	//뎁스 설정
	m_pRenderer->m_Depth = (int)SLDepth::Object;

	//스프라이트 세팅
	SetSprite(SLDataManager->GetSprite("stone_none_broken"));
}

void Rock::Update()
{
	/// 파괴되어 있다면 
	if (IsDestroyed())
	{
		// 패스
		m_Active = false;
		m_Visible = false;
		return;
	}

	/// 아직 남아 있다면

	// 무언가와 충돌 했을 때
	if (!this->m_pCollider->m_Hits.empty())
	{
		// 충돌 프로세스
		Collision();
	}


}

void Rock::Collision()
{
	//cout << "[Rock] 충돌 m_Hits.size = " << m_pCollider->m_Hits.size() << "\n";

	for (auto obj : m_pCollider->m_Hits)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(obj);

		//cout << "[Rock] 충돌 오브젝트의 tag = " << gameObject->m_Tag << "\n\n";

		// 불릿이랑 충돌 했을 때 
		if (gameObject->m_Tag == "Bullet")
		{
			Bullet* bullet = dynamic_cast<Bullet*>(gameObject);

			// 그 bullet의 슈터가 Player 라면
			if (bullet->m_Shooter->m_Tag == "Player")
			{
				// 피격 처리를 한다.
				ReceiveAttack(bullet);


			}
		}

		// 이동 가능 상태이면서 플레이어랑 충돌 했을 때
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
		cout << "[Rock] 밀기 불가능!!\n";
		return;
	}

	m_MoveSpeed = player->GetMoveSpeed();

	D2D1_POINT_2F dir = player->GetLookVector();

	//미는 방향에 다른 오브젝트가 있는지 체크..
	for (int i = 0; i < m_pCollider->m_Hits.size(); i++)
	{
		Object* tempObj = m_pCollider->m_Hits[i];
		//검사할 대상이 플레이어면 패스
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

	cout << "[Rock] 이동(밀림) !!\n";

}

void Rock::ReceiveAttack(Bullet* bulletObject)
{
	UnitAttribute bulletAttribute = bulletObject->m_Attribute;

	cout << "[Rock] 피격! 피격속성 -> " << static_cast<int>(bulletAttribute) << "\n";

	// 맞은 탄환의 속성에 따라서
	switch (bulletAttribute)
	{

		// 물속성(+무속성) 탄환일 경우
	case UnitAttribute::Water:
	{
		// 움직임이 가능한 상태로 변경
		m_IsMoving = true;

		cout << "[Rock] 이동 가능 상태로 변경~~!\n\n";

		// 바위의 이미지도 바뀌어야 한다
		SetSprite(SLDataManager->GetSprite("stone_water_broken"));

		break;
	}

	// 불속상 탄환일 경우
	case UnitAttribute::Fire:
	{
		// 오브젝트 비활성화(미 배치 상태(제거상태로)
		m_Active = false;
		m_Visible = false;
		m_IsDestroyed = true;

		cout << "[Rock] " << this << " 파괴!!\n\n";


		break;
	}

	// 풀속상 탄환일 경우
	case UnitAttribute::Grass:
	case UnitAttribute::None:
	{
		// 아무 일도 일어나지 않았다
		cout << "[Rock] 아무 일도 일어나지 않았다!\n\n";

		break;
	}
	}// end of switch
}

