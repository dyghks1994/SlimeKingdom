#include "stdafx.h"

Player::Player(string name)
	: Unit(name)
{
	this->m_Attribute = UnitAttribute::None;	// ���Ӽ� ���·�

	this->m_LookVector = { 0.0f,1.0f };

	this->m_Active = true;
	this->m_Visible = true;
	this->m_Tag = "Player";

	this->m_pRenderer->m_Depth = (int)SLDepth::Object;

	this->m_MoveSpeed = 9.0f;
	this->m_Life = 3;
	this->m_CurrentHp = 3;
	this->m_MaxHp = 3;
	this->m_Transform.Position.x = 200;
	this->m_Transform.Position.y = 200;
	this->m_pCollider->m_Size.width = 80;
	this->m_pCollider->m_Size.height = 80;
	this->m_pCollider->m_Transform.Position.y = 10;

	this->m_SkillGauge = 0;		// ���� ������
	//this->m_SkillGauge = 100;		// �ϴ��� �׽�Ʈ ���� ó���� 100���� ������. 

	// ó���� �������� ���·� ����
	// �������� 0����
	m_State = PlayerState::Live;

	this->SetLayer((int)SLLayer::Player);

	// �߻�ü �ʱ�ȭ
	for (int i = 0; i < MAX_BULLET_SIZE; i++)
	{
		// �߻�ü �̸� ����
		m_Bullets[i] = new Bullet(this);	// �߻� ��ü(����)�� ������ �˷���
		m_Bullets[i]->SetLayer((int)SLLayer::Player_Atk);
	}

	//UI ����
	this->InitUI();

	SetMyAnimation();
}

Player::~Player()
{
	for (int i = 0; i < MAX_BULLET_SIZE; i++)
	{
		// �߻�ü �޸� ����
		delete m_Bullets[i];
	}
}

void Player::Reset()
{
	this->m_Attribute = UnitAttribute::None;	// ���Ӽ� ���·�
	this->m_LookVector = { 0.0f,1.0f };
	this->m_Life = 3;
	this->m_CurrentHp = 3;

	this->m_SkillGauge = 0;		// ���� ������

	m_KingWakeup = false;
	m_GameClear = false;

	m_PlayerBag = 0;

	m_State = PlayerState::Live;

	for (int i = 0; i < MAX_BULLET_SIZE; i++)
	{
		m_Bullets[i]->m_Transform.Position = { 0,0 };
		m_Bullets[i]->m_Transform.Angle = 0;
		m_Bullets[i]->SetLayer((int)SLLayer::Player_Atk);
	}
}

void Player::SetMyAnimation()
{
	string attribute[] = { "slime", "water_slime", "fire_slime", "grass_slime" };
	string dirStr[] = { "","_B","_L","_R" };
	string stateName[] = { "_idle","_move", "_eat", "_hurt","_attack" };

	m_AnimState = PlayerAnimState::Idle;
	m_AnimDir = AnimDir::F;


	//SLDataManager�� �ִϸ��̼��� �̿��Ͽ� ���ο� �ִϸ��̼� ����
	for (int att = 0; att < (int)UnitAttribute::AttributeNum; att++)
	{
		for (int state = 0; state < (int)PlayerAnimState::AnimStateNum; state++)
		{
			for (int dir = 0; dir < (int)AnimDir::DirNum; dir++)
			{
				string animName = attribute[att] + stateName[state] + dirStr[dir];
				Animation tempAnim = *SLDataManager->GetAnimation(animName);
				anims[att][state][dir] = new Animation(tempAnim);
			}
		}
	}

	m_EndingAnim = new Animation(*SLDataManager->GetAnimation("playerEnding"));

	for (int att = 0; att < (int)UnitAttribute::AttributeNum; att++)
	{
		for (int dir = 0; dir < (int)AnimDir::DirNum; dir++)
		{
			anims[att][(int)PlayerAnimState::Attack][dir]->m_IsLoop = false;
		}
	}

	this->SetAnimation(anims[(int)m_Attribute][(int)m_AnimState][(int)m_AnimDir]);
}

void Player::UpdateAnimState()
{
	//Animation ���� üũ
	//�̵� ���� üũ
	if (GetDirect().x == 0 && GetDirect().y == 0)
	{
		m_AnimState = PlayerAnimState::Idle;
	}
	else
	{
		m_AnimState = PlayerAnimState::Move;
	}
	//�̵� üũ ���� ���� üũ
	if (m_State & PlayerState::Absorb)
	{
		m_AnimState = PlayerAnimState::Eat;
	}
	if (m_State & PlayerState::Hit)
	{
		m_AnimState = PlayerAnimState::Hit;
	}
	if (m_State & PlayerState::Attacking)
	{
		m_AnimState = PlayerAnimState::Attack;
	}

	//���� üũ
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

	Animation* nowAnim = anims[(int)m_Attribute][(int)m_AnimState][(int)m_AnimDir];
	if (m_pAnimation != nowAnim)
	{
		nowAnim->Reset();
		SetAnimation(nowAnim);
	}
}

