#pragma once
/// <summary>
/// Gimmick Ŭ����
/// ���ӿ� ��ġ�Ǵ� ����, ����, ��, ���� ������
/// �÷��̾��� ���� �Ӽ��� ���� Ư�� �׼��� ���ϰų�
/// �ı� �����ϴ�.
/// 
/// �ֿ�ȯ
/// 2021.02.21
/// </summary>

class Gimmick : public GameObject
{
public:
	Gimmick(string name = "Gimmick");
	virtual ~Gimmick();

	// �ʱ�ȭ
	virtual void Initialize(const float spawnPosX, const float spawnPosY) {}

	// ������Ʈ
	virtual void Update() {}

	virtual void Reset() {}

	bool IsDestroyed();

	virtual void Collision() {}

	// �̵�(�÷��̾��� ���ۿ� ���� �и���)
	virtual void Move() {}
	virtual void Move(Player* player) {}	// Wall �̳� Box�� �Ⱦ�������...

	// �ǰ�( �÷��̾�� ���ݴ����� �� )
	virtual void ReceiveAttack(GameObject* gameObject) {}	// Wall �̳� Box�� �Ⱦ�������...

protected:
	float m_MoveSpeed;		// �̵� �ӵ�(�÷��̾ �ж� �и��� ��)
	bool m_IsDestroyed;		// �ı� ���� �Ǻ� ����
private:
};

