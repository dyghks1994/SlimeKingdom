#pragma once

/// Player Ŭ���� �ۼ�
/// ������ ���ΰ�, �̵�, ����, ���, ��ȣ�ۿ� ����
/// 
/// �ۼ��� : �ֿ�ȯ, �����
/// 2021.02.15

#include "Unit.h"
#include "SOUND_pch.h"
#include <wincrypt.h>


enum PlayerState : uint
{
	Live			= 1U << 0,	// 1  ���� ���� Live / Dead	
	Absorb			= 1U << 1,	// 2  ��� �� On / off		
	Attacking		= 1U << 2,	// 4  ���� �� On / Off		
	Hit				= 1U << 3,	// 8  �ǰ� �� On / Off		
};

enum PlayerBag : uint
{
	Water	= 1U << 0,		// �� ���� ĭ
	Fire	= 1U << 1,		// �� ���� ĭ
	Grass	= 1U << 2,		// Ǯ ���� ĭ
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

	//�÷��̾� �ִϸ�����
	State* animState[(int)UnitAttribute::AttributeNum][(int)PlayerAnimState::AnimStateNum];
	Animation* anims[(int)UnitAttribute::AttributeNum][(int)PlayerAnimState::AnimStateNum][(int)AnimDir::DirNum];

	PlayerAnimState m_AnimState;
	AnimDir m_AnimDir;
	void SetMyAnimation();
	void UpdateAnimState();

	//Player UI
	ImageUI* m_HeartUI[3];			// Hp

	Sprite* m_LifeNumber[4];		// ������
	ImageUI* m_LifeImageUI;
	ImageUI* m_LifeNumUI;
	
	Sprite* m_states[4];			// �Ӽ�
	ImageUI* m_AttributeBar;		
	RectUI* m_SkillGaugeBase;
	RectUI* m_SkillGaugeBar;
	
	Sprite* m_Jewel[3];				// ����
	ImageUI* m_JewelUI[3];			
	
	void InitUI();
	void UIUpdate();

	virtual void Update();

	// �÷��̾� �̵�
	virtual void Move() override;	

	/// �Ӽ� ��� �õ� �� ���� ������ �� ��� ó���ұ�?
	/// ������ �Լ�(���)�� ����?
	/// �׳� �ǰ� ���� �� ����׼� ���ӽð� ���̸� ����� ����??
	/// 1. ������ �߻�ü�� �浹�Ѵ�.
	///		1.1 ������̴� -> �Ӽ� ���(�ǰ�X)
	///		1.2 ������� �ƴϴ� -> �ǰ�(ü���� ����)

	// �ǰ�
	virtual void ReceiveAttack() override;	// �׽�Ʈ�� ��ư �Է½� Ȯ�ο�
	virtual void ReceiveAttack(GameObject* gameObject) override;

	// �Ӽ�(��ų) ���
	void Absorb();

	// ��� �߿� �ǰ�(�浹) ���� �� �Ӽ��� ��ȯ�Ѵ�.
	void ChangeAttribute(UnitAttribute attribute);		// �Ķ���͸� �߰��� ����

	// �浹
	virtual void Collision() override;


	// �߻�
	virtual void Shoot() override;

	// ����߳�?
	virtual bool IsDead() const override;

	// �÷��̾� ���� üũ�� ��� �Լ�
	void ShowPlayerStateToConsole() const;
	
	// ������ ����
	void DecreasesGauge();
	
	// �÷��̾� ���� ���� ���
	uint GetPlayerBag();
	void SetPlayerBag(const uint val);

	bool IsGameClear();

protected:

private:
	uint m_State;			// �÷��̾� ����
	uint m_PlayerBag;		// ȹ���� ������ ������ ����

	int m_SkillGauge;		// ��ų(����) ����� �� �ʿ��� ������

	float m_Absorb_Delay					= 1.0f;		// ��� ��Ÿ��
	float m_Absorb_Duration					= 0.5f;		// ��� �׼� ���ӽð�

	int m_Skill_Gauge_Max					= 100;		// ��ų ������ MAX
	float m_Skill_Gauge_Decreases_Interval  = 1.0f;		// ��ų ������ �����ϴ� �ð� ����
	
	float m_Hit_Interval					= 1.0f;		// �ǰ� ���� �ð�
	float hitTimer = 0.0f;								// �ǰ� Ÿ�̸�

	/// ���� Ŭ���� Ȯ�ο� ����
	bool m_GameClear;
	bool m_KingWakeup;

	Animation* m_EndingAnim;
														
	/// To ������
	/// �÷��̾��� ���¿��� Ư�� ���¸� Ȯ���ϴ� ���
	/// 
	/// ex) ���� ����ֳ�?
	///   1101	(���� ���� -> �ǰ�(o), ����(o), ���(x) ����(o))
	/// & 0001  (���� ���� ���̶� ��Ʈ ����(AND) )
	/// ---------
	///   0001  ( ���� ���� ���θ� ����)
	/// 
	/// 
	/// ex) Ư�� ���� �߰��ϰ� ���� ��
	///   1101	(���� ���� -> �ǰ�(o), ����(o), ���(x) ����(o))
	/// | 0010	(��� ���� ���̶� ��Ʈ ����(OR) )
	/// ---------
	///   1111	(���� ���¿��� ��� ���°� �߰� ��)
	/// 
	/// 
	/// ex) Ư�� ���� �����ϰ� ���� ��
	///   1101	(���� ���� -> �ǰ�(o), ����(o), ���(x) ����(o))
	/// & 1110	(~���� ���� ��(��Ʈ ����)�̶� ��Ʈ ����(AND) )
	/// ---------
	///   1100	(���� ���¿��� �ٸ��� �״�ΰ� ���� ���¸� ���� ��)
};

