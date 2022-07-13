#include "stdafx.h"
#include "Switch.h"

Switch::Switch(float spawnPosX, float spawnPosY, string name)
{
	// 태그 설정
	m_Tag = name;

	m_Door = nullptr;

	// 스폰위치 초기화
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

	cout << "[Switch]  문 연결(설정)!!\n\n";
}

void Switch::Initialize(const float spawnPosX, const float spawnPosY)
{
	// 오브젝트 활성화
	m_Active = true;
	m_Visible = true;

	// 위치 설정
	m_Transform.Position.x = spawnPosX;
	m_Transform.Position.y = spawnPosY;

	// 콜라이더 설정
	this->SetLayer(int(SLLayer::Object));
	m_pCollider->SetSize({ 120.0f, 120.0f });

	// 스위치 Off 상태로
	m_SwitchState = SwitchState::Off;

	//뎁스 설정
	m_pRenderer->m_Depth = (int)SLDepth::Object;

	// 스프라이트 등록
	m_Sprite[0] = SLDataManager->GetSprite(m_Tag);
	m_Sprite[1] = SLDataManager->GetSprite("switch_1_on");

	// 초기 스프라이트 이미지 설정
	SetSprite(m_Sprite[0]);
}

void Switch::Update()
{
	// 문설정이 안되어 있다면
	if (!m_Door)
	{
 		Door* door = nullptr;

		// 스위치의 태그에 따라서 문을 찾아 연결한다.
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

		// 찾은 문이 있다면 문을 연결(세팅)한다.
		if (door)
		{
			SetDoor(door);
			cout << "[Switch] 문 연결 성공!!\n\n";
		}
	}

	if (IsSwitchOn())
	{
		// 이미 스위치가 on 이라면 패스하자
		return;
	}
	// 무언가와 충돌 했을 때
	if (!this->m_pCollider->m_Hits.empty())
	{
		// 충돌 프로세스
		Collision();
	}
}

void Switch::Collision()
{
	//cout << "[Switch] 충돌 m_Hits.size = " << m_pCollider->m_Hits.size() << "\n";

	for (auto obj : m_pCollider->m_Hits)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(obj);

		//cout << "[Switch] 충돌 오브젝트의 tag = " << gameObject->m_Tag << "\n\n";

		// 불릿이랑 충돌 했을 때 
		if (gameObject->m_Tag == "Bullet")
		{
			Bullet* bullet = dynamic_cast<Bullet*>(gameObject);

			// 그 bullet의 슈터가 Player 라면
			if (bullet->m_Shooter->m_Tag == "Player")
			{
				if (IsSwitchOn())
				{
					cout << "[Switch] 이미 작동 되었다!!\n";

					return;
				}

				// 피격 처리를 한다.
				ReceiveAttack(bullet);
			}
		}
	}
}

void Switch::ReceiveAttack(Bullet* bulletObject)
{
	UnitAttribute bulletAttribute = bulletObject->m_Attribute;

	// 맞은 탄환의 속성에 따라서
	switch (bulletAttribute)
	{
		// 물속성() 탄환일 경우
	case UnitAttribute::Water:
	case UnitAttribute::Fire:
	{
		cout << "[Switch] 아무 일도 일어나지 않았다..\n\n";

		break;
	}


	// 풀속상 탄환일 경우
	case UnitAttribute::Grass:
	{
		if (!m_Door)
		{
			cout << "[Switch] 연결된 문이 없습니다!!! 문을 설정하세요~~\n\n";

			return;
		}
		// 문을 연다
		m_Door->OpenDoor();

		// 열면서 애니메이션 시작
		m_Door->StartAnim(m_Door->GetAnim());

		m_SwitchState = SwitchState::On;

		cout << "[Switch] 연결된 문을 엽니다!!\n\n";

		// 이미지 변경
		SetSprite(m_Sprite[1]);

		break;
	}
	}// end of switch
}

bool Switch::IsSwitchOn()
{
	
	return static_cast<int>(m_SwitchState);
}
