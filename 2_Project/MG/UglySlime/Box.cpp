#include "stdafx.h"
#include "Box.h"

Box::Box(float spawnPosX, float spawnPosY, JewelryAttribute jewelry, string name)
	: Gimmick(name)
{
	cout << "[Box] " << this << " 생성\n";
	
	// 태그 설정
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
	// 오브젝트 활성화
	m_Active = true;
	m_Visible = true;

	// 위치 설정
	m_Transform.Position.x = spawnPosX;
	m_Transform.Position.y = spawnPosY;

	// 콜라이더 사이즈 설정
	m_pCollider->SetSize({ 120.0f, 120.0f });

	// 박스 여는 시간 설정
	m_BoxOpenTime = 0.3f;

	// 상자 상태는 닫힌 상태로 초기화
	m_BoxState = BoxState::Closed;

	//뎁스 설정
	m_pRenderer->m_Depth = (int)SLDepth::Object;

	//스프라이트 세팅
	SetSprite(SLDataManager->GetSprite(m_Tag));

	// 보석 속성 설정
	m_JewelryAttribute = jewelry;

	/// 보석 타입(속성)에 따라서 애니메이션(이미지) 세팅
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
	// 이미 열린 상태면 
	if (IsOpened())
	{
		// 패스하자
		return;
	}

	// 충돌 했을 때
	if (!this->m_pCollider->m_Hits.empty())
	{
		// 충돌 프로세스
		Collision();
	}

	// 열기 시작해서 타이머가 동작중이라면 타이머를 돌리자
	if (m_BoxState == BoxState::Opening)
	{
		// 타이머 감소
		openTimer -= 1.0f / 60.0f;

		// 타이머가 다 돌았으면
		if (openTimer <= 0.0f)
		{
			// 열린 상태로 변경
			m_BoxState = BoxState::Opened;

			// 이미지 세팅
			SetSprite(SLDataManager->GetSprite("box_open"));

			// 애니메이션 중지
			SetAnimation(nullptr);
		}
	}
}

void Box::Collision()
{
	//cout << "[Box] 충돌 m_Hits.size = " << m_pCollider->m_Hits.size() << "\n";

	for (auto obj : m_pCollider->m_Hits)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(obj);

		//cout << "[Box] 충돌 오브젝트의 tag = " << gameObject->m_Tag << "\n\n";


		// 플레이어랑 충돌했을 때
		if (gameObject->m_Tag == "Player")
		{
			Player* player = dynamic_cast<Player*>(gameObject);

			// 상자 문을 연다.
			OpenBox();

			// 애니메이션 실행
			SetAnimation(m_Anim);

			// 플레이어의 가방에 보석을 추가한다.
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
	// 열려 있으면
	if (m_BoxState == BoxState::Opened)
	{
		// 트루
		return true;
	}

	// 닫혀 있거나 , 열리는 중이면
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
			cout << "[Box] " << this << "박스를 엽니다~~\n\n";

			// 열리는 중으로 상태 변경
			m_BoxState = BoxState::Opening;

			// 타이머 세팅
			openTimer = m_BoxOpenTime;

			// 박스 열리는 애니메이션 실행

			// 박스 열리는 효과음
			SoundManager::PlayEX("Box_Open");

			break;
		}

		case BoxState::Opening:
		{
			cout << "[Box] " << this << "박스 이미 여는 중~~\n\n";
			break;

		}

		case BoxState::Opened:
		{
			cout << "[Box] " << this << "박스 열려 있다!!\n\n";
			break;

		}
	}// end of switch
}
