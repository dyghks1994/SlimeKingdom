#include "stdafx.h"
#include "Door.h"

Door::Door(float spawnPosX, float spawnPosY, string name)
	: Gimmick(name)
{
	// 태그 설정
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
	// 활성화 상태로 설정
	this->m_Active = true;
	this->m_Visible = true;

	// 닫힌 상태로 설정
	m_State = DoorState::Closed;

	// 좌표 설정
	this->m_Transform.Position.x = spawnPosX;
	this->m_Transform.Position.y = spawnPosY;

	// 콜라이더 사이즈 설정
	this->m_pCollider->SetSize({ 120.0f, 100.0f });
	m_pCollider->m_Transform.Position.y = 5.0f;

	this->SetLayer(int(SLLayer::Object));

	// 문 열리는 속도(시간) 설정
	m_DoorOpenTime = 0.5f;

	//뎁스 설정
	m_pRenderer->m_Depth = (int)SLDepth::Object;

	// 스프라이트 세팅
	m_Sprite[0] = SLDataManager->GetSprite(m_Tag);
	m_Sprite[1] = SLDataManager->GetSprite("door_open");

	SetSprite(m_Sprite[0]);

	// 애니메이션 세팅
	m_Anim = new Animation(*SLDataManager->GetAnimation("door_opening"));
}

void Door::Update()
{
	// 열려 있다면
	if (IsOpened())
	{
		// 패스하자.
		return;
	}

	// 열기 시작해서 타이머가 동작중이라면 타이머를 돌리자
	if (m_State == DoorState::Opening)
	{
		// 타이머 감소
		openTimer -= 0.5f / 60.0f;

		int x = m_Transform.Position.x / (120 * 16);
		int y = m_Transform.Position.y / (120 * 9);
		MGCamera->m_Transform.Position = { (float)(1920 * x), (float)(1080 * y) };
		SLDataManager->m_pMapManager->SwitchingSection(x + (y * 3));


		// 타이머가 다 돌았으면
		if (openTimer <= 0.0f)
		{
			// 열린 상태로 변경
			m_State = DoorState::Opened;

			/// 문이 열리면 아예 비활성화 시킬까?
			/// 콜라이더만 0으로 만들어 버릴까?
			/// 활성화 상태에서 콜라이더만 0이면 렌더링은 되나?

			// 애니메이션 중지
			SetAnimation(nullptr);

			// 닫힌 이미지로 변경
			SetSprite(m_Sprite[1]);

			// 비 활성화 
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
	// 문이 열려 있으면
	if (m_State == DoorState::Opened)
	{
		return true;
	}

	// 닫혀 있거나 열리는 중
	return false;
}

void Door::OpenDoor()
{
	switch (m_State)
	{
	case DoorState::Closed:
	{
		cout << "[Door] " << this << "문을 엽니다~~\n\n";

		// 열리는 중으로 상태 변경
		m_State = DoorState::Opening;

		// 타이머 세팅
		openTimer = m_DoorOpenTime;

		// 문 열리는 애니메이션 실행
		SoundManager::PlayEX("Door_Open");

		break;
	}

	case DoorState::Opening:
	{
		//cout << "[Door] " << this << "문 이미 여는 중~~\n\n";
		break;

	}

	case DoorState::Opened:
	{
		cout << "[Door] " << this << "문 이미 열려 있다!!\n\n";
		break;

	}
	}
}
