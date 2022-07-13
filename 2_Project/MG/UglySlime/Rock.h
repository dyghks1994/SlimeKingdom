#pragma once

/// <summary>
/// Rock Ŭ����
/// �ʱ� ���¿� ������ X
/// Ǯ �Ӽ� ���ݿ� ������ ������ O(�÷��̾ �о����)
/// �� �Ӽ� ���ݿ� ������ �ı�
/// �� �Ӽ� ���ݿ� ������ �ƹ� ��ȭ X
/// </summary>

class Rock : public Gimmick
{
public:
	Rock(float spawnPosX = 300.0f, float spawnPosY = 300.0f, string = "Rock");
	~Rock();

	// �ʱ�ȭ
	virtual void Initialize(const float spawnPosX, const float spawnPosY) override;

	// ������Ʈ
	virtual void Update() override;

	// �浹ó��
	virtual void Collision() override;

	// �̵�(�̵����� ���¶�� �÷��̾��� ���ۿ� ���� �и���)
	virtual void Move(Player* player) override;

	// �ǰ�( �÷��̾�� ���ݴ����� �� )
	virtual void ReceiveAttack(Bullet* bulletObject);

protected:


private:
	bool m_IsMoving;		// ������ �� �ִ°� ���°�?(ó���� false, Grass �Ӽ� ���ݿ� ������ Ȱ��ȭ)
};