void Player::InitUI()
{
	// ��ų������ UI �ʱ�ȭ
	m_SkillGaugeBase = new RectUI();
	m_SkillGaugeBase->m_Transform.Position.x = 275;
	m_SkillGaugeBase->m_Transform.Position.y = 105;
	m_SkillGaugeBase->m_Size.width = 290;
	m_SkillGaugeBase->m_Size.height = 50;
	m_SkillGaugeBase->m_Color = D2D1::ColorF(D2D1::ColorF(0.37f, 0.37f, 0.37f, 1.0f));
	m_SkillGaugeBase->m_Depth = -1;

	m_SkillGaugeBar = new RectUI();
	m_SkillGaugeBar->m_Transform.Position.x = 275;
	m_SkillGaugeBar->m_Transform.Position.y = 105;
	m_SkillGaugeBar->m_Size.width = 290;
	m_SkillGaugeBar->m_Size.height = 50;
	m_SkillGaugeBar->m_Depth = 0;

	Sprite* tempSprite;			// Image UI�� �ʱ�ȭ �ϱ� ���� ����

	// �÷��̾� �Ӽ�UI �ʱ�ȭ
	m_states[0] = SLDataManager->GetSprite("ui_stateGray");
	m_states[1] = SLDataManager->GetSprite("ui_stateBlue");
	m_states[2] = SLDataManager->GetSprite("ui_stateRed");
	m_states[3] = SLDataManager->GetSprite("ui_stateGreen");
	m_AttributeBar = new ImageUI();
	tempSprite = m_states[0];								// ���Ӽ� default
	m_AttributeBar->SetSprite(tempSprite);
	m_AttributeBar->m_Transform.Position.x = 32 + tempSprite->m_pBitmap->GetSize().width * 0.5f;
	m_AttributeBar->m_Transform.Position.y = 30 + tempSprite->m_pBitmap->GetSize().height * 0.5f;

	// ������ UI �ʱ�ȭ(������ �Ƿ翧)
	m_LifeImageUI = new ImageUI();
	tempSprite = SLDataManager->GetSprite("ui_life");
	m_LifeImageUI->SetSprite(tempSprite);
	m_LifeImageUI->m_Transform.Position.x = m_AttributeBar->m_Transform.Position.x
		+ (m_AttributeBar->m_pRenderer->GetSprite()->m_pBitmap->GetSize().width * 0.3f);
	m_LifeImageUI->m_Transform.Position.y = 26 + tempSprite->m_pBitmap->GetSize().height * 0.5f;

	// ������ UI �ʱ�ȭ(����)
	m_LifeNumber[0] = SLDataManager->GetSprite("ui_num00");
	m_LifeNumber[1] = SLDataManager->GetSprite("ui_num01");
	m_LifeNumber[2] = SLDataManager->GetSprite("ui_num02");
	m_LifeNumber[3] = SLDataManager->GetSprite("ui_num03");
	m_LifeNumUI = new ImageUI();
	tempSprite = m_LifeNumber[3];							// ������ 3 default
	m_LifeNumUI->SetSprite(tempSprite);
	m_LifeNumUI->m_Transform.Position.x = 408 + tempSprite->m_pBitmap->GetSize().width * 0.5f;
	m_LifeNumUI->m_Transform.Position.y = 33 + tempSprite->m_pBitmap->GetSize().height * 0.5f;

	// ������ UI �ʱ�ȭ(��Ʈ)
	for (int i = 0; i < 3; i++)
	{
		m_HeartUI[i] = new ImageUI();
		tempSprite = SLDataManager->GetSprite("ui_heartOn");
		m_HeartUI[i]->SetSprite(tempSprite);
		m_HeartUI[i]->m_Transform.Position.x = m_AttributeBar->m_Transform.Position.x
			+ 90
			+ ((tempSprite->m_pBitmap->GetSize().width + 9) * i);
		m_HeartUI[i]->m_Transform.Position.y = m_AttributeBar->m_Transform.Position.y
			+ (m_AttributeBar->m_pRenderer->GetSprite()->m_pBitmap->GetSize().height * 0.4f)
			+ 8
			+ (tempSprite->m_pBitmap->GetSize().height * 0.5f);
	}

	// ���� UI �ʱ�ȭ
	for (int i = 0; i < 3; i++)
	{
		m_JewelUI[i] = new ImageUI();
		tempSprite = SLDataManager->GetSprite("ui_jewelOff");	// ���� ���� default
		m_JewelUI[i]->SetSprite(tempSprite);
		m_JewelUI[i]->m_Transform.Position.x = 1672 + ((tempSprite->m_pBitmap->GetSize().width + 9) * i);
		m_JewelUI[i]->m_Transform.Position.y = 20 + (tempSprite->m_pBitmap->GetSize().height * 0.5f);;
	}
	m_Jewel[0] = SLDataManager->GetSprite("ui_jewelGreen");
	m_Jewel[1] = SLDataManager->GetSprite("ui_jewelBlue");
	m_Jewel[2] = SLDataManager->GetSprite("ui_jewelRed");
}

