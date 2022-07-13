#include "stdafx.h"

Player::Player(string name)
	: Unit(name)
{
	this->m_Attribute = UnitAttribute::None;	// 무속성 상태로

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

	this->m_SkillGauge = 0;		// 공격 게이지
	//this->m_SkillGauge = 100;		// 일단은 테스트 쉽게 처음에 100으로 해주자. 

	// 처음에 생존중인 상태로 설정
	// 나머지는 0으로
	m_State = PlayerState::Live;

	this->SetLayer((int)SLLayer::Player);

	// 발사체 초기화
	for (int i = 0; i < MAX_BULLET_SIZE; i++)
	{
		// 발사체 미리 생성
		m_Bullets[i] = new Bullet(this);	// 발사 주체(슈터)가 누군지 알려줌
		m_Bullets[i]->SetLayer((int)SLLayer::Player_Atk);
	}

	//UI 생성
	this->InitUI();

	SetMyAnimation();
}

Player::~Player()
{
	for (int i = 0; i < MAX_BULLET_SIZE; i++)
	{
		// 발사체 메모리 해제
		delete m_Bullets[i];
	}
}

void Player::Reset()
{
	this->m_Attribute = UnitAttribute::None;	// 무속성 상태로
	this->m_LookVector = { 0.0f,1.0f };
	this->m_Life = 3;
	this->m_CurrentHp = 3;

	this->m_SkillGauge = 0;		// 공격 게이지

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


	//SLDataManager의 애니메이션을 이용하여 새로운 애니메이션 생성
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
	//Animation 상태 체크
	//이동 먼저 체크
	if (GetDirect().x == 0 && GetDirect().y == 0)
	{
		m_AnimState = PlayerAnimState::Idle;
	}
	else
	{
		m_AnimState = PlayerAnimState::Move;
	}
	//이동 체크 이후 상태 체크
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

	//방향 체크
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
	// 스킬게이지 UI 초기화
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

	Sprite* tempSprite;			// Image UI를 초기화 하기 위한 변수

	// 플레이어 속성UI 초기화
	m_states[0] = SLDataManager->GetSprite("ui_stateGray");
	m_states[1] = SLDataManager->GetSprite("ui_stateBlue");
	m_states[2] = SLDataManager->GetSprite("ui_stateRed");
	m_states[3] = SLDataManager->GetSprite("ui_stateGreen");
	m_AttributeBar = new ImageUI();
	tempSprite = m_states[0];								// 무속성 default
	m_AttributeBar->SetSprite(tempSprite);
	m_AttributeBar->m_Transform.Position.x = 32 + tempSprite->m_pBitmap->GetSize().width * 0.5f;
	m_AttributeBar->m_Transform.Position.y = 30 + tempSprite->m_pBitmap->GetSize().height * 0.5f;

	// 라이프 UI 초기화(슬라임 실루엣)
	m_LifeImageUI = new ImageUI();
	tempSprite = SLDataManager->GetSprite("ui_life");
	m_LifeImageUI->SetSprite(tempSprite);
	m_LifeImageUI->m_Transform.Position.x = m_AttributeBar->m_Transform.Position.x
		+ (m_AttributeBar->m_pRenderer->GetSprite()->m_pBitmap->GetSize().width * 0.3f);
	m_LifeImageUI->m_Transform.Position.y = 26 + tempSprite->m_pBitmap->GetSize().height * 0.5f;

	// 라이프 UI 초기화(숫자)
	m_LifeNumber[0] = SLDataManager->GetSprite("ui_num00");
	m_LifeNumber[1] = SLDataManager->GetSprite("ui_num01");
	m_LifeNumber[2] = SLDataManager->GetSprite("ui_num02");
	m_LifeNumber[3] = SLDataManager->GetSprite("ui_num03");
	m_LifeNumUI = new ImageUI();
	tempSprite = m_LifeNumber[3];							// 라이프 3 default
	m_LifeNumUI->SetSprite(tempSprite);
	m_LifeNumUI->m_Transform.Position.x = 408 + tempSprite->m_pBitmap->GetSize().width * 0.5f;
	m_LifeNumUI->m_Transform.Position.y = 33 + tempSprite->m_pBitmap->GetSize().height * 0.5f;

	// 라이프 UI 초기화(하트)
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

	// 보석 UI 초기화
	for (int i = 0; i < 3; i++)
	{
		m_JewelUI[i] = new ImageUI();
		tempSprite = SLDataManager->GetSprite("ui_jewelOff");	// 보석 없음 default
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
	// 속성 UI
	m_AttributeBar->SetSprite(m_states[(int)m_Attribute]);

	switch ((int)m_Attribute)
	{
	case 1: // 물
		m_SkillGaugeBar->m_Color = D2D1::ColorF(D2D1::ColorF(0.41f, 0.8f, 0.92f, 1.0f));
		break;
	case 2: // 불
		m_SkillGaugeBar->m_Color = D2D1::ColorF(D2D1::ColorF(1.0f, 0.54f, 0.2f, 1.0f));
		break;
	case 3: // 풀
		m_SkillGaugeBar->m_Color = D2D1::ColorF(D2D1::ColorF(0.4f, 0.82f, 0.92f, 0.32f));
		break;
	}
	m_SkillGaugeBar->m_FillAmount = (float)m_SkillGauge * 0.01f;

	// 라이프 UI
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

	// 보석 UI
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

	/// 플레이어가 죽어 있으면
	if (IsDead())
	{
		// 업데이트 하지 않는다.
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

	/// 살아있으면 로직을 돌린다. Update

	// 피격 중이면 피격 타이머를 돌린다.
	if (m_State & PlayerState::Hit)
	{
		// 히트 타이머 돌리기
		hitTimer -= 1.0f / 60.0f;

		// 피격 시간 끝나면
		if (hitTimer <= 0)
		{
			cout << "[Player] 피격 끝~\n\n";

			// 피격 상태 해제
			m_State &= ~PlayerState::Hit;
		}
	}

	if (!this->m_pCollider->m_Hits.empty())
	{
		// 충돌 프로세스
		Collision();
	}

	if (m_GameClear)
	{
		return;
	}

	// 이동
	Move();

	// 공격(속성) 흡수
	Absorb();

	// 발사 관련 루틴
	Shoot();

	// 스킬(공격)게이지 감소
	DecreasesGauge();

	/// 임시 테스트용
	// 콘솔에 플레이어 상태 출력
	if (KeyInput->InputKeyDown(VK_C))
	{
		ShowPlayerStateToConsole();
	}

	// 피격 함수 테스트용 호출
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

	//Animation State 갱신
	UpdateAnimState();

	//UI 갱신
	UIUpdate();
}

void Player::Move()
{
	/// 동시 키 입력(이동) 불가
	static int FPS = 0;

	// 우 이동
	if (KeyInput->InputKey(VK_RIGHT))
	{

		m_LookVector = { +1.0f, 0.0f };

		m_Transform.Position.x += m_LookVector.x * m_MoveSpeed;
		m_Transform.Position.y += m_LookVector.y * m_MoveSpeed;
	}

	// 좌 이동
	else if (KeyInput->InputKey(VK_LEFT))
	{
		m_LookVector = { -1.0f, 0.0f };

		m_Transform.Position.x += m_LookVector.x * m_MoveSpeed;
		m_Transform.Position.y += m_LookVector.y * m_MoveSpeed;
	}

	// 상 이동
	else if (KeyInput->InputKey(VK_UP))
	{
		m_LookVector = { 0.0f, -1.0f };

		m_Transform.Position.x += m_LookVector.x * m_MoveSpeed;
		m_Transform.Position.y += m_LookVector.y * m_MoveSpeed;
	}

	// 하 이동
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
	// 히트 타이머 초기화

	// 흡수 상태인지 체크하자
	uint absorbState = m_State & PlayerState::Absorb;

	// 흡수 중인 상태라면
	if (absorbState)
	{
		// 공격을 흡수(속성 변환) 한다
		ChangeAttribute(UnitAttribute::Water);
	}

	// 피격당할 때
	else
	{
		// 피격 상태 추출
		uint hitState = m_State & PlayerState::Hit;

		// 이미 피격 중이면 기다린다.
		if (hitState)
		{
			cout << "[Player] 이미 피격중~\n";

			return;
		}

		// 캐릭터 피격시 효과음
		SoundManager::PlayEX("Ch_Hit");

		// 히트(피격) 상태 추가
		m_State |= PlayerState::Hit;

		// 히트 타이머 시작
		hitTimer = m_Hit_Interval;

		// Hp 1 감소;
		this->m_CurrentHp--;

		cout << "[Player] 피격 I'm Hit!!!\n";
		cout << "[Player] 현재 Hp = " << m_CurrentHp << "\n\n";

		// 일단 위치를 살짝 움직여 주자.
		// 방향 계산
		//float dirX = gameObject->m_Transform.Position.x - this->GetDirect().x
		//this->m_Transform.Position.x += 500;
		//this->m_Transform.Position.y += 500;

		// Hp 체크
		if (this->m_CurrentHp < 0)
		{
			// 라이프 감소
			if (m_Life >= 1)
			{
				m_Life -= 1;
				m_CurrentHp = 3;
			}
			// 사망 상태로 변경
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
	/// 피격당했을 때
	/// 흡수 중이면 속성(스킬)을 흡수하게 하고
	/// 흡수 중이 아니면 체력이 빠지게 하자

	// 히트 타이머 초기화

	// 흡수 상태인지 체크하자
	uint absorbState = m_State & PlayerState::Absorb;

	// 흡수 중인 상태라면
	if (absorbState && gameObject->m_Tag == "Bullet")
	{
		Bullet* bullet = dynamic_cast<Bullet*>(gameObject);

		if (bullet)
		{
			//공격 방향 체크
			//0도 위->아래
			//90도 왼쪽->오른쪽
			//180도 아래->위
			//-90도 오른쪽->왼쪽
			float angle = bullet->m_pRenderer->m_Transform.Angle;
			bool isDir = false;
			if (((GetLookVector().x == -1.0f) && angle == -90)
				|| ((GetLookVector().x == 1.0f) && angle == 90)
				|| ((GetLookVector().y == -1.0f) && angle == 0)
				|| ((GetLookVector().y == 1.0f) && angle == 180))
			{
				isDir = true;
			}

			//방향이 맞으면 공격을 흡수(속성 변환) 한다
			if (isDir)
			{
				ChangeAttribute(bullet->GetAttribute());
			}

			// 방향이 다르면
			else
			{
				// 피격 상태 추출
				uint hitState = m_State & PlayerState::Hit;

				// 이미 피격 중이면 기다린다.
				if (hitState)
				{
					cout << "[Player] 이미 피격중~\n";

					return;
				}

				// 캐릭터 피격시 효과음
				SoundManager::PlayEX("Ch_Hit");

				// 히트(피격) 상태 추가
				m_State |= PlayerState::Hit;

				// 히트 타이머 시작
				hitTimer = m_Hit_Interval;

				// Hp 1 감소;
				this->m_CurrentHp--;

				cout << "[Player] 피격 I'm Hit!!!\n";
				cout << "[Player] 현재 Hp = " << m_CurrentHp << "\n\n";

				/// 일단 위치를 살짝 움직여 주자.
				float dirX = gameObject->GetDirect().x;
				float dirY = gameObject->GetDirect().y;


				// 테스트용 멈춰있는 오브젝트랑 부딪혔을 떄 임시로 방향을 설정한다.
				if (dirX == 0.0f && dirY == 0.0f)
				{
					dirX = -1.0f;	// 실제로는 몬스터나 bullet와 부딪힐테니 아마 없어도 될 것이다.
				}

				this->m_Transform.Position.x += dirX * 50.0f;
				this->m_Transform.Position.y += dirY * 50.0f;

				// Hp 체크
				if (this->m_CurrentHp < 0)
				{
					// 라이프 감소
					if (m_Life >= 1)
					{
						m_Life -= 1;
						m_CurrentHp = 3;
					}
					// 사망 상태로 변경
					else
					{
						m_State &= ~PlayerState::Live;
					}
				}

				ShowPlayerStateToConsole();
			}

		}

	}

	// 피격당할 때
	else
	{
		// 피격 상태 추출
		uint hitState = m_State & PlayerState::Hit;

		// 이미 피격 중이면 기다린다.
		if (hitState)
		{
			cout << "[Player] 이미 피격중~\n";

			return;
		}

		// 캐릭터 피격시 효과음
		SoundManager::PlayEX("Ch_Hit");

		// 히트(피격) 상태 추가
		m_State |= PlayerState::Hit;

		// 히트 타이머 시작
		hitTimer = m_Hit_Interval;

		// Hp 1 감소;
		this->m_CurrentHp--;

		cout << "[Player] 피격 I'm Hit!!!\n";
		cout << "[Player] 현재 Hp = " << m_CurrentHp << "\n\n";

		/// 일단 위치를 살짝 움직여 주자.
		float dirX = gameObject->GetDirect().x;
		float dirY = gameObject->GetDirect().y;


		// 테스트용 멈춰있는 오브젝트랑 부딪혔을 떄 임시로 방향을 설정한다.
		if (dirX == 0.0f && dirY == 0.0f)
		{
			dirX = -1.0f;	// 실제로는 몬스터나 bullet와 부딪힐테니 아마 없어도 될 것이다.
		}

		this->m_Transform.Position.x += dirX * 50.0f;
		this->m_Transform.Position.y += dirY * 50.0f;

		// Hp 체크
		if (this->m_CurrentHp < 0)
		{
			// 라이프 감소
			if (m_Life >= 1)
			{
				m_Life -= 1;
				m_CurrentHp = 3;
			}
			// 사망 상태로 변경
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
	/// 흡수에 사용할 타이머
	static float coolTimer = 0.0f;		// 쿨타임 타이머
	static float durationTimer = 0.0f;		// 지속시간 타이머

	/// 캐릭터의 흡수 상태 여부 추출
	uint absorbState = m_State & PlayerState::Absorb;

	/// 흡수 쿨타임일 때
	if (coolTimer > 0.0f)
	{
		// dTime(엔진타임?) 만큼 타이머 뺌
		coolTimer -= 1.0f / 60.0f;		// 임시로 상수를 때려박자

		//cout << coolTimer << "\n";

		// 타이머가 0이 되면
		if (coolTimer <= 0.0f)
		{
			// 흡수 시도 가능 상태로 변경
			cout << "[Player] 흡수 쿨타임 끝~~\n\n";
		}
	}

	/// 흡수 동작(액션) 중이면
	if (absorbState) // ==> if (absorbState == PlayerState::Absorb)
	{
		//cout << "흡수 동작 중\n";

		durationTimer -= 1.0f / 60.0f;		// 지속시간 감소
		//cout << durationTimer << "\n\n";

		// 지속시간이 끝나면
		if (durationTimer <= 0.0f)
		{
			// 흡수 동작 중지
			m_State &= ~PlayerState::Absorb;

			cout << "[Player] 흡수 액션 끝~\n";

			// 애니메이션도 중지해야 한다.
		}
	}


	/// 'Z' 키를 누르면
	if (KeyInput->InputKeyDown(VK_Z))
	{
		/// 흡수 가능하면
		// -> 쿨타임 돌았고, 플레이어가 흡수중이 아닌 상태면
		if (coolTimer <= 0 && absorbState == false)
		{
			cout << "[Player] 흡수 시작~\n";

			// 흡수 불가능 상태로 변경(쿨타임 돌리기)

			// 쿨타임 타이머 세팅
			coolTimer = m_Absorb_Delay;

			// 캐릭터를 흡수하는 상태로 변경(실제로 흡수 동작)
			m_State |= PlayerState::Absorb;

			// 지속시간 타이머 세팅
			durationTimer = m_Absorb_Duration;

			// 흡수하는 애니매이션 동작(세팅) 해야함

			SoundManager::PlayEX("Ch_Absorb");
		}

		/// 흡수 불가능하면
		else
		{
			// 이미 사용중
			if (absorbState)
			{
				cout << "[Player] 이미 흡수 중 입니다~\n";
			}

			// 쿨타임 기다리는 중
			else
			{
				cout << "[Player] 흡수 쿨타임 도는 중~ !!\n";
			}
		}
	}
}

void Player::ChangeAttribute(UnitAttribute attribute)
{
	cout << "[Player] ChangeAttribute(UnitAttribute attribute) 호출\n";

	uint absorbState = m_State & PlayerState::Absorb;

	if (m_State == false)
	{
		cout << "[Player] 이미 흡수 중~\n\n";

		return;
	}

	// 속성을 변환하고
	cout << "[Player] 속성 변환 (" << static_cast<int>(m_Attribute);
	m_Attribute = attribute;
	cout << " - > " << static_cast<int>(m_Attribute) << ") ~~\n";

	// 스킬게이지를 회복
	m_SkillGauge = (m_Attribute == UnitAttribute::None) ? 0 : m_Skill_Gauge_Max;
	cout << "[Player] 스킬(공격) 게이지 회복!\n\n";

	//애니메이션 변경
	UpdateAnimState();
}

void Player::Collision()
{
	//cout << "[Player] 충돌 m_Hits.size = " << m_pCollider->m_Hits.size() << "\n";

	for (auto obj : this->m_pCollider->m_Hits)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(obj);

		//cout << "[Player] 충돌 오브젝트의 tag = " << gameObject->m_Tag << "\n\n";

		// 충돌한 오브젝트가 Monster 인경우에
		if (gameObject->m_Tag == "Mon_Water" ||
			gameObject->m_Tag == "Mon_Fire" ||
			gameObject->m_Tag == "Mon_Grass")
		{
			Monster* monster = dynamic_cast<Monster*>(gameObject);

			// 피격 처리를 한다.
			ReceiveAttack(monster);
		}

		// 충돌한 오브젝트가 bullet인 경우에
		if (gameObject->m_Tag == "Bullet")
		{
			Bullet* bullet = dynamic_cast<Bullet*>(gameObject);

			// 그 bullet의 슈터가 Monster 이라면
			if (bullet->m_Shooter->m_Tag == "Mon_Water" ||
				bullet->m_Shooter->m_Tag == "Mon_Fire" ||
				bullet->m_Shooter->m_Tag == "Mon_Grass")
			{
				// 피격 처리를 한다.
				ReceiveAttack(bullet);
			}
		}

		// 충돌한 오브젝트가 석상인 경우에
		if (gameObject->m_Tag == "statue_water_off" ||
			gameObject->m_Tag == "statue_fire_off" ||
			gameObject->m_Tag == "statue_leaf_off")
		{
			/// 모든 석상이 보석을 가지고 있다면
			Statue* waterSlimeStatue = dynamic_cast<Statue*>(MGSceneManager->GetNowScene()->m_pGameObjectManager->FindGameObject("statue_water_off"));
			Statue* fireSlimeStatue = dynamic_cast<Statue*>(MGSceneManager->GetNowScene()->m_pGameObjectManager->FindGameObject("statue_fire_off"));
			Statue* grassSlimeStatue = dynamic_cast<Statue*>(MGSceneManager->GetNowScene()->m_pGameObjectManager->FindGameObject("statue_leaf_off"));

			if (waterSlimeStatue->IsAttachedJewelry() &&
				fireSlimeStatue->IsAttachedJewelry() &&
				grassSlimeStatue->IsAttachedJewelry())
			{
				/// 킹슬라임 석상을 찾아서 활성화 상태로 바꿔준다.
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

				cout << "[Statue] 킹슬라임 석상 활성화!!! \n\n";

			}

		}


		if (gameObject->m_Tag == "shining_starting_point"
			&& m_KingWakeup
			&& (Distance(gameObject->m_Transform.Position.x, gameObject->m_Transform.Position.y, this->m_Transform.Position.x, this->m_Transform.Position.y) <= 20.0f))
		{
			//게임 클리어
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
	//cout << "[System] Player::Shoot() 호출\n\n";

	// 공격 중인가 상태 추출
	bool attackState = m_State & PlayerState::Attacking;

	// 공격 가능한지 판단
	if (KeyInput->InputKeyDown(VK_X) &&	// X 키를 눌렀고 
		!attackState &&					// 공격 가능 상태이면서
		m_SkillGauge > 0 				// 게이지도 1 이상 
		)
	{
		// 발사한 순간에 발사체에 방향과 속성을 설정해 주자.
		for (int i = 0; i < MAX_BULLET_SIZE; i++)
		{
			// 발사 중이지 않은 발사체를 찾는다.
			if (!m_Bullets[i]->GetIsFired())
			{
				cout << "[Player] " << i << " 발사 성공!\n";

				// 공격 중인 상태 추가
				m_State |= PlayerState::Attacking;

				// 발사위치와 발사방향을 정해준다.
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

				// 게이지 감소
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
		//cout << "[System] 생존 중 alive\n";
		return false;
	}

	//cout << "[System] 사망... Dead\n";

	return true;
}

void Player::ShowPlayerStateToConsole() const
{
	// 각 상태 정보를 추출
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
	cout << "생존 - " << isLive << "\n";
	cout << "흡수 - " << isAbsorb << "\n";
	cout << "공격 - " << isAttacking << "\n";
	cout << "피격 - " << isHit << "\n";
	cout << "마나 - " << m_SkillGauge << "\n";
	cout << "속성 - " << static_cast<int>(m_Attribute) << "\n";
	cout << "이동속도 - " << m_MoveSpeed << "\n\n";

	cout << "물 보석 - " << hasWaterJewelry << "\n";
	cout << "불 보석 - " << hasFireJewelry << "\n";
	cout << "풀 보석 - " << hasGrassJewelry << "\n";
	cout << "================\n\n";


	cout << "\n\n";
}

void Player::DecreasesGauge()
{
	// 이미 게이지가 0이면 굳이 계산하지 말자
	if (m_SkillGauge <= 0)
	{
		return;
	}

	// 게이지 감소 타이머 설정
	static float timer = m_Skill_Gauge_Decreases_Interval;

	// 시간은 간다~
	timer -= 1.0f / 8.0f;	// 분모를 조정해서 속도 조절 가능

	// 타이머가 되면
	if (timer <= 0)
	{
		// 게이지 감소
		m_SkillGauge -= 1;

		// 타이머 리셋
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

