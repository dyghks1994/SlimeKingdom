#include "stdafx.h"
#include "Sign.h"

Sign::Sign(float spawnPosX, float spawnPosY, string str)
{
	// 태그 설정
	m_Tag = str;

	// 초기화
	Initialize(spawnPosX, spawnPosY);
}

Sign::~Sign()
{
}

void Sign::Initialize(const float spawnPosX, const float spawnPosY)
{
	// 활성화 상태로 설정
	this->m_Active = true;
	this->m_Visible = true;


	// 좌표 설정
	this->m_Transform.Position.x = spawnPosX;
	this->m_Transform.Position.y = spawnPosY;

	// 콜라이더 사이즈 설정
	this->m_pCollider->SetSize({ 80.0f, 60.0f });

	this->SetLayer(int(SLLayer::Object));


	//뎁스 설정
	m_pRenderer->m_Depth = (int)SLDepth::Object;

	// 스프라이트 세팅
	m_SignSprite = SLDataManager->GetSprite(m_Tag);		// 표지판 몸체

	// 스프라이트 적용
	SetSprite(m_SignSprite);

	// 각 표지판별 내용 이미지 설정
	if (m_Tag == "sign_1")
	{
		m_ContentsSprite = SLDataManager->GetSprite("sign_1_contents");
	}

	if (m_Tag == "sign_2")
	{
		m_ContentsSprite = SLDataManager->GetSprite("sign_2_contents");
	}

	if (m_Tag == "sign_3")
	{
		m_ContentsSprite = SLDataManager->GetSprite("sign_3_contents");
	}

	if (m_Tag == "sign_4")
	{
		m_ContentsSprite = SLDataManager->GetSprite("sign_4_contents");
	}

	if (m_Tag == "sign_5")
	{
		m_ContentsSprite = SLDataManager->GetSprite("sign_5_contents");
	}

	m_SignUI = new ImageUI();
	m_SignUI->m_Visible = false;
	m_SignUI->m_Depth = 2;
	m_SignUI->SetSprite(m_ContentsSprite);
	m_SignUI->m_Transform.Position.x = 960;
	m_SignUI->m_Transform.Position.y = 540;
}

void Sign::Update()
{

	if (m_WaitTime > 0.0f)
	{
		m_SignUI->m_Visible = false;
	}

	// 무언가와 충돌 했을 때
	if (!this->m_pCollider->m_Hits.empty())
	{
		// 충돌 프로세스
		Collision();
	}

	m_WaitTime -= 1.0f / 60.0f;
}

void Sign::Collision()
{
	//cout << "[Sign] 충돌 m_Hits.size = " << m_pCollider->m_Hits.size() << "\n";

	for (auto obj : m_pCollider->m_Hits)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(obj);

		//cout << "[Bush] 충돌 오브젝트의 tag = " << gameObject->m_Tag << "\n\n";

		// 플레이어랑 충돌 했을 때
		if (gameObject->m_Tag == "Player" && !m_SignUI->m_Visible && m_WaitTime <= 0.0f)
		{
			Player* player = dynamic_cast<Player*>(gameObject);

			// 표지판의 팝업창을 띄워준다
			m_SignUI->m_Visible = true;
			m_WaitTime = 1.0f;
			MGSceneManager->Pause = true;
			return;
		}
	}
}