void Player::UIUpdate()
{
	// �Ӽ� UI
	m_AttributeBar->SetSprite(m_states[(int)m_Attribute]);

	switch ((int)m_Attribute)
	{
	case 1: // ��
		m_SkillGaugeBar->m_Color = D2D1::ColorF(D2D1::ColorF(0.41f, 0.8f, 0.92f, 1.0f));
		break;
	case 2: // ��
		m_SkillGaugeBar->m_Color = D2D1::ColorF(D2D1::ColorF(1.0f, 0.54f, 0.2f, 1.0f));
		break;
	case 3: // Ǯ
		m_SkillGaugeBar->m_Color = D2D1::ColorF(D2D1::ColorF(0.4f, 0.82f, 0.92f, 0.32f));
		break;
	}
	m_SkillGaugeBar->m_FillAmount = (float)m_SkillGauge * 0.01f;

	// ������ UI
	m_LifeNumUI->SetSprite(m_LifeNumber[m_Life]);

	// Hp UI
	for (int i = 2; i >= 0; i--)
	{
		if (i >= m_CurrentHp)
		{
			m_HeartUI[i]->SetSprite(SLDataManager->GetSprite("ui_heartOff"));
		}
		else
		{
			m_HeartUI[i]->SetSprite(SLDataManager->GetSprite("ui_heartOn"));
		}
	}

	// ���� UI
	if (m_PlayerBag & PlayerBag::Grass)
	{
		m_JewelUI[0]->SetSprite(m_Jewel[0]);
	}
	else
	{
		m_JewelUI[0]->SetSprite(SLDataManager->GetSprite("ui_jewelOff"));
	}


	if (m_PlayerBag & PlayerBag::Water)
	{
		m_JewelUI[1]->SetSprite(m_Jewel[1]);
	}
	else
	{
		m_JewelUI[1]->SetSprite(SLDataManager->GetSprite("ui_jewelOff"));
	}

	if (m_PlayerBag & PlayerBag::Fire)
	{
		m_JewelUI[2]->SetSprite(m_Jewel[2]);
	}
	else
	{
		m_JewelUI[2]->SetSprite(SLDataManager->GetSprite("ui_jewelOff"));
	}
	//MGGraphicEngine->SetTransform(m_Transform.GetSRMatrix());
	//MGGraphicEngine->SetTransform(D2D1::Matrix3x2F::Identity());


	//MGGraphicEngine->SetTransform(GetTransform().GetSRMatrix());
	//D2D1_POINT_2F drawStartPoint = {100.0f, 100.f};
	//D2D1_POINT_2F drawEndPoint;
	//drawEndPoint.x = drawStartPoint.x * m_SkillGauge;
	//drawEndPoint.y = drawStartPoint.y;
	//
	//MGGraphicEngine->DrawRectangle(drawStartPoint, drawEndPoint.x, drawEndPoint.y, CollisionColor);
	//MGGraphicEngine->SetTransform(D2D1::Matrix3x2F::Identity());

}

