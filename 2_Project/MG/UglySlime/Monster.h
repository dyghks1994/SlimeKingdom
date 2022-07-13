#pragma once

/// <summary>
/// Monster Ŭ����
/// �ڵ����� �̵�, Ž��, ����, �������� �ؾ��Ѵ�
/// 
/// �ۼ��� : �ֿ�ȯ
/// 2021.02.19
/// </summary>



/// <summary>
/// �ʿ��� ���� ������ ����..
/// 
/// ���� ����(���� Ÿ�̸� or ��Ÿ �ൿ)
/// Ž�� ����(X -> �����Ӱ� �̵� / O -> �÷��̾� ����)
/// 
/// </summary>
/// enum class MonsterState

enum class MonsterState
{
	Move,		// �÷��̾� �̰��� ���� �̵� ����
	Hunting,	// �÷��̾ �����ؼ� ���󰡴� ����
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

	// �� ���͵��� ó�� ���� ��ġ�� ���??
	// ���͸� ������ ���� ������ ���� ��ġ�� �Ӽ��� �ʿ���
	Monster(string name = "Monster", float spawnPosX = 300.0f, float spawnPosY = 300.0f, UnitAttribute attribute = UnitAttribute::Fire);
	~Monster();

	// �ʱ�ȭ
	void Initialize(float spawnPosX = 300.0f, float spawnPosY = 300.0f, UnitAttribute attribute = UnitAttribute::Fire);

	//����
	void Reset();

	// ������Ʈ
	virtual void Update();

	void Collision();

	// ���� ���μ���
	void SpawnProcess();

	// ����
	void Spawn();

	// �̵�
	virtual void Move() override;

	// �߻�
	virtual void Shoot() override;

	// �ǰ�
	virtual void ReceiveAttack() override;

	// ����߳�?
	virtual bool IsDead() const override;

	//�ִϸ��̼� ����
	void SetAnimations();
	void UpdateAnimState();

	bool IsPlayerInRange();

protected:

public:
	Player* m_pPlayer;

private:
	//�ִϸ��̼� ������
	MonsterAnimState m_AnimState;
	AnimDir m_AnimDir;
	Animation* anims[(int)MonsterAnimState::Num][(int)AnimDir::DirNum];

	MonsterState m_State;		// ������ ����

	const float m_SpawnWaitngTime;	// �׾��� �� ������ ����� �ð�
	float m_SpawnWait;			//�������� ��ٸ� ��� �ð�
	float m_SpawnPosX;			// ���� ��ġ X
	float m_SpawnPosY;			// ���� ��ġ Y

	float m_DetectionRange;		// �÷��̾ Ž�� �� ����
	//float m_AttackRange;		// ���� ��Ÿ�

	float m_SpawnWaitNow;

	float m_AttackTimer;
	float m_ChangeDirTimer;
};

