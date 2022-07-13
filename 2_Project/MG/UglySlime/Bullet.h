#pragma once

/// <summary>
/// Bullet Ŭ����
/// �÷��̾ ���Ͱ� ������ �� ����ϴ� �߻�ü
/// �Ӽ��� �̵�����, �ӵ� ���� ������ ��� �Ѵ�.
/// �ֿ�ȯ
/// 2021.02.16
/// </summary>

class Bullet : public GameObject
{
public:
	Bullet(Unit* shooter);
	~Bullet();

	void Initialize();

	virtual void Update();

	void Collision();

	// �Ӽ� ����
	UnitAttribute GetAttribute();
	void SetAttribute(const UnitAttribute attribute);

	// ���� ����
	void SetDirection(Unit* shooter);

	// �߻� �Ǿ����� üũ
	bool GetIsFired() const;
	void SetIsFired(const bool val);

	// �߻�
	void Shoot();

	// �̵�
	void Move();

	// �߻�ü�� ��ȿ�� ��ġ�� �ִ��� Ȯ��(ī�޶� ���� ��)
	bool CheekValidPosition();

protected:

public:
	bool m_IsFired;						// �߻� �Ǿ���? �Ǻ�

	Unit* m_Shooter;					// �� ����

	UnitAttribute m_Attribute;			// �߻�ü�� �Ӽ�
	int m_AttackPower;					// ������

	float m_MoveSpeed;					// �̵� �ӵ�
	D2D1_POINT_2F m_Dir;				// �̵� ����


	// �±�? �� �� �̷��ɷ� ������ �߻�ü�� ��ü(�÷��̾� or ����)�� ������ �˰� �ؾ� �Ѵ�.
	// ...

	// �׸��� �浹 ���� ����� �߻�ü�� ��ü�� �������� ���� ó���� ������.

};