void Player::Update()
{
	if (KeyInput->InputKeyDown(VK_A))
	{
		system("cls");
	}

	/// �÷��̾ �׾� ������
	if (IsDead())
	{
		// ������Ʈ ���� �ʴ´�.
		return;
	}

	if (m_GameClear)
	{
		if (m_pAnimation == nullptr)
		{
			return;
		}

		if((m_pAnimation->m_NowIndex == (m_pAnimation->m_pSprites.size() - 1))
			&&(m_pAnimation->m_TotalDelay >= 10.0f - m_pAnimation->m_Speed))
		{
			SetAnimation(nullptr);
		}
		return;
	}

	/// ��������� ������ ������. Update

	// �ǰ� ���̸� �ǰ� Ÿ�̸Ӹ� ������.
	if (m_State & PlayerState::Hit)
	{
		// ��Ʈ Ÿ�̸� ������
		hitTimer -= 1.0f / 60.0f;

		// �ǰ� �ð� ������
		if (hitTimer <= 0)
		{
			cout << "[Player] �ǰ� ��~\n\n";

			// �ǰ� ���� ����
			m_State &= ~PlayerState::Hit;
		}
	}

	if (!this->m_pCollider->m_Hits.empty())
	{
		// �浹 ���μ���
		Collision();
	}

	if (m_GameClear)
	{
		return;
	}

	// �̵�
	Move();

	// ����(�Ӽ�) ���
	Absorb();

	// �߻� ���� ��ƾ
	Shoot();

	// ��ų(����)������ ����
	DecreasesGauge();

	/// �ӽ� �׽�Ʈ��
	// �ֿܼ� �÷��̾� ���� ���
	if (KeyInput->InputKeyDown(VK_C))
	{
		ShowPlayerStateToConsole();
	}

	// �ǰ� �Լ� �׽�Ʈ�� ȣ��
	if (KeyInput->InputKeyDown(VK_V))
	{
		ReceiveAttack();
	}

	if (KeyInput->InputKeyDown(VK_2))
	{
		ChangeAttribute(UnitAttribute::Water);
	}

	if (KeyInput->InputKeyDown(VK_3))
	{
		ChangeAttribute(UnitAttribute::Fire);
	}

	if (KeyInput->InputKeyDown(VK_4))
	{
		ChangeAttribute(UnitAttribute::Grass);
	}

	if (m_Attribute != UnitAttribute::None && m_SkillGauge <= 0)
	{
		ChangeAttribute(UnitAttribute::None);
	}

	if (KeyInput->InputKeyDown(VK_Q))
	{
		SetMoveSpeed(m_MoveSpeed - 1.0f);
	}

	if (KeyInput->InputKeyDown(VK_W))
	{
		SetMoveSpeed(m_MoveSpeed + 1.0f);
	}

	if (KeyInput->InputKeyDown(VK_F7))
	{
		m_PlayerBag |= PlayerBag::Fire;
		m_PlayerBag |= PlayerBag::Water;
		m_PlayerBag |= PlayerBag::Grass;
	}

	//Animation State ����
	UpdateAnimState();

	//UI ����
	UIUpdate();
}

void Player::Move()
{
	/// ���� Ű �Է�(�̵�) �Ұ�
	static int FPS = 0;

	// �� �̵�
	if (KeyInput->InputKey(VK_RIGHT))
	{

		m_LookVector = { +1.0f, 0.0f };

		m_Transform.Position.x += m_LookVector.x * m_MoveSpeed;
		m_Transform.Position.y += m_LookVector.y * m_MoveSpeed;
	}

	// �� �̵�
	else if (KeyInput->InputKey(VK_LEFT))
	{
		m_LookVector = { -1.0f, 0.0f };

		m_Transform.Position.x += m_LookVector.x * m_MoveSpeed;
		m_Transform.Position.y += m_LookVector.y * m_MoveSpeed;
	}

	// �� �̵�
	else if (KeyInput->InputKey(VK_UP))
	{
		m_LookVector = { 0.0f, -1.0f };

		m_Transform.Position.x += m_LookVector.x * m_MoveSpeed;
		m_Transform.Position.y += m_LookVector.y * m_MoveSpeed;
	}

	// �� �̵�
	else if (KeyInput->InputKey(VK_DOWN))
	{
		m_LookVector = { 0.0f, +1.0f };

		m_Transform.Position.x += m_LookVector.x * m_MoveSpeed;
		m_Transform.Position.y += m_LookVector.y * m_MoveSpeed;
	}

	if (GetDirect().x != 0 || GetDirect().y != 0)
	{
		FPS++;
	}

	if (FPS > 18)
	{
		SoundManager::PlayEX("Ch_Move");
		FPS = 0;
	}

}

