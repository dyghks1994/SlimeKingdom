#pragma once

/// <summary>
/// Monster 클래스
/// 자동으로 이동, 탐지, 공격, 리스폰을 해야한다
/// 
/// 작성자 : 최요환
/// 2021.02.19
/// </summary>



/// <summary>
/// 필요한 상태 생각해 보자..
/// 
/// 생존 여부(스폰 타이머 or 기타 행동)
/// 탐지 여부(X -> 자유롭게 이동 / O -> 플레이어 추적)
/// 
/// </summary>
/// enum class MonsterState

enum class MonsterState
{
	Move,		// 플레이어 미감지 자유 이동 상태
	Hunting,	// 플레이어를 감지해서 따라가는 상태
};

enum class MonsterAnimState
{
	Idle,
	Move,
	Hit,
	Attack,

	Num
};

class Monster : public Unit
{
public:
	static int count;

	// 각 몬스터들의 처음 생성 위치를 어떻게??
	// 몬스터를 생성할 떄는 각각의 스폰 위치와 속성이 필요함
	Monster(string name = "Monster", float spawnPosX = 300.0f, float spawnPosY = 300.0f, UnitAttribute attribute = UnitAttribute::Fire);
	~Monster();

	// 초기화
	void Initialize(float spawnPosX = 300.0f, float spawnPosY = 300.0f, UnitAttribute attribute = UnitAttribute::Fire);

	//리셋
	void Reset();

	// 업데이트
	virtual void Update();

	void Collision();

	// 스폰 프로세스
	void SpawnProcess();

	// 스폰
	void Spawn();

	// 이동
	virtual void Move() override;

	// 발사
	virtual void Shoot() override;

	// 피격
	virtual void ReceiveAttack() override;

	// 사망했나?
	virtual bool IsDead() const override;

	//애니메이션 관련
	void SetAnimations();
	void UpdateAnimState();

	bool IsPlayerInRange();

protected:

public:
	Player* m_pPlayer;

private:
	//애니메이션 변수들
	MonsterAnimState m_AnimState;
	AnimDir m_AnimDir;
	Animation* anims[(int)MonsterAnimState::Num][(int)AnimDir::DirNum];

	MonsterState m_State;		// 몬스터의 상태

	const float m_SpawnWaitngTime;	// 죽었을 때 리스폰 대기할 시간
	float m_SpawnWait;			//스폰까지 기다린 대기 시간
	float m_SpawnPosX;			// 스폰 위치 X
	float m_SpawnPosY;			// 스폰 위치 Y

	float m_DetectionRange;		// 플레이어를 탐지 할 범위
	//float m_AttackRange;		// 공격 사거리

	float m_SpawnWaitNow;

	float m_AttackTimer;
	float m_ChangeDirTimer;
};

