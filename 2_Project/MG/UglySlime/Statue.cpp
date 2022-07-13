#include "stdafx.h"
#include "Statue.h"


Statue::Statue(float spawnPosX, float spawnPosY, StatueType type, string str)
	: Gimmick(str)
{
	// 태그 값
	m_Tag = str;
	m_Type = type;

	Initialize(spawnPosX, spawnPosY);
}

Statue::~Statue()
{
}

void Statue::Initialize(const float spawnPosX, const float spawnPosY)
{
	// 배치(활성화)상태로 설정
	m_Active = true;
	m_Visible = true;

	// 스폰 포인트에 위치시킨다
	m_Transform.Position.x = spawnPosX;
	m_Transform.Position.y = spawnPosY;

	// 슬라임 킹 석상은  콜라이더 사이즈를 좀 크게 설정해주자
	if (m_Tag == "statue_king_off")
	{
		m_pCollider->SetSize({ 200.0f, 180.0f });
		m_pCollider->m_Transform.Position.y += 20.0f;
	}
	
	// 나머지는 보통 타일 사이즈로 설정해주자.
	else
	{
		m_pCollider->SetSize({ 100.0f, 100.0f });
		m_pCollider->m_Transform.Position.y += 5.0f;
	}

	SetLayer((int)SLLayer::Object);

	//뎁스 설정
	m_pRenderer->m_Depth = (int)SLDepth::Object;

	/// 석상 종류에 따라서 이미지 세팅하면 되겠지?
	SetSprite(SLDataManager->GetSprite(m_Tag));
	
}

void Statue::Update()
{
	// 석상에 보석이 부착되있다면
	if (m_AttachedJewelry)
	{
		// 패스 하자
		return;
	}

	// 무언가와 충돌 했을 때
	if (!this->m_pCollider->m_Hits.empty())
	{
		// 충돌 프로세스
		Collision();
	}
}

void Statue::Collision()
{
	//cout << "[Statue] 충돌 m_Hits.size = " << m_pCollider->m_Hits.size() << "\n";

	for (auto obj : m_pCollider->m_Hits)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(obj);

		cout << "[Statue] 충돌 오브젝트의 tag = " << gameObject->m_Tag << "\n\n";


		// 플레이어랑 충돌 했을 때 
		if (gameObject->m_Tag == "Player")
		{
			Player* player = dynamic_cast<Player*>(gameObject);

			// 먼저 플레이어의 가방(보석 획득) 정보를 얻는다.
			uint bag = player->GetPlayerBag();

			if (bag == 0)
			{
				cout << "[System] 가방이 비어있다!!!\n\n";
				continue;
			}

			AttachJewelry(bag);
		}
	}
}

void Statue::AttachJewelry(uint bag)
{
	/// 석상 종류에 따라서 이미지 세팅하면 되겠지?
	switch (m_Type)
	{
		// 석상 타입이 물일 때
		case StatueType::Water:	
		{
			// 플레이어의 가방에 물 보석이 있다면
			if (bag & PlayerBag::Water)
			{
				// 물보석 박힌 이미지로 변경
				SetSprite(SLDataManager->GetSprite("statue_water_on"));
				SoundManager::PlayEX("Statue_On");

				/// 보석을 박은 상태로 바꾸고 이미지를 바꾸자
				m_AttachedJewelry = true;

				cout << "[석상] 보석 장착 성공!! <타입 -> " << static_cast<int>(m_Type) << ">\n\n";


				/// 게임 디자인(설계)상 물 석상이 마지막 지점
				/// 물 석상에 보석이 박히면 킹슬라임 석상을 활성화 시킨다.
				/// 
				
			}
			break;
		}
		
		// 석상 타입이 불일 때
		case StatueType::Fire:
		{
			// 플레이어의 가방에 불 보석이 있다면
			if (bag & PlayerBag::Fire)
			{
				// 불 보석 박힌 이미지로 변경
				SetSprite(SLDataManager->GetSprite("statue_fire_on"));
				SoundManager::PlayEX("Statue_On");

				/// 보석을 박은 상태로 바꾸고 이미지를 바꾸자
				m_AttachedJewelry = true;

				cout << "[석상] 보석 장착 성공!! <타입 -> " << static_cast<int>(m_Type) << ">\n\n";

			}
			break;
		}

		// 석상 타입이 풀일 때
		case StatueType::Grass:
		{
			// 플레이어의 가방에 풀 보석이 있다면
			if (bag & PlayerBag::Grass)
			{
				// 풀 보석 박힌 이미지로 변경
				SetSprite(SLDataManager->GetSprite("statue_leaf_on"));
				SoundManager::PlayEX("Statue_On");

				/// 보석을 박은 상태로 바꾸고 이미지를 바꾸자
				m_AttachedJewelry = true;

				cout << "[석상] 보석 장착 성공!! <타입 -> " << static_cast<int>(m_Type) << ">\n\n";
			}
			break;
		}
	}
	
}

bool Statue::IsAttachedJewelry()
{
	return m_AttachedJewelry;
}