void Player::ReceiveAttack()
{
	// ��Ʈ Ÿ�̸� �ʱ�ȭ

	// ��� �������� üũ����
	uint absorbState = m_State & PlayerState::Absorb;

	// ��� ���� ���¶��
	if (absorbState)
	{
		// ������ ���(�Ӽ� ��ȯ) �Ѵ�
		ChangeAttribute(UnitAttribute::Water);
	}

	// �ǰݴ��� ��
	else
	{
		// �ǰ� ���� ����
		uint hitState = m_State & PlayerState::Hit;

		// �̹� �ǰ� ���̸� ��ٸ���.
		if (hitState)
		{
			cout << "[Player] �̹� �ǰ���~\n";

			return;
		}

		// ĳ���� �ǰݽ� ȿ����
		SoundManager::PlayEX("Ch_Hit");

		// ��Ʈ(�ǰ�) ���� �߰�
		m_State |= PlayerState::Hit;

		// ��Ʈ Ÿ�̸� ����
		hitTimer = m_Hit_Interval;

		// Hp 1 ����;
		this->m_CurrentHp--;

		cout << "[Player] �ǰ� I'm Hit!!!\n";
		cout << "[Player] ���� Hp = " << m_CurrentHp << "\n\n";

		// �ϴ� ��ġ�� ��¦ ������ ����.
		// ���� ���
		//float dirX = gameObject->m_Transform.Position.x - this->GetDirect().x
		//this->m_Transform.Position.x += 500;
		//this->m_Transform.Position.y += 500;

		// Hp üũ
		if (this->m_CurrentHp < 0)
		{
			// ������ ����
			if (m_Life >= 1)
			{
				m_Life -= 1;
				m_CurrentHp = 3;
			}
			// ��� ���·� ����
			else
			{
				m_State &= ~PlayerState::Live;
				SoundManager::PlayEX("Ch_Dead");
			}
		}

		ShowPlayerStateToConsole();
	}
}

void Player::ReceiveAttack(GameObject* gameObject)
{
	/// �ǰݴ����� ��
	/// ��� ���̸� �Ӽ�(��ų)�� ����ϰ� �ϰ�
	/// ��� ���� �ƴϸ� ü���� ������ ����

	// ��Ʈ Ÿ�̸� �ʱ�ȭ

	// ��� �������� üũ����
	uint absorbState = m_State & PlayerState::Absorb;

	// ��� ���� ���¶��
	if (absorbState && gameObject->m_Tag == "Bullet")
	{
		Bullet* bullet = dynamic_cast<Bullet*>(gameObject);

		if (bullet)
		{
			//���� ���� üũ
			//0�� ��->�Ʒ�
			//90�� ����->������
			//180�� �Ʒ�->��
			//-90�� ������->����
			float angle = bullet->m_pRenderer->m_Transform.Angle;
			bool isDir = false;
			if (((GetLookVector().x == -1.0f) && angle == -90)
				|| ((GetLookVector().x == 1.0f) && angle == 90)
				|| ((GetLookVector().y == -1.0f) && angle == 0)
				|| ((GetLookVector().y == 1.0f) && angle == 180))
			{
				isDir = true;
			}

			//������ ������ ������ ���(�Ӽ� ��ȯ) �Ѵ�
			if (isDir)
			{
				ChangeAttribute(bullet->GetAttribute());
			}

			// ������ �ٸ���
			else
			{
				// �ǰ� ���� ����
				uint hitState = m_State & PlayerState::Hit;

				// �̹� �ǰ� ���̸� ��ٸ���.
				if (hitState)
				{
					cout << "[Player] �̹� �ǰ���~\n";

					return;
				}

				// ĳ���� �ǰݽ� ȿ����
				SoundManager::PlayEX("Ch_Hit");

				// ��Ʈ(�ǰ�) ���� �߰�
				m_State |= PlayerState::Hit;

				// ��Ʈ Ÿ�̸� ����
				hitTimer = m_Hit_Interval;

				// Hp 1 ����;
				this->m_CurrentHp--;

				cout << "[Player] �ǰ� I'm Hit!!!\n";
				cout << "[Player] ���� Hp = " << m_CurrentHp << "\n\n";

				/// �ϴ� ��ġ�� ��¦ ������ ����.
				float dirX = gameObject->GetDirect().x;
				float dirY = gameObject->GetDirect().y;


				// �׽�Ʈ�� �����ִ� ������Ʈ�� �ε����� �� �ӽ÷� ������ �����Ѵ�.
				if (dirX == 0.0f && dirY == 0.0f)
				{
					dirX = -1.0f;	// �����δ� ���ͳ� bullet�� �ε����״� �Ƹ� ��� �� ���̴�.
				}

				this->m_Transform.Position.x += dirX * 50.0f;
				this->m_Transform.Position.y += dirY * 50.0f;

				// Hp üũ
				if (this->m_CurrentHp < 0)
				{
					// ������ ����
					if (m_Life >= 1)
					{
						m_Life -= 1;
						m_CurrentHp = 3;
					}
					// ��� ���·� ����
					else
					{
						m_State &= ~PlayerState::Live;
					}
				}

				ShowPlayerStateToConsole();
			}

		}

	}

	// �ǰݴ��� ��
	else
	{
		// �ǰ� ���� ����
		uint hitState = m_State & PlayerState::Hit;

		// �̹� �ǰ� ���̸� ��ٸ���.
		if (hitState)
		{
			cout << "[Player] �̹� �ǰ���~\n";

			return;
		}

		// ĳ���� �ǰݽ� ȿ����
		SoundManager::PlayEX("Ch_Hit");

		// ��Ʈ(�ǰ�) ���� �߰�
		m_State |= PlayerState::Hit;

		// ��Ʈ Ÿ�̸� ����
		hitTimer = m_Hit_Interval;

		// Hp 1 ����;
		this->m_CurrentHp--;

		cout << "[Player] �ǰ� I'm Hit!!!\n";
		cout << "[Player] ���� Hp = " << m_CurrentHp << "\n\n";

		/// �ϴ� ��ġ�� ��¦ ������ ����.
		float dirX = gameObject->GetDirect().x;
		float dirY = gameObject->GetDirect().y;


		// �׽�Ʈ�� �����ִ� ������Ʈ�� �ε����� �� �ӽ÷� ������ �����Ѵ�.
		if (dirX == 0.0f && dirY == 0.0f)
		{
			dirX = -1.0f;	// �����δ� ���ͳ� bullet�� �ε����״� �Ƹ� ��� �� ���̴�.
		}

		this->m_Transform.Position.x += dirX * 50.0f;
		this->m_Transform.Position.y += dirY * 50.0f;

		// Hp üũ
		if (this->m_CurrentHp < 0)
		{
			// ������ ����
			if (m_Life >= 1)
			{
				m_Life -= 1;
				m_CurrentHp = 3;
			}
			// ��� ���·� ����
			else
			{
				m_State &= ~PlayerState::Live;
			}
		}

		ShowPlayerStateToConsole();
	}
}

