#include "stdafx.h"
#include "Sign.h"

Sign::Sign(float spawnPosX, float spawnPosY, string str)
{
	// �±� ����
	m_Tag = str;

	// �ʱ�ȭ
	Initialize(spawnPosX, spawnPosY);
}

Sign::~Sign()
{
}

void Sign::Initialize(const float spawnPosX, const float spawnPosY)
{
	// Ȱ��ȭ ���·� ����
	this->m_Active = true;
	this->m_Visible = true;


	// ��ǥ ����
	this->m_Transform.Position.x = spawnPosX;
	this->m_Transform.Position.y = spawnPosY;

	// �ݶ��̴� ������ ����
	this->m_pCollider->SetSize({ 80.0f, 60.0f });

	this->SetLayer(int(SLLayer::Object));


	//���� ����
	m_pRenderer->m_Depth = (int)SLDepth::Object;

	// ��������Ʈ ����
	m_SignSprite = SLDataManager->GetSprite(m_Tag);		// ǥ���� ��ü

	// ��������Ʈ ����
	SetSprite(m_SignSprite);

	// �� ǥ���Ǻ� ���� �̹��� ����
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

	// ���𰡿� �浹 ���� ��
	if (!this->m_pCollider->m_Hits.empty())
	{
		// �浹 ���μ���
		Collision();
	}

	m_WaitTime -= 1.0f / 60.0f;
}

void Sign::Collision()
{
	//cout << "[Sign] �浹 m_Hits.size = " << m_pCollider->m_Hits.size() << "\n";

	for (auto obj : m_pCollider->m_Hits)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(obj);

		//cout << "[Bush] �浹 ������Ʈ�� tag = " << gameObject->m_Tag << "\n\n";

		// �÷��̾�� �浹 ���� ��
		if (gameObject->m_Tag == "Player" && !m_SignUI->m_Visible && m_WaitTime <= 0.0f)
		{
			Player* player = dynamic_cast<Player*>(gameObject);

			// ǥ������ �˾�â�� ����ش�
			m_SignUI->m_Visible = true;
			m_WaitTime = 1.0f;
			MGSceneManager->Pause = true;
			return;
		}
	}
}
