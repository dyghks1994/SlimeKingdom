#pragma once
class Bush : public Gimmick
{
public:
	Bush(float spawnPosX = 300.0f, float spawnPosY = 300.0f, bool fruit = false, string = "Bush");
	~Bush();

	// �ʱ�ȭ
	virtual void Initialize(const float spawnPosX, const float spawnPosY) override;

	// ������Ʈ
	virtual void Update() override;

	// �浹ó��
	virtual void Collision() override;

	// �̵�(�÷��̾��� ���ۿ� ���� �и���)
	virtual void Move();
	virtual void Move(Player* player) override;

	// �ǰ�( �÷��̾�� ���ݴ����� �� )
	virtual void ReceiveAttack(Bullet* bulletObject);

protected:


private:
	bool m_Fruit;			// ���� ����(������ ȸ��, ������ X)
	bool m_IsMoving;		// ������ �� �ִ°� ���°�?(ó���� false, Grass �Ӽ� ���ݿ� ������ Ȱ��ȭ)
};