void Player::Absorb()
{
	/// ����� ����� Ÿ�̸�
	static float coolTimer = 0.0f;		// ��Ÿ�� Ÿ�̸�
	static float durationTimer = 0.0f;		// ���ӽð� Ÿ�̸�

	/// ĳ������ ��� ���� ���� ����
	uint absorbState = m_State & PlayerState::Absorb;

	/// ��� ��Ÿ���� ��
	if (coolTimer > 0.0f)
	{
		// dTime(����Ÿ��?) ��ŭ Ÿ�̸� ��
		coolTimer -= 1.0f / 60.0f;		// �ӽ÷� ����� ��������

		//cout << coolTimer << "\n";

		// Ÿ�̸Ӱ� 0�� �Ǹ�
		if (coolTimer <= 0.0f)
		{
			// ��� �õ� ���� ���·� ����
			cout << "[Player] ��� ��Ÿ�� ��~~\n\n";
		}
	}

	/// ��� ����(�׼�) ���̸�
	if (absorbState) // ==> if (absorbState == PlayerState::Absorb)
	{
		//cout << "��� ���� ��\n";

		durationTimer -= 1.0f / 60.0f;		// ���ӽð� ����
		//cout << durationTimer << "\n\n";

		// ���ӽð��� ������
		if (durationTimer <= 0.0f)
		{
			// ��� ���� ����
			m_State &= ~PlayerState::Absorb;

			cout << "[Player] ��� �׼� ��~\n";

			// �ִϸ��̼ǵ� �����ؾ� �Ѵ�.
		}
	}


	/// 'Z' Ű�� ������
	if (KeyInput->InputKeyDown(VK_Z))
	{
		/// ��� �����ϸ�
		// -> ��Ÿ�� ���Ұ�, �÷��̾ ������� �ƴ� ���¸�
		if (coolTimer <= 0 && absorbState == false)
		{
			cout << "[Player] ��� ����~\n";

			// ��� �Ұ��� ���·� ����(��Ÿ�� ������)

			// ��Ÿ�� Ÿ�̸� ����
			coolTimer = m_Absorb_Delay;

			// ĳ���͸� ����ϴ� ���·� ����(������ ��� ����)
			m_State |= PlayerState::Absorb;

			// ���ӽð� Ÿ�̸� ����
			durationTimer = m_Absorb_Duration;

			// ����ϴ� �ִϸ��̼� ����(����) �ؾ���

			SoundManager::PlayEX("Ch_Absorb");
		}

		/// ��� �Ұ����ϸ�
		else
		{
			// �̹� �����
			if (absorbState)
			{
				cout << "[Player] �̹� ��� �� �Դϴ�~\n";
			}

			// ��Ÿ�� ��ٸ��� ��
			else
			{
				cout << "[Player] ��� ��Ÿ�� ���� ��~ !!\n";
			}
		}
	}
}

