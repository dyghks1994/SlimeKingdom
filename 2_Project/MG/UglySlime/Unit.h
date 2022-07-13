#pragma once

/// Unit Ŭ����
/// ���ӿ� �����ϴ� ���ֵ�
/// �ֿ�ȯ, �����
/// 2021.02.15


#include "GameObject.h"

#define MAX_BULLET_SIZE 5		// �߻�ü �ִ� ������

enum class UnitAttribute 
{
	None,		// ���Ӽ�
	Water,		// ���Ӽ�
	Fire,		// �ҼӼ�
	Grass,		// Ǯ�Ӽ�

	AttributeNum
};

class Bullet;

class Unit : public GameObject
{
public:
	Unit(string = "GameObject");
	~Unit();


	//============================================
	// Geeter / Setter
	//============================================
	int GetLife() const;
	void SetLife(const int life);

	int GetCurrentHp() const;
	void SetCurrentHp(const int hp);

	int GetMaxHp() const;
	void SetMaxHp(const int hp);

	D2D1_POINT_2F GetLookVector();

	float GetMoveSpeed() const;
	void SetMoveSpeed(const float moveSpeed);
	
	float GetShootSpeed() const;
	void SetShootSpeed(const float attackSpeed);

	UnitAttribute GetAttribute() const;

	// �̵�
	virtual void Move() {}

	// �浹
	virtual void Collision() {}

	// �߻�
	virtual void Shoot() {}

	// �ǰ�
	virtual void ReceiveAttack() {}
	virtual void ReceiveAttack(GameObject* gameObject) {}

	// ����߳�?
	virtual bool IsDead() const { return false; }

protected:
	int m_Life;							// ������
	int m_MaxHp;						// �ִ� �����
	int m_CurrentHp;					// ���� �����

	D2D_POINT_2F m_LookVector;			// �ٶ󺸰� �ִ� ����
	float m_MoveSpeed;					// �̵��ӵ�

	bool m_IsCanAttack;					// ���� ���ݰ������� �Ǵ�
	float m_AttackSpeed;				// ���ݼӵ�
	float m_DelayCount;					// ������ ī��Ʈ ����

	UnitAttribute m_Attribute;			// ������ �Ӽ�	(����, ��, ��, Ǯ)
	Bullet* m_Bullets[MAX_BULLET_SIZE];	// ���� ������ �ִ� ��ų(źȯ ����..)

private:

};