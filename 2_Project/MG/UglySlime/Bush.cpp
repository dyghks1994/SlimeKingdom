#include "stdafx.h"
#include "Bush.h"

Bush::Bush(float spawnPosX, float spawnPosY, bool fruit, string name)
	: Gimmick(name)
{
	// 열매 유무 세팅
	m_Fruit = fruit;

	Initialize(spawnPosX, spawnPosY);
}

Bush::~Bush()
{
}

void Bush::Initialize(const float spawnPosX, const float spawnPosY)
{
	// 배치(활성화)상태로 설정
	m_Active = true;
	m_Visible = true;

	m_IsDestroyed = false;

	// 처음엔 움직일 수 없게 설정
	m_IsMoving = false;

	// 태그 값
	m_Tag = "Bush";

	// 스폰 포인트에 위치시킨다
	m_Transform.Position.x = spawnPosX;
	m_Transform.Position.y = spawnPosY;

	// 나무의 콜라이더 사이즈 만큼 설정해주자
	m_pCollider->SetSize({ 110.0f, 100.0f });
	SetLayer((int)SLLayer::Object);


	//뎁스 설정
	m_pRenderer->m_Depth = (int)SLDepth::Object;


	//스프라이트 세팅
	string name = "bush_none";
	name += (m_Fruit) ? "_life" : "";
	SetSprite(SLDataManager->GetSprite(name));
}

void Bush::Update()
{
	/// 파괴 되어있다면 업데이트 하지 말자
	if (IsDestroyed())
	{
		m_Active = false;
		m_Visible = false;
		return;
	}

	/// 아직 남아 있다면
	m_Active = true;
	m_Visible = true;

	// 무언가와 충돌 했을 때
	if (!this->m_pCollider->m_Hits.empty())
	{
		// 충돌 프로세스
		Collision();
	}
}

void Bush::Collision()
{
	//cout << "[Bush] 충돌 m_Hits.size = " << m_pCollider->m_Hits.size() << "\n";

	for (auto obj : m_pCollider->m_Hits)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(obj);

		//cout << "[Bush] 충돌 오브젝트의 tag = " << gameObject->m_Tag << "\n\n";

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
}



void Bush::Move()
{

}

void Bush::Move(Player* player)
{
	if (!m_IsMoving)
	{
		cout << "[Bush] 밀기 불가능!!\n";
		return;
	}

	m_MoveSpeed = player->GetMoveSpeed();

	// 플레이어의 시선 벡터를 구한다.
	//D2D1_POINT_2F dir = player->GetLookVector();
	D2D1_POINT_2F playerDir = player->GetLookVector();

	// Bush로 부터 플레이어의 방향(위치)을 구한다.
	//m_Transform
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

		if ((playerDir.x == tempDir.x)||(playerDir.y == tempDir.y))
		{
			return;
		}
	}


	m_Transform.Position.x += playerDir.x * m_MoveSpeed;
	m_Transform.Position.y += playerDir.y * m_MoveSpeed;

	cout << "[Bush] 이동(밀림) !!\n";
}

void Bush::ReceiveAttack(Bullet* bulletObject)
{
	UnitAttribute bulletAttribute = bulletObject->m_Attribute;

	// 맞은 탄환의 속성에 따라서
	switch (bulletAttribute)
	{
		// 물속성() 탄환일 경우
		case UnitAttribute::Water:
		{
			// 아직 열매(회복 시키지 않았다면)가 있다면
			if (m_Fruit)
			{
				cout << "[Bush] 열매가 있어서 움직이지 못함~~\n\n";
				break;
			}

			// 움직임이 가능한 상태로 변경
			m_IsMoving = true;

			cout << "[Bush] 이동 가능 상태로 변경~~!\n\n";

			SetSprite(SLDataManager->GetSprite("bush_water"));

			break;
		}

		// 불속상 탄환일 경우
		case UnitAttribute::Fire:
		{
			// 오브젝트 비활성화(미 배치 상태(제거상태로)
			m_Active = false;
			m_Visible = false;

			m_IsDestroyed = true;

			cout << "[Bush] " << this << " 파괴!!\n\n";

			break;
		}

		// 풀속상 탄환일 경우
		case UnitAttribute::Grass:
		{
			if (m_Fruit)
			{
				// 열매 제거
				m_Fruit = false;
				SoundManager::PlayEX("Ch_Heal");

				// 열매 없는 이미지로 변경
				SetSprite(SLDataManager->GetSprite("bush_none"));

				if (bulletObject->m_Shooter->GetCurrentHp() < bulletObject->m_Shooter->GetMaxHp())
				{
					// 플레이어의 Hp를 1 증가 시키자.
					bulletObject->m_Shooter->SetCurrentHp(bulletObject->m_Shooter->GetCurrentHp() + 1);

					cout << "[Player] Hp 1 회복!\n\n";	
				}
				
				else
				{
					cout << "[Player] Hp가 Max라서 회복 불가능~\n\n";
				}

				break;
			}	

			
			cout << "[Bush] 이미 열매가 사용되었다!!\n\n";

			break;
		}
	}// end of switch
}