void Player::ChangeAttribute(UnitAttribute attribute)
{
	cout << "[Player] ChangeAttribute(UnitAttribute attribute) ȣ��\n";

	uint absorbState = m_State & PlayerState::Absorb;

	if (m_State == false)
	{
		cout << "[Player] �̹� ��� ��~\n\n";

		return;
	}

	// �Ӽ��� ��ȯ�ϰ�
	cout << "[Player] �Ӽ� ��ȯ (" << static_cast<int>(m_Attribute);
	m_Attribute = attribute;
	cout << " - > " << static_cast<int>(m_Attribute) << ") ~~\n";

	// ��ų�������� ȸ��
	m_SkillGauge = (m_Attribute == UnitAttribute::None) ? 0 : m_Skill_Gauge_Max;
	cout << "[Player] ��ų(����) ������ ȸ��!\n\n";

	//�ִϸ��̼� ����
	UpdateAnimState();
}

void Player::Collision()
{
	//cout << "[Player] �浹 m_Hits.size = " << m_pCollider->m_Hits.size() << "\n";

	for (auto obj : this->m_pCollider->m_Hits)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(obj);

		//cout << "[Player] �浹 ������Ʈ�� tag = " << gameObject->m_Tag << "\n\n";

		// �浹�� ������Ʈ�� Monster �ΰ�쿡
		if (gameObject->m_Tag == "Mon_Water" ||
			gameObject->m_Tag == "Mon_Fire" ||
			gameObject->m_Tag == "Mon_Grass")
		{
			Monster* monster = dynamic_cast<Monster*>(gameObject);

			// �ǰ� ó���� �Ѵ�.
			ReceiveAttack(monster);
		}

		// �浹�� ������Ʈ�� bullet�� ��쿡
		if (gameObject->m_Tag == "Bullet")
		{
			Bullet* bullet = dynamic_cast<Bullet*>(gameObject);

			// �� bullet�� ���Ͱ� Monster �̶��
			if (bullet->m_Shooter->m_Tag == "Mon_Water" ||
				bullet->m_Shooter->m_Tag == "Mon_Fire" ||
				bullet->m_Shooter->m_Tag == "Mon_Grass")
			{
				// �ǰ� ó���� �Ѵ�.
				ReceiveAttack(bullet);
			}
		}

		// �浹�� ������Ʈ�� ������ ��쿡
		if (gameObject->m_Tag == "statue_water_off" ||
			gameObject->m_Tag == "statue_fire_off" ||
			gameObject->m_Tag == "statue_leaf_off")
		{
			/// ��� ������ ������ ������ �ִٸ�
			Statue* waterSlimeStatue = dynamic_cast<Statue*>(MGSceneManager->GetNowScene()->m_pGameObjectManager->FindGameObject("statue_water_off"));
			Statue* fireSlimeStatue = dynamic_cast<Statue*>(MGSceneManager->GetNowScene()->m_pGameObjectManager->FindGameObject("statue_fire_off"));
			Statue* grassSlimeStatue = dynamic_cast<Statue*>(MGSceneManager->GetNowScene()->m_pGameObjectManager->FindGameObject("statue_leaf_off"));

			if (waterSlimeStatue->IsAttachedJewelry() &&
				fireSlimeStatue->IsAttachedJewelry() &&
				grassSlimeStatue->IsAttachedJewelry())
			{
				/// ŷ������ ������ ã�Ƽ� Ȱ��ȭ ���·� �ٲ��ش�.
				Statue* kingSlimeStatue = dynamic_cast<Statue*>(MGSceneManager->GetNowScene()->m_pGameObjectManager->FindGameObject("statue_king_off"));
				kingSlimeStatue->SetSprite(SLDataManager->GetSprite("statue_king_on"));

				//kingSlimeStatue->
				m_KingWakeup = true;
				SetAnimation(SLDataManager->GetAnimation("playerEnding"));
				for (auto i : MGScene->m_pGameObjectManager->m_ItemList)
				{
					if (i.second.second->m_Tag == "shining_starting_point")
					{
						Animation* temp = SLDataManager->GetAnimation("starting_ani_sprite");
						i.second.second->SetAnimation(temp);
						break;
					}
				}

				cout << "[Statue] ŷ������ ���� Ȱ��ȭ!!! \n\n";

			}

		}


		if (gameObject->m_Tag == "shining_starting_point"
			&& m_KingWakeup
			&& (Distance(gameObject->m_Transform.Position.x, gameObject->m_Transform.Position.y, this->m_Transform.Position.x, this->m_Transform.Position.y) <= 20.0f))
		{
			//���� Ŭ����
			m_GameClear = true;
			SoundManager::PlayEX("KingSlime");
			m_pAnimation = nullptr;
			SetSprite(m_EndingAnim->m_pSprites[0]);
			m_EndingAnim->Reset();
			SetAnimation(m_EndingAnim);

			if (KeyInput->InputKeyDown(VK_X)) return;
		}

	}
}

