#pragma once

/// Player 클래스 작성
/// 게임의 주인공, 이동, 공격, 흡수, 상호작용 가능
/// 
/// 작성자 : 최요환, 김경재
/// 2021.02.15

#include "Unit.h"
#include "SOUND_pch.h"
#include <wincrypt.h>


enum PlayerState : uint
{
	Live			= 1U << 0,	// 1  생존 여부 Live / Dead	
	Absorb			= 1U << 1,	// 2  흡수 중 On / off		
	Attacking		= 1U << 2,	// 4  공격 중 On / Off		
	Hit				= 1U << 3,	// 8  피격 중 On / Off		
};

enum PlayerBag : uint
{
	Water	= 1U << 0,		// 물 보석 칸
	Fire	= 1U << 1,		// 불 보석 칸
	Grass	= 1U << 2,		// 풀 보석 칸
};



enum class PlayerAnimState

{
	Idle,
	Move,
	Eat,
	Hit,
	Attack,

	AnimStateNum
};

enum class AnimDir
{
	F,
	B,
	L,
	R,

	DirNum
};

class Player : public Unit
{
public:
	Player(string name = "Player");
	~Player();

	void Reset();

	//플레이어 애니메이터
	State* animState[(int)UnitAttribute::AttributeNum][(int)PlayerAnimState::AnimStateNum];
	Animation* anims[(int)UnitAttribute::AttributeNum][(int)PlayerAnimState::AnimStateNum][(int)AnimDir::DirNum];

	PlayerAnimState m_AnimState;
	AnimDir m_AnimDir;
	void SetMyAnimation();
	void UpdateAnimState();

	//Player UI
	ImageUI* m_HeartUI[3];			// Hp

	Sprite* m_LifeNumber[4];		// 라이프
	ImageUI* m_LifeImageUI;
	ImageUI* m_LifeNumUI;
	
	Sprite* m_states[4];			// 속성
	ImageUI* m_AttributeBar;		
	RectUI* m_SkillGaugeBase;
	RectUI* m_SkillGaugeBar;
	
	Sprite* m_Jewel[3];				// 보석
	ImageUI* m_JewelUI[3];			
	
	void InitUI();
	void UIUpdate();

	virtual void Update();

	// 플레이어 이동
	virtual void Move() override;	

	/// 속성 흡수 시도 중 공격 당했을 때 어떻게 처리할까?
	/// 별도의 함수(기능)을 구현?
	/// 그냥 피격 당할 때 흡수액션 지속시간 중이면 흡수로 가자??
	/// 1. 몬스터의 발사체에 충돌한다.
	///		1.1 흡수중이다 -> 속성 흡수(피격X)
	///		1.2 흡수중이 아니다 -> 피격(체력을 깍자)

	// 피격
	virtual void ReceiveAttack() override;	// 테스트용 버튼 입력시 확인용
	virtual void ReceiveAttack(GameObject* gameObject) override;

	// 속성(스킬) 흡수
	void Absorb();

	// 흡수 중에 피격(충돌) 했을 때 속성을 변환한다.
	void ChangeAttribute(UnitAttribute attribute);		// 파라미터를 추가해 주자

	// 충돌
	virtual void Collision() override;


	// 발사
	virtual void Shoot() override;

	// 사망했나?
	virtual bool IsDead() const override;

	// 플레이어 상태 체크용 출력 함수
	void ShowPlayerStateToConsole() const;
	
	// 게이지 감소
	void DecreasesGauge();
	
	// 플레이어 가방 정보 얻기
	uint GetPlayerBag();
	void SetPlayerBag(const uint val);

	bool IsGameClear();

protected:

private:
	uint m_State;			// 플레이어 상태
	uint m_PlayerBag;		// 획득한 보석을 가지는 가방

	int m_SkillGauge;		// 스킬(공격) 사용할 때 필요한 게이지

	float m_Absorb_Delay					= 1.0f;		// 흡수 쿨타임
	float m_Absorb_Duration					= 0.5f;		// 흡수 액션 지속시간

	int m_Skill_Gauge_Max					= 100;		// 스킬 게이지 MAX
	float m_Skill_Gauge_Decreases_Interval  = 1.0f;		// 스킬 게이지 감소하는 시간 간격
	
	float m_Hit_Interval					= 1.0f;		// 피격 간격 시간
	float hitTimer = 0.0f;								// 피격 타이머

	/// 게임 클리어 확인용 변수
	bool m_GameClear;
	bool m_KingWakeup;

	Animation* m_EndingAnim;
														
	/// To 경재형
	/// 플레이어의 상태에서 특정 상태를 확인하는 방법
	/// 
	/// ex) 현재 살아있냐?
	///   1101	(현재 상태 -> 피격(o), 공격(o), 흡수(x) 생존(o))
	/// & 0001  (생존 상태 값이랑 비트 논리곱(AND) )
	/// ---------
	///   0001  ( 현재 생존 여부만 추출)
	/// 
	/// 
	/// ex) 특정 값을 추가하고 싶을 때
	///   1101	(현재 상태 -> 피격(o), 공격(o), 흡수(x) 생존(o))
	/// | 0010	(흡수 상태 값이랑 비트 논리합(OR) )
	/// ---------
	///   1111	(원래 상태에서 흡수 상태가 추가 됌)
	/// 
	/// 
	/// ex) 특정 값만 해제하고 싶을 때
	///   1101	(현재 상태 -> 피격(o), 공격(o), 흡수(x) 생존(o))
	/// & 1110	(~생존 상태 값(비트 반전)이랑 비트 논리곱(AND) )
	/// ---------
	///   1100	(원래 상태에서 다른건 그대로고 생존 상태만 제거 됌)
};