void Player::Shoot()
{
	//cout << "[System] Player::Shoot() ȣ��\n\n";

	// ���� ���ΰ� ���� ����
	bool attackState = m_State & PlayerState::Attacking;

	// ���� �������� �Ǵ�
	if (KeyInput->InputKeyDown(VK_X) &&	// X Ű�� ������ 
		!attackState &&					// ���� ���� �����̸鼭
		m_SkillGauge > 0 				// �������� 1 �̻� 
		)
	{
		// �߻��� ������ �߻�ü�� ����� �Ӽ��� ������ ����.
		for (int i = 0; i < MAX_BULLET_SIZE; i++)
		{
			// �߻� ������ ���� �߻�ü�� ã�´�.
			if (!m_Bullets[i]->GetIsFired())
			{
				cout << "[Player] " << i << " �߻� ����!\n";

				// ���� ���� ���� �߰�
				m_State |= PlayerState::Attacking;

				// �߻���ġ�� �߻������ �����ش�.
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

				// ������ ����
				m_SkillGauge -= 20;

				break;
			}

		}
	}

	if (attackState && m_pAnimation->m_TotalDelay >= 1.0f)
	{
		m_State &= ~PlayerState::Attacking;
	}

	//for (int i = 0; i < MAX_BULLET_SIZE; i++)
	//{
	//	m_Bullets[i]->Update();
	//}

}

bool Player::IsDead() const
{
	if (m_State & PlayerState::Live)
	{
		//cout << "[System] ���� �� alive\n";
		return false;
	}

	//cout << "[System] ���... Dead\n";

	return true;
}

void Player::ShowPlayerStateToConsole() const
{
	// �� ���� ������ ����
	uint isLive = m_State & PlayerState::Live;
	uint isAbsorb = m_State & PlayerState::Absorb;
	uint isAttacking = m_State & PlayerState::Attacking;
	uint isHit = m_State & PlayerState::Hit;

	uint hasWaterJewelry = m_PlayerBag & PlayerBag::Water;
	uint hasFireJewelry = m_PlayerBag & PlayerBag::Fire;
	uint hasGrassJewelry = m_PlayerBag & PlayerBag::Grass;

	cout << "<Now Player State>\n";
	cout << "Life - " << m_Life << "\n";
	cout << "Hp   - " << m_CurrentHp << "\n";
	cout << "���� - " << isLive << "\n";
	cout << "��� - " << isAbsorb << "\n";
	cout << "���� - " << isAttacking << "\n";
	cout << "�ǰ� - " << isHit << "\n";
	cout << "���� - " << m_SkillGauge << "\n";
	cout << "�Ӽ� - " << static_cast<int>(m_Attribute) << "\n";
	cout << "�̵��ӵ� - " << m_MoveSpeed << "\n\n";

	cout << "�� ���� - " << hasWaterJewelry << "\n";
	cout << "�� ���� - " << hasFireJewelry << "\n";
	cout << "Ǯ ���� - " << hasGrassJewelry << "\n";
	cout << "================\n\n";


	cout << "\n\n";
}

void Player::DecreasesGauge()
{
	// �̹� �������� 0�̸� ���� ������� ����
	if (m_SkillGauge <= 0)
	{
		return;
	}

	// ������ ���� Ÿ�̸� ����
	static float timer = m_Skill_Gauge_Decreases_Interval;

	// �ð��� ����~
	timer -= 1.0f / 8.0f;	// �и� �����ؼ� �ӵ� ���� ����

	// Ÿ�̸Ӱ� �Ǹ�
	if (timer <= 0)
	{
		// ������ ����
		m_SkillGauge -= 1;

		// Ÿ�̸� ����
		timer = m_Skill_Gauge_Decreases_Interval;
	}
}

uint Player::GetPlayerBag()
{
	return m_PlayerBag;
}

void Player::SetPlayerBag(const uint val)
{
	m_PlayerBag = val;
}

bool Player::IsGameClear()
{
	return m_GameClear && m_pAnimation == nullptr;
}

